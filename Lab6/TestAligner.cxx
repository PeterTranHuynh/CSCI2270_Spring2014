#include <iostream>
#include <string>
#include "Aligner.h"

using namespace std;
using namespace Lab6;

	int main()
	{
		char c;
		do 
		{
			// here we call the Aligner constructor
			Aligner al;
			// here we prepare strings to align 
			al.initialize();
			// now we align the strings
			unsigned int m = al.match();
			// now we print the matching alignment score
			cout << "Match gives me a score of: " << m << endl;
			cout << al << endl;
			// now we let the user quit aligning things
			cout << "Enter 'q' to quit or any other key to continue: ";
			cin >> c;
		} while (c != 'q' && c != 'Q');
	}

