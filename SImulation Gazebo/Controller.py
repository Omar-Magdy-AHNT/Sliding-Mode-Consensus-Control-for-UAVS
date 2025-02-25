import rclpy  # Import the rclpy library for ROS2 functionalities
from rclpy.node import Node  # Import Node class for creating ROS2 nodes
from rclpy.qos import QoSProfile, ReliabilityPolicy, HistoryPolicy
from mavros_msgs.srv import CommandBool, SetMode, CommandTOL  # Import required services from mavros_msgs
from mavros_msgs.msg import State, PositionTarget  # Import required messages from mavros_msgs
from geometry_msgs.msg import PoseStamped, Point, TwistStamped, AccelStamped, Vector3# Import PoseStamped message from geometry_msgs
import math  # Import the math module for mathematical functions
import time  # Import time module to add delays where necessary
import numpy as np

class DroneController(Node):

    def __init__(self, drone_name):
        super().__init__(f'{drone_name}_controller')  # Set unique node name for each drone
        self.current_state = State()
        self.arm_state = False
        self.drone_name = drone_name
        self.rate = self.create_rate(50)

        #######################################################

        # Define QoS settings
        qos_profile = QoSProfile(
            history=HistoryPolicy.KEEP_LAST,
            depth=10,
            reliability=ReliabilityPolicy.BEST_EFFORT
        )

        # ROS subscribers
        self.acc = self.create_subscription(
        AccelStamped,
        f'{drone_name}/local_position/acceleration',
        self.acceleration_callback,
        qos_profile
        )
        self.d1vel = self.create_subscription(
        TwistStamped,
        f'{drone_name}/local_position/velocity_local',
        self.velocity_callback,
        qos_profile
        )    
        self.pose = self.create_subscription(
            PoseStamped, 
            f'{drone_name}/local_position/pose',  # Topic for each drone's pose
            self.pose_callback, 
            qos_profile)
        self.state = self.create_subscription(
            State, 
            f'{drone_name}/state',  # Topic for each drone's state
            self.state_callback, 
            qos_profile)

        self.get_logger().info(f'{drone_name} Subscriptions initialized')

        # ROS publishers
        self.pose_pub = self.create_publisher(PositionTarget, 'drone2/setpoint_raw/local', qos_profile) # Create a publisher for setpoints

        self.get_logger().info('Publishers initialized') #Log when publishers are initilaized

        #######################################################

        # ROS services
        self.set_mode_client = self.create_client(SetMode, 'drone2/set_mode') # Create a service client for setting the mode

        self.arming_client = self.create_client(CommandBool, 'drone2/cmd/arming') # Create a service client for arming/disarming

        self.takeoff_client = self.create_client(CommandTOL, 'drone2/cmd/takeoff') # Create a service client for takeoff

        self.get_logger().info('Services initialized') #Log when services are initilaized

        #######################################################

        self.curr_x = 0.0
        self.curr_y = 0.0
        self.curr_z = 0.0
        self.cur_vx = 0.0
        self.cur_vy = 0.0
        self.cur_vz = 0.0
        self.cur_ax = 0.0
        self.cur_ay = 0.0
        self.cur_az = 0.0
        self.des_x = 0.0
        self.des_y = 0.0
        self.des_z = 0.0
        self.des_vx = 0.0
        self.des_vy = 0.0
        self.des_vz = 0.0
        self.des_ax = 0.0
        self.des_ay = 0.0
        self.des_az = 0.0

    #######################################################

    def state_callback(self, state):
        self.current_state = state
        self.get_logger().info(f"{self.drone_name} Received state update: {state}")

    #######################################################

    def pose_callback(self, msg: PoseStamped):
        self.get_logger().info(f'{self.drone_name} Pose callback triggered')
        self.curr_x = msg.pose.position.x
        self.curr_y = msg.pose.position.y
        self.curr_z = msg.pose.position.z  # Altitude is in the z-coordinate of PoseStamped
        #self.get_logger().info(f'{self.drone_name} Received Pose update: x={self.curr_x}, y={self.curr_y}, z={self.curr_z}')

    #######################################################

    def velocity_callback(self,msg: TwistStamped):
        self.get_logger().info(f'{self.drone_name} vel callback triggered')
        self.curr_vx = msg.twist.linear.x
        self.curr_vy = msg.twist.linear.y
        self.curr_vz = msg.twist.linear.z  # Altitude is in the z-coordinate of PoseStamped
        #self.get_logger().info(f'{self.drone_name} Received Vel update: vx={self.curr_vx}, vy={self.curr_vy}, vz={self.curr_vz}')

    ################################################

    def acceleration_callback(self,msg: AccelStamped):
        self.get_logger().info(f'{self.drone_name} Acc callback triggered')
        self.curr_ax = msg.accel.linear.x
        self.curr_ay = msg.accel.linear.y
        self.curr_az = msg.accel.linear.z  # Altitude is in the z-coordinate of PoseStamped
        #self.get_logger().info(f'{self.drone_name} Received Acc update: ax={self.curr_ax}, ay={self.curr_ay}, az={self.curr_az}')

    #######################################################

    def connect(self):
        while rclpy.ok() and not self.current_state.connected:
            self.get_logger().info(f'{self.drone_name} Waiting for connection to MAVROS...')
            rclpy.spin_once(self)
        if self.current_state.connected:
            self.get_logger().info(f'{self.drone_name} Connected to MAVROS!')
            return True
        else:
            self.get_logger().error(f'{self.drone_name} Failed to connect to MAVROS!')
            return False

    #######################################################

    def set_mode(self, mode):
        req = SetMode.Request()
        req.custom_mode = mode
        future = self.set_mode_client.call_async(req)
        
        start_time = self.get_clock().now()
        while rclpy.ok():
            if self.current_state.mode == mode:
                self.get_logger().info(f'{self.drone_name} Mode changed to {mode}')
                return True
            if (self.get_clock().now() - start_time).to_msg().sec > 5.0:
                self.get_logger().error(f'{self.drone_name} Failed to set mode to {mode}')
                return False
            rclpy.spin_once(self)

    #######################################################

    def arm(self, arm: bool):
        req = CommandBool.Request()
        req.value = arm
        future = self.arming_client.call_async(req)
        
        start_time = self.get_clock().now()
        while rclpy.ok():
            if self.current_state.armed == arm:
                if arm:
                    self.get_logger().info(f'{self.drone_name} Vehicle armed!')
                else:
                    self.get_logger().info(f'{self.drone_name} Vehicle disarmed!')
                return True
            if (self.get_clock().now() - start_time).to_msg().sec > 5.0:
                self.get_logger().error(f'{self.drone_name} Failed to arm vehicle!')
                return False
            rclpy.spin_once(self)

    #######################################################



    def send_position_velocity(self, x, y, z, vx, vy, vz,ax,ay,az):
        """
        Send position and velocity to the drone using PositionTarget message, ignoring acceleration.
        """
        setpoint = PositionTarget()
        
        # Use local NED frame for position and velocity
        setpoint.coordinate_frame = PositionTarget.FRAME_LOCAL_NED
        
        # Set type_mask to ignore acceleration (only include position and velocity)
        setpoint.type_mask = 0
        
        # Set position (x, y, z)
        setpoint.position = Point(x=x, y=y, z=z)
        
        # Set velocity (vx, vy, vz)
        setpoint.velocity = Vector3(x=vx, y=vy, z=vz)

        setpoint.acceleration_or_force = Vector3(x=ax, y=ay, z=az)
        # Publish the setpoint to mavros
        self.pose_pub.publish(setpoint)



    #######################################################

    def takeoff(self, altitude):
        req = CommandTOL.Request()
        req.altitude = altitude
        future = self.takeoff_client.call_async(req)
        
        self.get_logger().info(f'{self.drone_name} Sending takeoff command to {altitude} meters...')
        
        start_time = self.get_clock().now()
        while rclpy.ok():
            if abs(self.curr_z - altitude) <= 0.3:  # Check if the current altitude is within 0.3 meters of target
                self.get_logger().info(f'{self.drone_name} Reached desired altitude {altitude:.2f} meters')
                return True
            if (self.get_clock().now() - start_time).to_msg().sec > 20.0:  # Increased timeout to 20 seconds
                self.get_logger().error(f'{self.drone_name} Takeoff timeout exceeded. Current altitude: {self.curr_z}')
                return False
            rclpy.spin_once(self)
        return False

    #######################################################

    def wait_for_condition(self, condition, timeout=10):
        start_time = self.get_clock().now()
        while rclpy.ok():
            if condition():
                return True
            if (self.get_clock().now() - start_time).to_msg().sec > timeout:
                self.get_logger().error(f'{self.drone_name} Condition not met in time.')
                return False
            rclpy.spin_once(self)

    #######################################################

    def controller(self, d1):
        setpoint = PositionTarget()  # Create a PositionTarget message

        setpoint.coordinate_frame = PositionTarget.FRAME_LOCAL_NED  # Set the coordinate frame
        setpoint.type_mask = 0
        kp = 0.8929
        kv = ka=0.5522
        d = np.array([1, 1, 0])

        while d1.current_state.mode != 'GUIDED':
            rclpy.spin_once(self)
            self.get_logger().info('Waiting for Leader to enter GUIDED mode...')

        if not self.set_mode('GUIDED'):  
            self.get_logger().error('Failed to set Follower to GUIDED mode')
            return

        while not d1.current_state.armed:
            rclpy.spin_once(self)
            self.get_logger().info('Waiting for Leader to arm...')

        if not self.arm(True):  
            self.get_logger().error('Failed to arm Follower')
            return

        if not self.takeoff(1.0):  
            self.get_logger().error('Follower Takeoff failed')
            return
        
        # Control loop (this is where the dynamic listening happens)
        while rclpy.ok() and d1.current_state.connected and d1.current_state.mode != 'LAND':

            # Dynamically get new values in each loop iteration (latest values)
            x2, y2, z2 = self.curr_x, self.curr_y, self.curr_z
            p2 = np.array([x2, y2, z2])
            vx2, vy2, vz2 = self.cur_vx, self.cur_vy, self.cur_vz
            v2 = np.array([vx2, vy2, vz2])
            ax2, ay2, az2 = self.cur_ax, self.cur_ay, self.cur_az
            a2 = np.array([ax2, ay2, az2])

            x1, y1, z1 = d1.curr_x, d1.curr_y, d1.curr_z
            p1 = np.array([x1, y1, z1])
            vx1, vy1, vz1 = d1.cur_vx, d1.cur_vy, d1.cur_vz
            v1 = np.array([vx1, vy1, vz1])
            ax1, ay1, az1 = d1.cur_ax, d1.cur_ay, d1.cur_az
            a1 = np.array([ax1, ay1, az1])
            self.get_logger().info(f'{self.drone_name} Received Pose update: x={x2}, y={y2}, z={z2}')
            d1.get_logger().info(f'{d1.drone_name} Received Pose update: x={x1}, y={y1}, z={z1}')
            # Calculate control commands for current state
            unp = (-kp * (p2 - p1)) - (0.1 * abs(p2 - p1) * np.sign(p2 - p1)) + p1 
            unv = (-kv * (v2 - v1) )- (0.1 * abs(v2 - v1) * np.sign(v2 - v1)) + v1
            una = (-ka * (a2 - a1) )- (0.1 * abs(a2 - a1) * np.sign(a2 - a1)) + a1

            # Send control commands (position, velocity, acceleration)
            setpoint.position.x = unp[0]
            setpoint.position.y = unp[1]
            setpoint.position.z = unp[2]
            setpoint.velocity.x = unv[0]
            setpoint.velocity.y = unv[1]
            setpoint.velocity.z = unv[2]
            setpoint.acceleration_or_force.x = una[0]
            setpoint.acceleration_or_force.y = una[1]
            setpoint.acceleration_or_force.z = una[2]
            self.pose_pub.publish(setpoint)  # Publish the setpoint message
            # If all values are within 0.1, break the loop
            # while rclpy.ok() and self.distance() > 0.1:  # Loop until ROS is shut down or the distance is within the threshold
            rclpy.spin_once(self)
            rclpy.spin_once(d1)  # Process incoming messages
            # self.get_logger().info(f"Current distance to setpoint: {self.distance()} meters")

        # Once the condition is met, set the mode to LAND to safely land the drone
        if not self.set_mode('LAND'):  
            self.get_logger().error('Exiting...')
            return

    #######################################################

    # def distance(self):  # Define the distance method

    #     dx = self.curr_x - self.des_x  # Calculate the difference in x position

    #     dy = self.curr_y - self.des_y  # Calculate the difference in y position

    #     dz = self.curr_z - self.des_z  # Calculate the difference in z position

    #     return math.sqrt(dx * dx + dy * dy + dz * dz)  # Return the Euclidean distance


    #######################################################

def main(args=None):  # Define the main function
    rclpy.init(args=args)  # Initialize rclpy

    controller_drone1 = DroneController(drone_name="mavros")  # Create an instance for drone 1
    controller_drone2 = DroneController(drone_name="drone2")  # Create an instance for drone 2


    if not controller_drone2.connect():  
        controller_drone2.get_logger().error('Exiting...')
        return

    while not controller_drone1.current_state.connected:
        controller_drone1.get_logger().info('Waiting for Leader to connect...')
        rclpy.spin_once(controller_drone1)  # Process one event cycleg

    # Once connected, log that the drone is connected
    controller_drone1.get_logger().info('Leader is connected!')

    controller_drone2.controller(controller_drone1)
    
    rclpy.shutdown()  # Shutdown rclpy to end the program

if __name__ == '__main__':
    main()