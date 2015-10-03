#include <cstdlib>  // Provides unsigned int
#include <iostream> // Provides istream and ostream

using namespace std;

class MyClass 
{
	private:
		int x;
	
	public:
		MyClass()
		{
			x=0;
		}
		
		MyClass(int x) 
		{
			this->x = x;
		}
		
		void setX(int x)
		{
			this->x = x;
		}
		
		int getX()
		{
			return x;
		}
		
		void printX()
		{
			cout << "x=" << x  << endl;
		}
		
};
