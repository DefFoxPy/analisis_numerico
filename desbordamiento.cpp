#include <iostream>
#include <limits>
using namespace std;

void desbordamiento ()
{
	int valor = 0;
	int previo = 0;

	while (valor >= previo)
	{
		previo = valor++;
	}

	cout << "El valor máximo para int antes del desbordamiento es: " << previo << endl; // 2147483647
    cout << "El valor de int después del desbordamiento es: " << valor << endl;
}

void con_libreria()
{
	int max_int = numeric_limits<int>::max();
	cout << "El valor máximo para int es: " << max_int << endl;
	max_int += 1;
	cout << "el valor de int después del desbordamiento es: " << max_int << endl;
}
int main()
{
	//con_libreria();
	desbordamiento();
    return 0;
}