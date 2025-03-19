% Custom saturation function
function saturatedValue = saturate(value, boundary_thickness)
    saturatedValue = max(min(value/boundary_thickness, 1.0), -1.0);
end
