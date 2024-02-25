/*
Descomponer una matriz de la forma LU con pivoteo
*/
#include <iostream>
#include <vector>
#include <iomanip>
using namespace std;

const int L = 15; // para fines de mostrar la matriz

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

void luDecomposition(vector<vector<double>>& mat) {
    int n = mat.size();
    for (int k = 0; k < n; k++) {
        for (int i = k + 1; i < n; i++) {
            if (mat[k][k] == 0) {
                cerr << "Error: Division by zero!" << endl;
                return;
            }
            double factor = mat[i][k] / mat[k][k];
            mat[i][k] = factor;
            for (int j = k + 1; j < n; j++) {
                mat[i][j] -= factor * mat[k][j];
            }
        }
    }
}

int main() {
    vector<vector<double>> matrix = {
    	{2, 1, -3}, 
    	{-1, 3, 2}, 
    	{3, 1, -3}};
    int n = matrix.size();

    cout << "Original matrix:" << endl;
    printMatriz(matrix);

    luDecomposition(matrix);
    
    cout << "L and U matrices after decomposition:" << endl;
    printMatriz(matrix);

    return 0;
}