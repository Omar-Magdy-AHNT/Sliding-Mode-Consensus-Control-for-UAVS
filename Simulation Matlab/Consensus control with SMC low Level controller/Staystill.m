function [xdes, xdesdot] = Staystill(t,pos)
persistent spos; % Persistent variable to store the initial position

    %If it's the first call, save the initial position
    if isempty(spos)
        spos = pos;
        
    end

    xdes = [0 0 0 0 0 0 spos(7) 0 spos(9) 0 spos(11) 0]';
    xdesdot = [0 0 0 0 0 0 0 0 0 0 0 0]';

end