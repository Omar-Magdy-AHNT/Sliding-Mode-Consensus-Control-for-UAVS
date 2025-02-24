function [xdes, xdesdot,comp] = circle(t,pos)
    % Fixed omega and Vz %
    % Define the main parameters of the helix
    % w = 3.0;
    % Vz = 1.0;
    % r = 1.0;
    persistent spos;
    if isempty(spos)
        spos = pos;
        
    end
    comp = false;
    %xdes = [phi p theta q psi r x xdot y ydot z zdot]
    xdes = [0 0 0 0 0 0 spos(7)+cos(t) -sin(t) spos(9)+sin(t) cos(t) spos(11) 0]';
    xdesdot = [0 0 0 0 0 0 -sin(t) -cos(t) cos(t) -sin(t) 0 0]';
    if t >= 27
        comp = true;
    end
end