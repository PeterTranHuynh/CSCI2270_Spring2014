#include "MyClass.cxx"


// Pass by value
void fun1(MyClass a)
{
	a.setX(1);
}


// Pass by reference
void fun2(MyClass& a)
{
	a.setX(2);
}



// Pass by pointer
void fun3(MyClass* a)
{
	a->setX(3);
}


// Using double pointers! Coz why stop at single pointers? :)
void fun4(MyClass** a)
{
	(*a)->setX(4);
}



int main() 
{
	MyClass a;
	MyClass* b;
	MyClass** c;
	
	cout << endl << "----Calling fun1----" << endl;
	
	fun1(a); 
	a.printX(); // Explaining output (1 point)	
	/*
	 * 
	 * In the function fun1, fun1 takes the parameter of a local copy of MyClass a, not the actual object a.
	 * Object a's x value is still 0, since fun1 just makes a copy of a, not passing a by reference.
	 * 
	 */

	cout << endl << "----Calling fun2----" << endl;	
	
	fun2(a); 
	a.printX(); // Explaining output (1 point)
	/*
	 * 
	 * In the function fun2, fun2 actually passes a by reference, which grabs the address of a, allowing for the 
	 * change in a's x value. a's new x value should be 2.
	 * 
	 */

	cout << endl << "----Calling fun3----" << endl;
	
	b = &a;     // Fixing compile error (1 point)
	// I've changed b to set to the address of a, which turns b into a hard copy of a.
	fun3(b);   
	a.printX(); // Explaining output (1 point)
	/*
	 * 
	 * b is a pointer object of MyClass, which is then set as the address of MyClass object a.
	 * function fun3 then takes in the pointer object b, which is the address of a and the changes a's x value
	 *  (using the arrow operator instead of the dot operator for the pointer to use the set method in MyClass objects)
	 * This thus changes a's x into 3, which is then printed out with the class method printX
	 * 
	 */

	cout << endl << "----Calling fun4----" << endl;
	
	c = &b;    // Fixing compile error (1 point)
	// I replaced the assignment of c from a into &b, which is the address of b, which is the value of a, since the pointer b is the address of a.
	// c becomes a pointer for the pointer b, which points to a. Hence, c is now a hard copy of b, which is a hard copy of a.
	fun4(c);    
	a.printX(); // Explaining output (1 point)
	/*
	 * 
	 * The double pointer object MyClass c is assigned the address of b, which is the value of a. Then the function fun4
	 * passes the double pointer c, which is a hard copy of b and a, and then uses the address of c, which is the address of a, or the value of b, with an arrow operator
	 * to call the set method to change a's x value into 4.
	 * 
	 */
	

	//Dereferencing using single pointer
	cout << "\n\nTwo ways of dereferencing, \n1. Using '.' operator\n2. Using '->' operator\n\n";
	
	(*b).printX();          // Fixing compile error (1 point)
	// I replaced b with (*b)
	(b)->printX();      // Fixing compile error (1 point) 
	// I replaced (*b) with (b)

	// An array of the object MyClass is created with the identifier arr, which can hold 5 seperate instances of MyClass objects
	cout << "\n\n----Understanding arrays as pointers----" << endl;
	MyClass arr[5];
	
	arr[0].setX(10);
	arr[1].setX(20);
	arr[2].setX(30);
	arr[3].setX(40);
	arr[4].setX(50);

	cout << "----Running for loop for array variable 'arr' with 5 slots----" << endl << endl;
	
	//Explaining for loop (2 points)
	for (unsigned int i=0; i<5; i++)
	{
		cout << "i = " << i << endl;
		cout << "memory location (arr + i) = " << arr+i << endl;
		cout << "  (*(arr + i)).printX() prints ";
		(*(arr+i)).printX();
		cout << "        arr[i].printX() prints ";
		arr[i].printX();
		cout << endl;
	}
	/*
	 * 
	 * This for loop iterates a total of 5 times, from 0 to 4, within a positive increments for i.
	 * Within the for loop itself, the loop prints out the value of i at it's current increment, then the memory address of the object array + i's value
	 * Then it uses this memory address as a pointer within a printX method of MyClass to display the x value of that object that the memory location contains
	 * After, the loop then prints the x value of the object at position i within the object array, which happens to be the same value as the previous
	 * memory location's x value. Hence, these addresses must be the addresses of the objects within the object array.
	 * 
	 */
	
	return 0;
}

