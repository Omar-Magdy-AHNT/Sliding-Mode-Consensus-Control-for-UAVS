function correction_rate = sqrt_controller(err, p, second_ord_lim, dt)
% The square root controller
% Code is taken from sqrt_controller(...) in AC_PosControl.cpp.

if (second_ord_lim < 0 || second_ord_lim == 0)
   correction_rate = err * p;
elseif (p == 0)
    % P term is zero, but second order limit is positive
    if (err > 0)
        correction_rate = sqrt(2.0 * second_ord_lim * err);
    elseif (err < 0)
        correction_rate = sqrt(2.0 * second_ord_lim * -err);
    else
        correction_rate = 0.0;
    end
else
    % P term and second order limit are positive, hence have been defined
    linear_dist = second_ord_lim / (p * p);
    % Check if error exceeds linear range of controller gain
    if (err > linear_dist)
        correction_rate = sqrt(2.0 * second_ord_lim * ( err - (linear_dist / 2.0) ));
    elseif (err < -linear_dist)
        correction_rate = -sqrt(2.0 * second_ord_lim * ( -err - (linear_dist / 2.0) ));
    else
        % Return linearly amplified correction if error is in linear range
        correction_rate = err * p;
    end
end

% Prevent oscillations by over-shooting the error correction in the last
% time step
if (dt ~= 0)
    correction_rate = max( min(correction_rate, abs(err) / dt), -abs(err) / dt);
end

