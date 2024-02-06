/*
Integra una función analitica, ya sea mediante la regla del trapecio
 o mediante la regla extendida de simpson, según la elección del usuario.
*/
#include <iostream>
#include <cmath>
#include <iomanip>
using namespace std;

const int ISIMP_trapecio = 0;
const int ISIMP_simpson = 1;
const int ANCHO = 15;

double func (double x) // funcion a integral
{
	return pow(1 + pow(x / 2, 2), 2) * 3.14159;
}

double trapz(int n, double a, double b, double h)
{
	double s = 0, x;
	double w = 0;

	for (int i = 0; i <= n; i++)
	{
		x = a + i * h;
		w = 2;
		if (i == 0 or i == n)
		{
			w = 1;
		}
		s = s + w * func(x);
		cout << setw(2) << i << setw(ANCHO) << x << setw(ANCHO) << h << setw(ANCHO) << func(x) << setw(ANCHO) << w << endl; 
	}
	s = s * h / 2;
	return s;
}

double simps(int n, double a, double b, double h)
{
	double s = 0, ss = 0;
	double x = 0, w = 0;
	double ls;

	if (n % 2 == 1)
	{	
		ls = 3;
		for (int i = 0; i <= 3; i++)// regla de 3/8 simpson si es impar n
		{
			x = a + h * i;
			w = 3;
			if ( i == 0 or i == 3)
			{
				w = 1;
			}
			ss = ss + w * func(x);
		}
		ss = ss * h * 3 / 8;
		
		if (n == 3)
		{
			return ss;
		}
	}
	else
	{
		ls = 0;
	}
	// aplicar la regla de 1/3 de simpson
	for (int i = 0; i <= n - ls; i++)
	{
		x = a + h * (i + ls);
		w = 2;
		int i_trunc = i / 2;
		if (i_trunc * 2 + 1 == 1)
		{
			w = 4;
		}
		if (i == 0 or i == n - ls)
		{
			w = 1;
		}
		s = s + w * func(x);
	}
	ss = ss + s * h / 3;
	return ss;
}

int main()
{
	int opcion, n;
	double a, b;
	double h, s;

	cout << "La función a integrar debe estar definida en el subprograma" << endl;

	cout << "eliga 0 para el trapecio, 1 para el simpson" << endl;
	cin >> opcion;

	cout << "¿número de intervalos? ";
	cin >> n;

	if (opcion != ISIMP_simpson and opcion != ISIMP_trapecio)
	{
		cout << "La opción es invalida" << endl;
	}
	else
	{
		cout << "¿límite inferior de integración?: ";
		cin >> a;
		cout << "¿LÍMITE superior de ingregración?; ";
		cin >> b;

		h = (b - a) / n; // espaciamiento

		if (opcion == ISIMP_trapecio)
		{
			s = trapz(n, a, b, h);
		}
		else
		{
			s = simps(n, a, b, h);
		}
		cout << "Resultado final: " << s << endl;
	}

	return 0;
}