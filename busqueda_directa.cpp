/*
IO2 optimización incondicionada, método búsqueda directa
*/
#include <iostream>
#include <iomanip>
using namespace std;

double func (double x) 
{
    // función definida por tramos
    if (0 <= x && x < 2)
    {
        return 3 * x;
    }
    else if (2 <= x && x <= 3)
    {   
        return (0.3333) * (20 - x); 
    }
    else 
    {
        cout << "Error, la función no tiene definido este valor" << endl;
        return 0; //función no definida en ese intervalo
    }
}

void busqueda_directa(double a, double c, double tolerancia, int IL)
{
    const int W = 12; // para el ancho al mostrar datos en pantalla

    cout << "IT"<< setw(W) <<"xi"<< setw(W) <<"xr"<< setw(W) <<"x1"<< setw(W) << "x2" 
         << setw(W) << "func(x1)" << setw(W) << "func(x2)" << endl;

    int it = 0;
    double xi = a;  
    double xr = c; 
    bool bandera = false;

    while ((xr - xi) >= tolerancia && it < IL)
    {
        it += 1;
        double x1 = 0.5 * (xr + xi - tolerancia);  
        double x2 = 0.5 * (xr + xi + tolerancia);

        cout << setw(2) << it << setw(W) << xi << setw(W) << xr << setw(W) << x1 << setw(W) << x2 
             << setw(W) << func(x1) << setw(W) << func(x2) << endl;

        if (func(x1) > func(x2))
        {
            xr = x2;
        }
        else if (func(x1) < func(x2))
        {
            xi = x1;
        }
        else // iguales
        {
            xi = x1;
            xr = x2;
        }

        // limites
        if (it == IL)
        {
            cout << "Límite de interaciones superado" << endl;
        }

        if ((xr - xi)/ 2 < tolerancia)
        {
            cout << "Se ha satisfecho la tolerancia" << endl;
            cout << "punto máximo aproximado: " << func((xr + xi) / 2) << endl;
            cout << "en el punto x= " << (xr + xi) / 2 << endl; 
            break;
        }
    }
    
    if (bandera)
    {

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
        busqueda_directa(a, c, tolerancia, IL);
    }  
    else 
    {
        cout << "Intervalo no permitido" <<endl;
    }
    return 0;
}