#include <iostream>
#include <vector>
#include <iomanip>
#include <limits>
using namespace std;

const int L = 15; // para fines de mostrar la matriz
const double EPS = numeric_limits<double>::epsilon(); // epsilon de la máquina

void swapRows(vector<vector<double>>& mat, int row1, int row2) {
    int cols = mat[0].size();
    for (int i = 0; i < cols; i++) {
        swap(mat[row1][i], mat[row2][i]);
    }
}

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

int luDecomposition(vector<vector<double>>& mat, bool pivot) {
    int n = mat.size();
    int permutationCount = 0;
    double det = 1.0; // Inicialización del determinante

    for (int k = 0; k < n; k++) {
        
        if (pivot) {
            int maxRow = k;
            for (int i = k + 1; i < n; i++) {
                if (abs(mat[i][k]) > abs(mat[maxRow][k])) {
                    maxRow = i;
                }
            }
            if (maxRow != k) {
                swapRows(mat, k, maxRow);
                permutationCount++;
            }
        }

        for (int i = k + 1; i < n; i++) {
            if (mat[k][k] < EPS) {
                cout << "Error: ¡División entre cero!" << endl;
                return -1;
            }
            double factor = mat[i][k] / mat[k][k];
            mat[i][k] = factor;
            for (int j = k + 1; j < n; j++) {
                mat[i][j] -= factor * mat[k][j];
            }
        }

        det *= mat[k][k];
    }
    if (permutationCount % 2 == 1){
        det *= -1;
    }

    cout << "\nDeterminante: " << det << endl;

    return permutationCount;
}

int main() {
    vector<vector<double>> matriz = {
        {2, 1, -3}, 
        {-1, 3, 2}, 
        {3, 1, -3}};
    int n = matriz.size();

    cout << "Matriz Original:" << endl;
    printMatriz(matriz);

    char choice;
    cout << "Si se desea el pivoteo, oprima 'y', de lo contrario oprima 'n': ";
    cin >> choice;

    bool pivot = (choice == 'y' || choice == 'Y');

    int permutationCount = luDecomposition(matriz, pivot);

    if (permutationCount >= 0) {
        cout << "L y U matrices después de la descomposición:" << endl;
        printMatriz(matriz);
        cout << "Numero de permutaciones: " << permutationCount << endl;
    }

    return 0;
}