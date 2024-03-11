#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>

using namespace std;

const int L = 15;
const int POLINOMIAL = 0;

double func(double x, int i) {
	if (i == 1) 
		return 1;
	else if (i == 2) 
		return x;
	else if (i == 3) 
		return sin(x);
	else if (i == 4) 
		return exp(x);
	else
		return 0;
}

vector<double> Regression(const vector<double>& x, const vector<double>& y, int order, int LP) {
    int n = x.size();
    int m = 0;

    if (LP == POLINOMIAL)
    	m = order + 1;
    else
    	m = order;

    // Crear matrices para el sistema de ecuaciones normales
    vector<vector<double>> A(m, vector<double>(m, 0));
    vector<double> B(m, 0);

    // Calcular las sumatorias necesarias
    if (LP == POLINOMIAL) {
	    
	    for (int i = 0; i < n; i++) {
	        
	        for (int j = 0; j < m; j++) {
	            
	            for (int k = 0; k < m; k++) {
	                A[j][k] += pow(x[i], j + k);
	            }
	            B[j] += y[i] * pow(x[i], j);
	        }
	    }
	}
	else {

		for (int i = 0; i < n; i++) {
	        
	        for (int j = 0; j < m; j++) {
	            double func1 = func(x[i], j+1);
	            
	            for (int k = 0; k < m; k++) {
	                A[j][k] += func1 * func(x[i], k+1);
	            }
	            B[j] += y[i] * func1;
	        }
	    }

	}

    // mostrando el sistema de ecuaciones
    cout.setf(ios::scientific);
    for (int i = 0; i < m; i++) {

    	for ( int j = 0; j < m; j++) {
    		cout << setw(L) << A[i][j];
    	}
    	cout << setw(L) << B[i] << endl;
    }
    cout.unsetf(ios::scientific);

    cout << "\nDeterminación de los coeficientes" << endl;

    // Resolver el sistema de ecuaciones normales
    vector<double> coefficients(m, 0);
    for (int i = 0; i < m; i++) {
        for (int j = i + 1; j < m; j++) {
            double ratio = A[j][i] / A[i][i];
            for (int k = 0; k < m; k++) {
                A[j][k] -= ratio * A[i][k];
            }
            B[j] -= ratio * B[i];
        }
    }
    for (int i = m - 1; i >= 0; i--) {
        double sum = 0;
        for (int j = i + 1; j < m; j++) {
            sum += A[i][j] * coefficients[j];
        }
        coefficients[i] = (B[i] - sum) / A[i][i];
    }

    // Imprimir los resultados
    cout << "\nPotencia\tCoeficiente" << endl;
    for (int i = 0; i < m; i++) {
    	
    	if (LP == POLINOMIAL)
    		cout << i << "\t\t" << coefficients[i] << endl;
    	else
    		cout << i+1 << "\t\t" << coefficients[i] << endl;
    }
    cout << endl;

    return coefficients;
}

void errorEvalue(const vector<double>& x, const vector<double>& y, const vector<double>& coefficients, int k) {

	cout << "I" << setw(L) << "X(I)" << setw(L) << "Y(I)" 
	     << setw(L) << "Polinomio" << setw(L) << "Desviacion" << endl;

	for (int i = 0; i < x.size(); i++) {
		double gg = 0;
		
		for (int j = 1; j <= coefficients.size(); j++) {
			
			if (k == POLINOMIAL) 
				gg = gg + coefficients[j-1] * pow(x[i], j-1); 
			else 
				gg = gg + coefficients[j-1] * func(x[i], j); 
		}
		cout << i << setw(L) << x[i] << setw(L) << y[i] << setw(L) << gg << setw(L) << y[i] - gg << endl;
	}
	
}


int main() {
	vector<double> x = {0.1, 0.4, 0.5, 0.7, 0.7, 0.9};
    vector<double> y = {0.61, 0.92, 0.99, 1.52, 1.47, 2.03};	
	int LP, op;

	cout << "Ajuste de curvas mediante 	minimos cuadrados" << endl;
	cout << "Oprima 0 para ajuste polinomial, 1 para combinación lineal: ";
	cin >> LP;
	
	if (LP == POLINOMIAL) {
		cout << "orden del polinomio: ";
	}
	else {
		cout << "De el número de funciones en la combinación lineal: ";
	}

	cin >> op;
	auto coefficients = Regression(x, y, op, LP);
	errorEvalue(x, y, coefficients, LP);

	return 0;
}
