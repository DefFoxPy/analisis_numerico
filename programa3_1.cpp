#include <iostream>
#include <iomanip>
using namespace std;

double func (double x) 
{
    return x * x * x - 3 * x * x - x + 3; // función a la cual se le aplicará el método
}

void biseccion(double a, double c, double tolerancia, int IL)
{
    const int W = 12; // para el ancho al mostrar datos en pantalla

    if (func(a) * func(c) >= 0)
    {
        cout << "No se puede asegurar la existencia de una raíz en el intervalo dado" << endl;
    }

    cout << "IT"<< setw(W) <<"A"<< setw(W)<<"B"<< setw(W)<<"C"<< setw(W)
         <<"F(A)"<< setw(W) <<"F(B)"<< setw(W) <<"F(C)"<< setw(20) <<"ABS(F(C)-F(A))/2" << endl;

    double b = (a + c) / 2;
    int it = 0;
    bool bandera = true;

    while ((c - a) >= tolerancia && it < IL)
    {
        it += 1;
        b = (a + c) / 2;

        cout  << setw(2) << it << setw(W) << a << setw(W) << b << setw(W) << c << setw(W) << func(a) 
             << setw(W) << func(b) << setw(W) << func(c) << setw(W) << abs(func(c) - func(a)) / 2 << endl;

        if (func(b) == 0.0) // raiz encontrada directamente
        {
            break;
        }
        else if (func(a) * func(c) > 0) // verificación de intervalo
        {
            cout << "El producto al evaluar el intervalo es positivo" << endl;
            bandera = false;
            break;
        }
        else if (func(b) * func(a) < 0)  // por la izquierda
        {
            c = b;
        }
        else // por la derecha
        {
            a = b;
        }

        // limites
        if (it == IL)
        {
            cout << "Límite de interaciones superado" << endl;
        }

        if ((c - a) < tolerancia)
        {
            cout << "Se ha satisfecho la tolerancia" << endl;
        }
    }
    
    if (bandera)
    {
        cout << "La raíz es aproximadamente: " << b << endl;
    }
}

int main()
{
    double a, c, tolerancia;
    int IL;

    cout << "Ingrese el intervalo [a, c]: ";
    cin >> a >> c;
    cout << "Ingrese la tolerancia: ";
    cin >> tolerancia;
    cout << "Ingrese el limite de interaciones: ";
    cin >> IL;

    if (a <= c)
    {
        biseccion(a, c, tolerancia, IL);
    }  
    else 
    {
        cout << "Intervalo no permitido" <<endl;
    }
    return 0;
}