import numpy as np
import math
import pandas as pd
import matplotlib.pyplot as plt

PI = math.pi
K = 1 # parametro del sistema
 
def rk4_system(dydx, dvdx, x0, y0, v0, h, n):
    """
    Resuelve un sistema de EDOs de primer orden usando el método RK4.

    dydx: Derivada de y respecto a x.
    dvdx: Derivada de v respecto a x (segunda derivada de y respecto a x).
    x0, y0, v0: Condiciones iniciales.
    h: Tamaño del paso.
    n: Número de pasos.
    """
    x = x0
    y = y0
    v = v0

    d = list()  

    for i in range(n):
        k1_y = h * dydx(x, y, v)
        k1_v = h * dvdx(x, y, v)

        k2_y = h * dydx(x + 0.5*h, y + 0.5*k1_y, v + 0.5*k1_v)
        k2_v = h * dvdx(x + 0.5*h, y + 0.5*k1_y, v + 0.5*k1_v)

        k3_y = h * dydx(x + 0.5*h, y + 0.5*k2_y, v + 0.5*k2_v)
        k3_v = h * dvdx(x + 0.5*h, y + 0.5*k2_y, v + 0.5*k2_v)

        k4_y = h * dydx(x + h, y + k3_y, v + k3_v)
        k4_v = h * dvdx(x + h, y + k3_y, v + k3_v)

        y += (k1_y + 2*k2_y + 2*k3_y + k4_y) / 6
        v += (k1_v + 2*k2_v + 2*k3_v + k4_v) / 6
        x += h
 
        d.append([x, y, v])

    df = pd.DataFrame(d, columns=["t", "theta", "omega"])
    print(df)
    #print(df.loc[1000])

    return x, y, v, d

def dydx(x, y, v):
    return v

def dvdx(x, y, v):
    return -math.sin(y) -K * abs(v) * v 

intervalos = 2000

x0, y0, v0 = 0, PI+0.1, -1  # Condiciones iniciales
xf = 20*PI  # tiempo final
h = (xf - x0) / intervalos   # Tamaño del paso
n = intervalos  # Número de pasos

x, y, v, d = rk4_system(dydx, dvdx, x0, y0, v0, h, n)
print(f"Solución aproximada: theta({x}) = {y}")
print(f"Solución aproximada: omega({x}) = {v}")

t = list()
y = list()
v = list()
for i in d:
    t.append(i[0])
    y.append(i[1])
    v.append(i[2])


plt.plot(t, y, label='theta(t)')
plt.plot(t, v, label='omega(t)')
plt.title("runge-kutta")
plt.xlabel('Tiempo')
plt.ylabel('Valores')
plt.legend()
plt.show()