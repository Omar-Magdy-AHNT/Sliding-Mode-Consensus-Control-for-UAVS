function [xdes, xdesdot,comp] = Takeoff(t,pos)
persistent spos; % Persistent variable to store the initial position

    %If it's the first call, save the initial position
    if isempty(spos)
        spos = pos;
        
    end
    comp = false;
    xdes = [0 0 0 0 0 0 spos(7) 0 spos(9) 0 0.5*t 0.5]';
    xdesdot = [0 0 0 0 0 0 0 0 0 0 0.5 0]';
    if 0.5*t >= 3
        comp = true;
    end
end