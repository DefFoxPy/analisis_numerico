function dxdt = pendulum_rhs(x, k)

theta = x(1);
omega = x(2);

dtheta = omega;
domega = -sin(theta) -k * abs(omega) *omega;

dxdt = [dtheta; domega];

end