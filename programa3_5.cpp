#include <iostream>
#include <iomanip>
using namespace std;

// función normal
double func (double x) 
{
    double y  = x * x * x - 5.0 * x * x + 6.0 * x;
    return  y;
}
// derivada de la función
double Dfunc(double x)
{
    double Dy = 3.0 * x * x - 10.0 * x + 6;
    return Dy;
}

void newton(double tolerancia, double est_ini)
{
    double x = est_ini;
    double xb = x;
    double y = 0, yd = 0;
    int interacion = 0;
    const int W = 15; // para lo de anchura de campo

    cout << "IT"<< setw(W) << "X(n-1)" << setw(W) << "Y(n-1)" << setw(W) << "X(n)" << endl;
    cout.setf(ios::scientific); // para usar la notación cientifica

    do
    {
        xb = x;
        interacion += 1;
        y = func(x);
        yd = Dfunc(x);
        x = x - y / yd; // esquema de newton (encontrar la nueva x)

        cout << setw(2) << interacion << setw(W) << xb << setw(W) << y << setw(W) << x << endl;

    } while ((abs(x - xb) >= tolerancia)); // prueba de convergencia

    cout << "Solución final: " << x << endl;    
}

int main ()
{   
    double tolerancia, est_ini;

    cout << "Ingrese la tolerancia: ";
    cin >> tolerancia;
    cout << "Ingrese el la estimación inicial para la raiz: ";
    cin >> est_ini;

    newton(tolerancia, est_ini);

    return 0;
}