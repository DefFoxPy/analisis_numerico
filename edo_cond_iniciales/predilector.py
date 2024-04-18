import numpy as np
import pandas as pd
import math
import matplotlib.pyplot as plt

K = 1

def f1(t, y1, y2):
    return y2

def f2(t, y1, y2):
    return -math.sin(y1) -K * abs(y2) * y2   

def predictor_corrector(y1_0, y2_0, t0, tf, N):
    h = (tf - t0) / N  # Paso de tiempo
    t = np.linspace(t0, tf, N+1)
    y1 = np.zeros(N+1)
    y2 = np.zeros(N+1)
    y1[0], y2[0] = y1_0, y2_0  # Condiciones iniciales

    d = list()
    d.append([t[0], y1[0], y2[0]])

    # Inicialización con Runge-Kutta de cuarto orden
    for i in range(3):
        k1 = h * f1(t[i], y1[i], y2[i])
        l1 = h * f2(t[i], y1[i], y2[i])
        
        k2 = h * f1(t[i] + h/2, y1[i] + k1/2, y2[i] + l1/2)
        l2 = h * f2(t[i] + h/2, y1[i] + k1/2, y2[i] + l1/2)
        
        k3 = h * f1(t[i] + h/2, y1[i] + k2/2, y2[i] + l2/2)
        l3 = h * f2(t[i] + h/2, y1[i] + k2/2, y2[i] + l2/2)
        
        k4 = h * f1(t[i] + h, y1[i] + k3, y2[i] + l3)
        l4 = h * f2(t[i] + h, y1[i] + k3, y2[i] + l3)
        
        y1[i+1] = y1[i] + (k1 + 2*k2 + 2*k3 + k4) / 6
        y2[i+1] = y2[i] + (l1 + 2*l2 + 2*l3 + l4) / 6
        
        d.append([t[i+1], y1[i+1], y2[i+1]])


    # Predictor-Corrector
    for i in range(3, N):
        # Predictor (Adams-Bashforth de tercer orden)
        y1_pred = y1[i] + h * (23*f1(t[i], y1[i], y2[i]) - 16*f1(t[i-1], y1[i-1], y2[i-1]) + 5*f1(t[i-2], y1[i-2], y2[i-2])) / 12
        y2_pred = y2[i] + h * (23*f2(t[i], y1[i], y2[i]) - 16*f2(t[i-1], y1[i-1], y2[i-1]) + 5*f2(t[i-2], y1[i-2], y2[i-2])) / 12

        y1[i+1] = y1[i] + h * (5*f1(t[i+1], y1_pred, y2_pred) + 8*f1(t[i], y1[i], y2[i]) - f1(t[i-1], y1[i-1], y2[i-1])) / 12
        y2[i+1] = y2[i] + h * (5*f2(t[i+1], y1_pred, y2_pred) + 8*f2(t[i], y1[i], y2[i]) - f2(t[i-1], y1[i-1], y2[i-1])) / 12

        d.append([t[i+1], y1[i+1], y2[i+1]])
    
    df = pd.DataFrame(d, columns=["t", "theta", "omega"])
    print(df)

    return t, y1, y2

t, y1, y2 = predictor_corrector(math.pi+0.1, -1, 0, 20*math.pi, 2000)  # Ajustar según el problema

#Gráfica de los resultados
print(f"predi theta({t[-1]}) = {y1[-1]}")
plt.plot(t, y1, label='y(t)')
plt.plot(t, y2, label='v(t)')
plt.title("Predictor-corrector")
plt.xlabel('Tiempo')
plt.ylabel('Valores')
plt.legend()
plt.show()