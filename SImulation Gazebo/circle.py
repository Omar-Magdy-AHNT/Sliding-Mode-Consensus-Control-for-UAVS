import rclpy # Import the rclpy library for ROS functionalities

from rclpy.node import Node #Import the Node Class

from rclpy.qos import QoSProfile, ReliabilityPolicy, HistoryPolicy #Import the QoS settings

from mavros_msgs.srv import CommandBool, SetMode, CommandTOL # Import required services from mavros_msgs

from mavros_msgs.msg import State, PositionTarget # Import required messages from mavros_msgs

from geometry_msgs.msg import PoseStamped # Import PoseStamped message from geometry_msgs

import math # Import the math module for mathematical functions

class DroneController(Node): # Define the DroneController class

    def __init__(self): # Define the constructor method

        super().__init__('drone_controller') # Initialize the ROS node

        self.current_state = State() # Initialize current_state as an empty State message

        self.arm_state = False # Initialize arm_state as False

        self.rate = self.create_rate(10) # Set the loop rate to 10 Hz

        #######################################################
        
        # Define QoS settings to ensure topics are being published
        qos_profile = QoSProfile(history=HistoryPolicy.KEEP_LAST, depth=10, reliability=ReliabilityPolicy.BEST_EFFORT)

        #######################################################
        
        # ROS subscribers
        self.local_position_sub = self.create_subscription(PoseStamped, 'mavros/local_position/pose', self.pose_callback, qos_profile) # Subscribe to the 'mavros/local_position/pose' topic

        self.state_sub = self.create_subscription(State, 'mavros/state', self.state_callback, qos_profile) # Subscribe to the 'mavros/state' topic
        
        self.get_logger().info('Subscriptions initialized') #Log when subscriptions are initilaized

        #######################################################

        # ROS publishers
        self.pose_pub = self.create_publisher(PositionTarget, 'mavros/setpoint_raw/local', qos_profile) # Create a publisher for setpoints

        self.get_logger().info('Publishers initialized') #Log when publishers are initilaized

        #######################################################

        # ROS services
        self.set_mode_client = self.create_client(SetMode, 'mavros/set_mode') # Create a service client for setting the mode

        self.arming_client = self.create_client(CommandBool, 'mavros/cmd/arming') # Create a service client for arming/disarming

        self.takeoff_client = self.create_client(CommandTOL, 'mavros/cmd/takeoff') # Create a service client for takeoff

        self.get_logger().info('Services initialized') #Log when services are initilaized

        #######################################################

        #Initialize current and desired x, y, z postions

        self.curr_x = 0.0

        self.curr_y = 0.0

        self.curr_z = 0.0

        self.des_x = 0.0

        self.des_y = 0.0

        self.des_z = 0.0

    #######################################################

    def state_callback(self, state): # Define the state callback method

        self.current_state = state # Repeatedly update current_state with the self.des state data

    #######################################################

    def pose_callback(self, msg: PoseStamped): # Define the pose callback method

        self.curr_x = msg.pose.position.x # Repeatedly update the current x position
        self.curr_y = msg.pose.position.y # Repeatedly update the current y position
        self.curr_z = msg.pose.position.z # Repeatedly update the current z position

    
    #######################################################

    def connect(self): # Define the connect method

        while rclpy.ok() and not self.current_state.connected: # Loop while ROS is running and MAVROS is not connected

            self.get_logger().info('Waiting for connection to MAVROS...') # Log waiting for connection message

            rclpy.spin_once(self) # Process incoming messages

        if self.current_state.connected:

            self.get_logger().info('Connected to MAVROS!') # Log when MAVROS is connected

            return True
        
        else:
            self.get_logger().error('Failed to connect to MAVROS!') # Log if connection to MAVROS fails

            return False

    #######################################################

    def set_mode(self, mode): # Define the set_mode function to change mode of drone

        req = SetMode.Request() # Create a setMode request

        req.custom_mode = mode # Set the request to be the desired mode

        future = self.set_mode_client.call_async(req) # Call the setMode service
        
        start_time = self.get_clock().now() # Record the start time

        while rclpy.ok(): # Loop while ROS is running

            if self.current_state.mode == mode: # Check if mode is changed successfully
                
                self.get_logger().info(f'Mode changed to {mode}') # Log successful mode change

                return True
            
            if (self.get_clock().now() - start_time).to_msg().sec > 5.0: # Check for timeout

                self.get_logger().error(f'Failed to set mode to {mode}') # Log failed mode change

                return False
            
            rclpy.spin_once(self) # Process incoming messages

    #######################################################

    def arm(self, arm: bool): # Define the arm method

        req = CommandBool.Request() # Create a CommandBool requests

        req.value = arm # Set the arm/disarm value

        future = self.arming_client.call_async(req) # Call the arming/disarming service
        
        start_time = self.get_clock().now() # Record the start time

        while rclpy.ok(): # Loop while ROS is running

            if self.current_state.armed == arm: # Check if arming/disarming is successful

                if arm:

                    self.get_logger().info('Vehicle armed!') # Log successful arming

                else:

                    self.get_logger().info('Vehicle disarmed!') # Log successful disarming

                return True
            if (self.get_clock().now() - start_time).to_msg().sec > 5.0: # Check for timeout

                self.get_logger().error('Failed to arm vehicle!') # Log arming failure

                return False
            
            rclpy.spin_once(self) # Process incoming messages

    #######################################################

    def takeoff(self, altitude): # Define the takeoff method

        req = CommandTOL.Request() # Create a CommandTOL request

        req.altitude = altitude # Set the desired altitude

        future = self.takeoff_client.call_async(req) # Call the takeoff service
        
        start_time = self.get_clock().now() # Record the start time

        while rclpy.ok(): # Loop while ROS is running

            if abs(altitude - self.curr_z) <= 0.3: # check if desired altitude is reached

                self.get_logger().info(f'Reached altitude {altitude:.2f} meters') # Log successful takeoff

                return True
            
            if (self.get_clock().now() - start_time).to_msg().sec > 10.0:  # Increase timeout for takeoff and check

                self.get_logger().error('Takeoff timeout exceeded') # Log takeoff failure

                return False
            
            rclpy.spin_once(self) # Process incoming messages

        return False

    #######################################################
    def flyInCircle(self, x, y, z):  # Define the fly_in_circle method

        setpoint = PositionTarget()  # Create a PositionTarget message

        setpoint.coordinate_frame = PositionTarget.FRAME_LOCAL_NED  # Set the coordinate frame

        setpoint.type_mask = PositionTarget.IGNORE_VX | PositionTarget.IGNORE_VY | PositionTarget.IGNORE_VZ | PositionTarget.IGNORE_AFX | PositionTarget.IGNORE_AFY | PositionTarget.IGNORE_AFZ  # Set the type mask to ignore velocities and accelerations

        for i in range(1, 101):  # Loop 100 times to create a circular path

            self.des_x = float(x + 1 * math.cos(math.radians(i * 3.6)))  # Calculate the desired x position

            self.des_y = float(y + 1 * math.sin(math.radians(i * 3.6)))  # Calculate the desired y position

            self.des_z = float(z)  # Calculate the desired z position

            setpoint.position.x = self.des_x  # Set the desired position in the setpoint message

            setpoint.position.y = self.des_y  # Set the desired y position in the setpoint message

            setpoint.position.z = self.des_z  # Set the desired z position in the setpoint message

            self.pose_pub.publish(setpoint)  # Publish the setpoint message

            while rclpy.ok() and self.distance() > 0.1:  # Loop until ROS is shut down or the distance is within the threshold

                rclpy.spin_once(self)  # Process incoming messages

                self.get_logger().info(f"Current distance to setpoint: {self.distance()} meters")

        # Return to center
        self.des_x = 0.0  # Calculate the desired x position

        self.des_y = 0.0  # Calculate the desired y position

        self.des_z = 1.0  # Calculate the desired z position

        setpoint.position.x = self.des_x  # Set the desired position in the setpoint message

        setpoint.position.y = self.des_y  # Set the desired y position in the setpoint message

        setpoint.position.z = self.des_z  # Set the desired z position in the setpoint message

        self.pose_pub.publish(setpoint)  # Publish the setpoint message

        while rclpy.ok() and self.distance() > 0.1:  # Loop until ROS is shut down or the distance is within the threshold

            rclpy.spin_once(self)  # Process incoming messages

            self.get_logger().info(f"Current distance to setpoint: {self.distance()} meters")


    #######################################################

    def distance(self):  # Define the distance method

        dx = self.curr_x - self.des_x  # Calculate the difference in x position

        dy = self.curr_y - self.des_y  # Calculate the difference in y position

        dz = self.curr_z - self.des_z  # Calculate the difference in z position

        return math.sqrt(dx * dx + dy * dy + dz * dz)  # Return the Euclidean distance

###########################################################

def main(args=None): # Define the main script 

    rclpy.init(args=args) # initalize rclpy

    controller = DroneController() # Create an instance of DroneController

    if not controller.connect(): # Connect to MAVROS
        controller.get_logger().error('Exiting...')
        return

    if not controller.set_mode('GUIDED'): # Set the mode to GUIDED
        controller.get_logger().error('Exiting...')
        return

    if not controller.arm(True): # Arm the drone
        controller.get_logger().error('Exiting...')
        return
    

    if not controller.takeoff(1.0): # Takeoff 1 metre
        controller.get_logger().error('Exiting...')
        return

    controller.flyInCircle(controller.curr_x, controller.curr_y, controller.curr_z) # Fly in a circular path

    if not controller.set_mode('LAND'): # Land the drone
        controller.get_logger().error('Exiting...')
        return

    rclpy.shutdown()

if __name__ == '__main__':
    main() # Execure the main script
