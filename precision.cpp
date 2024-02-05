#include <iostream>
#include <limits>
#include <cfloat>
using namespace std;

void precision()
{
    float test_float = 1.0f;
    float incremento = 1.0f;

    while (test_float + incremento != test_float) 
    {
        incremento /= 2;
    }

    // Volver al último incremento que cambió el valor
    incremento *= 2;

    cout << "La precisión de float es: " << incremento << endl;
}


int main() 
{
    precision();
    return 0;
}