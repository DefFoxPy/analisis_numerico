#include <iostream>
#include <vector>
#include <iomanip>

using namespace std;

vector<vector<double>> tablaDiferencias(vector<double> x, vector<double> y) {
    int n = x.size();
    vector<vector<double>> T(n, vector<double>(n));

    for (int i = 0; i < n; i++) {
        T[0][i] = y[i];
    }

    for (int i = 1; i < n; i++) {
        for (int j = 0; j < n - i; j++) {
            T[i][j] = (T[i - 1][j + 1] - T[i - 1][j]) / (x[j + i] - x[j]);
        }
    }

    return T;
}

int main() {
    vector<double> x = {0.1, 0.2, 0.4, 0.7, 1.0, 1.2, 1.3};
    vector<double> y = {0.99750, 0.99002, 0.96040, 0.88120, 0.76520, 0.67113, 0.62009};

    vector<vector<double>> T = tablaDiferencias(x, y);

    cout << "I    X(I)    F(I, I+1)  F(I, I+2)  ..." << endl;

    for (int i = 0; i < T.size(); i++) {
        cout << fixed << i << "  " << x[i] << "  ";
        for (int j = 0; j < T[i].size(); j++) {
            if (T[j][i] == 0) cout << " ";
            else cout  << T[j][i] << "  ";
        }
        cout << endl;
    }

    return 0;
}