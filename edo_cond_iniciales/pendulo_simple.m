clear variables; close all; clc
syms s
% parametros
k = 1;

% funcion f(t,x)
f = @(t,x) pendulum_rhs(x, k);

% tiempo de discretización
ti = 0; tf = 20*pi;
t = linspace(ti, tf, 2000);

% condiciones iniciales
x0 = [pi+0.1; -1];

% resolver dx/dt = f(t,x)
[~, X] = ode45(f, t, x0);
X = X';

Ttheta = [t; X(1,:)]
Ttheta
Tomega = [t; X(2,:)]
Tomega

% grafica
figure ('IntegerHandle', 'off', 'position', [50 50 1280/2 720/2])
set(gcf, ...
    'defaultTextInterpreter', 'Latex', ...
    'defaultAxesFontSize', 18, ...
    'defaultLineLineWidth', 3)
%subplot(1, 2, 1)
%plot(X(1,:), X(2,:), 'g')
%xlabel('$\theta$'); ylabel('$\omega$')

subplot(1, 2, 1)
plot(t, X(1,:), 'r')
xlabel('$t$'); ylabel('$\theta$'); 

subplot(1, 2, 2)
plot(t, X(2,:), 'r')
xlabel('$t$'); ylabel('$\omega$');