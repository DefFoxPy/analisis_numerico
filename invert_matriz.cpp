/*
Invertir una matriz con el método de gaus jordan
*/
#include <iostream>
#include <vector>
#include <cmath>
#include <limits>
#include <iomanip>

using namespace std;

const double EPS = numeric_limits<double>::epsilon(); // epsilon de la máquina
const int L = 15; // para fines de mostrar la matriz

void printMatriz(const vector<vector<double>>& matriz) {
    cout.setf(ios::scientific);
    for (int i = 0; i < matriz.size(); i++) {
        for (int j = 0; j < matriz[i].size(); j++) {
            cout << setw(L) << matriz[i][j];
        }
        cout << endl;
    }
    cout << endl;
    cout.unsetf(ios::scientific);
}

// Función para invertir una matriz usando la eliminación de Gauss-Jordan
// y calcular su determinante para verificar si es singular.
pair<vector<vector<double>>, double> invertmatrizWithDeterminant(const vector<vector<double>>& matriz) {
    int n = matriz.size();
    double det = 1.0; // Inicialización del determinante
    vector<vector<double>> inverse(n, vector<double>(n, 0.0));

    // Inicializar la matriz inversa como una matriz identidad
    for (int i = 0; i < n; ++i) {
        inverse[i][i] = 1.0;
    }

    // Crear una copia de la matriz original para no modificarla
    vector<vector<double>> temp = matriz;

    // Aplicar la eliminación de Gauss-Jordan
    for (int i = 0; i < n; ++i) {
        // Buscar el pivote
        double pivotValue = temp[i][i];
        if (fabs(pivotValue) < EPS) {
            det = 0.0; // El determinante es cero, por lo tanto, la matriz es singular.
            break;
        }
        // Multiplicar el determinante por el valor del pivote
        det *= pivotValue;

        // Normalizar la fila del pivote
        for (int j = 0; j < n; ++j) {
            temp[i][j] /= pivotValue;
            inverse[i][j] /= pivotValue;
        }

        // Hacer ceros por encima y por debajo del pivote
        for (int k = 0; k < n; ++k) {
            if (k != i) { // No modificar la fila del pivote
                double factor = temp[k][i];
                for (int j = 0; j < n; ++j) {
                    temp[k][j] -= factor * temp[i][j];
                    inverse[k][j] -= factor * inverse[i][j];
                }
            }
        }
    }

    return make_pair(inverse, det);
}

int main() {
    vector<vector<double>> matriz = {
        {2, 1, -3},
        {-1, 3, 2},
        {3, 1, -3}
    };
    cout << "Matriz Original" << endl;
    printMatriz(matriz);

    // Invertir la matriz y calcular el determinante
    auto [inverseMatriz, determinant] = invertmatrizWithDeterminant(matriz);

    if (determinant != 0.0) {
        // Imprimir la matriz invertida
        cout << "Matriz Invertida:" << endl;
        printMatriz(inverseMatriz);
    } else {
        cout << "La matriz es singular y no tiene inversa." << endl;
    }

    // Imprimir el determinante
    cout << "Determinante: " << determinant << endl;
    cout << "Epsilon de la maquina: " << EPS << endl;

    return 0;
}