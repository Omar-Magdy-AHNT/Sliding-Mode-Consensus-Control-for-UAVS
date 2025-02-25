function [xdes, xdesdot,comp] = Helical(t)
    % Fixed omega and Vz %
    % Define the main parameters of the helix
    % w = 3.0;
    % Vz = 1.0;
    % r = 1.0;
    comp = false;
    %xdes = [phi p theta q psi r x xdot y ydot z zdot]
    xdes = [0 0 0 0 0 0 cos(t) -sin(t) sin(t) cos(t) t*0.5 0.5]';
    xdesdot = [0 0 0 0 0 0 -sin(t) -cos(t) cos(t) -sin(t) 0.5 0]';
    if t*0.5 >5
        comp = true;
    end
end