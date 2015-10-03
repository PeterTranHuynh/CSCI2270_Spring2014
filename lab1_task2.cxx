#include <iostream> 
#include <cstdlib>
using namespace std;

double underflow_double( );
float underflow_float( );

int main( )
{
    cout << underflow_float() << endl;
    cout << underflow_double() << endl;
    return EXIT_SUCCESS;
}

double underflow_double( )
{
 	double eps2 = 1;
	double n2 = 1;
	while (eps2 > 0)
	{
		eps2 = eps2 / 2;
		if(eps2 > 0)
			n2 = eps2;
	}
	return n2;
}

float underflow_float( )
{
	float eps1 = 1;
	float n1 = 1;
	while (eps1 > 0)
	{
		eps1 = eps1 / 2;
		if(eps1 > 0)
			n1 = eps1;
	}
	return n1;
}
