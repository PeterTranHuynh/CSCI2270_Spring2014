
#include <iostream>  // Provides cout, cin
#include <cstdlib>   // Provides EXIT_SUCCESS

using namespace std;

int main( )
{
	unsigned int m = 25;
	
	// Still Relies entirely on unassigned ints, except now it's a for loop.
	for(unsigned int i = 0; i <= m; i++)
		cout << m - i << endl;
		
    return EXIT_SUCCESS;
}

