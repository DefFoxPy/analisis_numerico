import numpy as np
import math
import matplotlib.pyplot as plt

# Parámetros dados
L = 50  # Longitud del cable en metros
T = 5000  # Tensión en kg
n = 10  # Número de intervalos
h = L / n  # Tamaño del paso

# Función que resuelve un sistema de ecu lineal con una variante de la eliminación de gauss
def tridg(a, b, c, d, n):
    for i in range(1, n):
        r = a[i] /   b[i-1]
        b[i] = b[i] - r * c[i-1]
        d[i] = d[i] - r * d[i-1]

    d[n-1] = d[n-1] / b[n-1]

    for i in range(n-2, -1, -1):
        d[i] = (d[i] - c[i] * d[i+1]) / b[i]

    return d

# gauss con pivoteo
def gauss_pivoteo(A, b):
    n = len(b)
    M = A.copy()
    y = b.copy()
    
    for k in range(n-1):
        # Pivoteo parcial
        maxindex = abs(M[k:,k]).argmax() + k
        if M[maxindex, k] == 0:
            raise ValueError("La matriz es singular.")
        # Intercambiar filas
        if maxindex != k:
            M[[k,maxindex]] = M[[maxindex, k]]
            y[[k,maxindex]] = y[[maxindex, k]]
        
        # Eliminación hacia adelante
        for row in range(k+1, n):
            multiplier = M[row,k]/M[k,k]
            M[row, k:] = M[row, k:] - multiplier*M[k, k:]
            y[row] = y[row] - multiplier*y[k]
    
    # Sustitución hacia atrás
    x = np.zeros(n)
    for k in range(n-1, -1, -1):
        x[k] = (y[k] - np.dot(M[k,k+1:], x[k+1:])) / M[k,k]
    
    return x

# Función para la distribución de carga w(x)
def w(x):
    return 20 * (1 + np.exp(x / 25))

# Construir la matriz A y el vector b del sistema de ecuaciones lineales 
A = np.zeros((n-1, n-1))
B = np.zeros(n-1)

a = np.zeros(n-1) # sub diagonal
b = np.zeros(n-1) # diagonal principal
c = np.zeros(n-1) # superdiagonal

for i in range(n-1):
    x_i = (i + 1) * h
    if i > 0:
        A[i, i-1] = 1
        a[i] = 1
    A[i, i] = -2
    b[i] = -2
    if i < n-2: 
        A[i, i+1] = 1
        c[i] = 1
    B[i] = -h**2 * w(x_i) / T

# Resolver el sistema de ecuaciones lineales para obtener los desplazamientos y
y = tridg(a, b, c, B, n-1)
#y = gauss_pivoteo(A, B)

# Agregar los desplazamientos en los extremos
y = np.insert(y, 0, 0)
y = np.append(y, 0)

# Generar los puntos x de la retícula
x = np.linspace(0, L, n+1)

# Cálculando la longitud del cable después de aplicarle la carga w(x)
l = 0
for i in range(1, len(x)):
    l += math.sqrt(math.pow(x[i] - x[i-1], 2) + math.pow(y[i] - y[i-1], 2))

print (l)

# Graficar la forma del cable
plt.plot(x, y, '-o')
plt.title(f'Forma del cable n ={n}')
plt.xlabel('x (m)')
plt.ylabel('y (m)')
plt.grid(True)
plt.show()