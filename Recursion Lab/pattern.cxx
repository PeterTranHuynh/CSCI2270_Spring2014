/**
 * 
 * BLUE
 * 
 * This was a tad harder than I expected...
 * 
 */

#include <cctype>          // Provides toupper
#include <iostream>        // Provides cout and cin
#include <cstdlib>         // Provides EXIT_SUCCESS
#include <string>
#include <math.h>			// MATH.H
using namespace std;


// PROTOTYPES for functions used by this test program:
void pattern(ostream& outs, unsigned int n, unsigned int i);

int main()
{
  int i2;
  cout << "Enter an integer: ";
  cin >> i2;
  pattern(cout, i2, 0);
  return (EXIT_SUCCESS);
}

// i is the offset
// n is the asterisks
void pattern(ostream& outs, unsigned int n, unsigned int i)
{
	unsigned int k = 0;
	unsigned int num = log(n) / log(2);
	if (num == 0)
	{   
		for (k = 0; k < i; k++) outs << (" ");
		for (k = 0; k < n; k++) outs << ("* ");
		outs << endl;
	}
	else
	{	
		unsigned int newNum = pow(2, num-1);
		pattern(outs, newNum, i); 
		for (k = 0; k < i; k++) outs << (" ");
		for (k = 0; k < n; k++) outs << ("* ");
		outs << endl;
		i += (num * 2);
		pattern(outs, newNum, i);
	}
}

