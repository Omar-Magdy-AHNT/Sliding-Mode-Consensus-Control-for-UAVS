function [xdes, xdesdot, comp] = Land(t, current_position)
    % LandingTrajectory generates a smooth landing trajectory for the drone.
    % 
    % Inputs:
    % - t: Current time (discrete or continuous)
    % - current_position: Current position vector [x, xdot, y, ydot, z, zdot]
    % 
    % Outputs:
    % - xdes: Desired state vector [phi, p, theta, q, psi, r, x, xdot, y, ydot, z, zdot]
    % - xdesdot: Desired state derivative vector
    % - comp: Completion flag (true if landing is complete)

    % Extract initial position and velocity
    x0 = current_position(1); % Initial x position
    y0 = current_position(3); % Initial y position
    z0 = current_position(5); % Initial z position
    landing_time = 10;  % Define landing time (seconds)

    % Desired horizontal position remains constant during landing
    x = x0;
    y = y0;

    % Ensure t is within bounds
    t_clamped = max(0, min(t, landing_time));

    % Linear descent for vertical position (z)
    z = z0 - (z0 * t_clamped / landing_time);  % Linear descent profile
    
    % Linear descent for vertical velocity (zdot)
    zdot = -z0 / landing_time;  % Constant rate of descent

    % Horizontal velocities remain zero (no horizontal movement)
    xdot = 0;
    ydot = 0;

    % Completion flag (landing completed when time reaches or exceeds landing time)
    comp = z <= 0.1;

    % Desired state and derivative vectors
    xdes = [0 0 0 0 0 0 x xdot y ydot z zdot]';
    xdesdot = [0 0 0 0 0 0 0 0 0 0 zdot 0]';
end
