// cuadratura de gauss
#include <iostream>
#include <iomanip>
#include <cmath>
#include <vector>
using namespace std;

const int ANCHO = 12;

double func(double x)
{
	return sin(x);
}

int main()
{
	vector<double> W(10, 0); // peso de integración
	vector<double> XA(10, 0); // coordenadas x en los puntos de la reticula	
	int n = 0;
	double a, b;

	cout << "Cuadratura de Gauss" << endl;
	cout << "Ordenes disponibles: N = 2, 3, 4, 5, 6, 8, 10" << endl;
	cout << "Ingrese N: ";
	cin >> n;

	if (n <= 0) 
		return 0;
	if (n == 7 || n == 9)
	{ 
		cout << "N = " << n << "no está disponible" << endl;
		return 0;	
	}

	cout << "¿limite inferior?: ";
	cin >> a;
	cout << "¿Limite superior?: ";
	cin >> b;

	if (n == 2)
	{
		XA[2] = 0.5773502691;
		W[2] = 1;
	}
	else if (n == 3)
	{
		XA[2] = 0;
		XA[3] = 0.7745966692;
		W[2] = 0.8888888888;
		W[3] = 0.5555555555;
	}
	else if (n == 4)
	{
		XA[3] = 0.3399810435;
		XA[4] = 0.8611363115;
		W[3] = 0.6521451548;
		W[4] = 0.3478548451;
	}
	else if (n == 5)
	{
		XA[3] = 0;
		XA[4] = 0.5384693101;
		XA[5] = 0.9061798459;
		W[3] = 0.5688888888;
		W[4] = 0.4786286704;
		W[5] = 0.2369268850;
	}
	else if (n == 6)
	{
		XA[4] = 0.2386191860;
		XA[5] = 0.6612093864;
		XA[6] = 0.9324695142;
		W[4] = 0.4679139345;
		W[5] = 0.3607615730;
		W[6] = 0.1713244923;
	}
	else if (n == 8)
	{
		XA[5] = 0.1834346424;
		XA[6] = 0.5255324099;
		XA [7] = 0.7966664774;
		XA[8] = 0.9602898564;
		W [5] = 0.3626837833;
		W [6] = 0.3137066458;
		W[7] = 0.2223810344;
		W[8] = 0.1012285362;
	}
	else if (n == 10)
	{
		XA[6] = 0.1488743389;
		XA[7] = 0.4333953941;
		XA[8] = 0.6794095682;
		XA[9] = 0.8650633666;
		XA[1] = 0.9739065285;
		W[6] = 0.2955242247;
		W[7] = 0.2692667193;
		W[8] = 0.2190863625;
		W[9] = 0.1494513491;
		W[1] = 0.0666713443;
	}
	
	const double PI = 3.1415927;
	const int int_n_2 = n / 2;
	
	for (int i = 1; i <= int_n_2; i++)
	{
		W[i] = W[n+1-i];
		XA[i] = -XA[n+1-i];
	}

	cout << setw(2) << "N" << setw(ANCHO) << "x" << setw(ANCHO) << "f(x)" << setw(ANCHO) << "w" << endl;

	for (int i = 1; i <= n; i++)
	{
		XA[i] = (XA[i] * (b - a) + a + b) / 2; // punto de gauss
	}
	
	double xi = 0; // resultado calculado
	double x = 0, f = 0;
	// inicialización de la formula de cuadratura de gauss
	for ( int i = 1; i <= n; i++)
	{
		x = XA[i];
		f = func(x);
		xi = xi + f * W[i];
		cout << setw(2) << i << setw(ANCHO) << x << setw(ANCHO) << f << setw(ANCHO) << W[i] << endl;
	}	
	xi = xi * (b - a) / 2;

	cout << "resultado final: i = " << xi << endl;

	return 0;
}