import numpy as np
import math
import pandas as pd
import matplotlib.pyplot as plt

K = 1 

def f(t, y, v):
    return -math.sin(y) -K * abs(v) * v 

# Parámetros iniciales
y0 = math.pi+0.1  # Condición inicial para y
v0 = -1  # Condición inicial para v (dy/dt)
t0 = 0  # Tiempo inicial
tf = 20*math.pi  # Tiempo final
N = 1000000
h = (tf - t0) / N  # Paso de tiempo

print(h)
# Creación de arrays para almacenar los resultados
t = np.linspace(t0, tf, N)
y = np.zeros(len(t))
v = np.zeros(len(t))
d = list()

# Inicialización de los primeros elementos
y[0] = y0
v[0] = v0
d.append([t[0], y[0], v[0]])

#Método de Euler para actualizar y y v
for i in range(1, len(t)):
    y[i] = y[i-1] + h * v[i-1]
    v[i] = v[i-1] + h * f(t[i-1], y[i-1], v[i-1])

    d.append([t[i], y[i], v[i]])

df = pd.DataFrame(d, columns=["t", "theta", "omega"])
print(df)

#Gráfica de los resultados
print(f"theta({t[-1]}) = {y[-1]}")
plt.plot(t, y, label='theta(t)')
plt.plot(t, v, label='omega(t)')
plt.title("Euler")
plt.xlabel('Tiempo')
plt.ylabel('Valores')
plt.legend()
plt.show()