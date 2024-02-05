#include <iostream>
#include <iomanip>
using namespace std;

/*
Vi(x) = (x−x1)(x−x2)···(x−xN)
(xi−x1)(xi−x2)···(xi−xN)

g(x) = V0(x)f0 +V1(x)f1 +···+VN(x)fN
*/

double interpolacion(int, double[], double[], double);
void mostrar_datos(int, double[], double[]);

int main()
{
	// datos
	const int N = 4;
	double x[] = {1.0, 2.0, 3.0, 4.0};
	double y[] = {0.671, 0.620, 0.567, 0.512};
	double x1;

	mostrar_datos(N, x, y);

	cout << "Ingrese x: ";
	cin >> x1;

	if (x1 < x[0] || x1 > x[N-1])
	{
		cout << "Advertencia, X está en el rango de extrapolación" << endl;
	}

	double result = interpolacion(N, x, y, x1);
	cout.setf(ios::scientific);
	cout  << "El resultado de la interpolacion es: " << result << endl;

	return 0;
}

double interpolacion(const int N, double x[], double y[], double x1)
{
	double result = 0.0;

	for (int i = 0; i < N; i++)
	{
		double term = y[i];
		for (int j = 0; j < N; j++)
		{
			if (j != i)
			{
				term *= (x1 - x[j]) / (x[i] - x[j]);	
			}
		}
		result += term;
	}
	return result;
}

void mostrar_datos(const int N, double x[], double y[])
{
	cout << "Valores utilizados" << endl;
	cout << "I\tx[i]\ty[i]" << endl;
	for (int i = 0; i < N; i++)
	{	
		cout << i << "\t" << x[i] << "\t" << y[i] << endl;
	}
	cout << endl;
}	