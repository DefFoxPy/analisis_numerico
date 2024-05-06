import numpy as np
import matplotlib.pyplot as plt

L = 100.0  # longitud del río en metros
T = 24.0   # tiempo total de simulación en horas
D = 0.01   # coeficiente de difusión m^2/h
ka = 0.10   # tasa de absorción /h
kd = 0.05  # tasa de desorción /h
Cs = 10.0  # concentración del contaminante en el lecho del río mg/L

# Parámetros de la discretización
Nx = 10    # número de segmentos espaciales
Nt = 24    # número de pasos temporales
h = L / Nx
dt = T / Nt

# Inicialización de la matriz de concentracionesz
C = np.zeros((Nx+1, Nt+1))  # Nx+1 para incluir ambos extremos

# Condiciones iniciales de frontera
#C[4, 0] = 10
#for i in range(0, Nx+1):
#    C[i, 0] = 4

# Iteración temporal
for n in range(0, Nt):
    for i in range(1, Nx):
        C[i, n+1] = C[i, n] + dt * (D * (C[i+1, n] - 2*C[i, n] + C[i-1, n]) / h**2 - ka * C[i, n] + kd * Cs)
    # Condiciones de Neumann en los extremos
    C[0, n+1] = C[1, n+1]
    C[Nx, n+1] = C[Nx-1, n+1]

for i in range(len(C)):
    for j in range(len(C[i])):
        print(round(C[i, j], 2), end=' ')
    print()


# Visualización de los resultados
plt.imshow(C, extent=[0, T, 0, L], origin='lower', aspect='auto', cmap='hot')
plt.colorbar(label='Concentración de contaminante (mg/L)')
plt.xlabel('Tiempo (h)')
plt.ylabel('Posición a lo largo del río (m)')
plt.title('Distribución de la concentración de contaminante en el río')
plt.show()