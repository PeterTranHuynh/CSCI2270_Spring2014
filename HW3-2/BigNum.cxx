// FILENAME: BigNum.cxx
// This is the implementation file of the BigNum class

#ifndef HW3_BIGNUM_CXX
#define HW3_BIGNUM_CXX
#include <algorithm>   // Provides copy function
#include <cstdlib>
#include <iostream>
#include <string>
#include <cstring>
#include <cassert>
#include "BigNum.h"
using namespace std;

namespace HW3
{
	BigNum::BigNum()
	{
		capacity = DEFAULT_CAPACITY;				// Set sapacity to DEFAULT_CAPACITY (20)
		digits = new unsigned int[capacity];		// Assigned digits as an unsigned int array the size of capacity
		digits[0] = 0;								// Set the first digit index, 0, as 0.
		used = 1;									// Set used as 1, since 1 index is occupied with 0
		positive = true;							// Positive is set to true, even though zero isn't positive...
	}    

	BigNum::BigNum(int num)
	{
		capacity = DEFAULT_CAPACITY;
		digits = new unsigned int[capacity];
		used = 0;									// Used is set to 0, since no values are within the array
		
		if(num == 0)								// Condition for the para value equal to 0, constructs digits array to hold 0
		{
			digits[0] = 0;
			used = 1;
			positive = true;
		}
		else if(num > 0)							// Condition for if num is positive, sets positive to true
			positive = true;
		else										// Condition for everything else, positive is set to negative, and num is reversed in sign
		{
			positive = false;
			num = -num;
		}
		
		while(num != 0)								// Loop that continues until num reaches zero
		{
			digits[used] = num % 10;				// Sets digits, in the index of used, to the remainder of num/10
			num /= 10;								// num is reassigned as num / 10, rounded up to the closest integer
			used++;									// used increments within the end of the loop
		}
		
		if(digits[used - 1] == 0)					// Checks if the there is any lingering zeros to trim from the array end.
			trim();									// Calls trim
	}

	// Constructor that receives a string; leading 0's will be ignored
	BigNum::BigNum(const string& strin)
	{
		
		unsigned int usedTemp;						// Temp value of used, used for a for loop implementation
		
		if(strin[0] == '-')							// Condition to see if the string contains a negative number
		{
			used = strin.length() - 1;				// used is set to the string's length -1
			positive = false;
			usedTemp = used;						// usedTemp is assigned the value of used
		}
		else if(strin[0] == '+')					// Condition to see if the string has a positive number
		{
			used = strin.length() - 1;
			positive = true;
			usedTemp = used;
		}
		else										// Condition where there isn't a sign at the beginning of the string
		{
			used = strin.length();
			positive = true;
			usedTemp = used - 1;
		}
		
		if(used <= DEFAULT_CAPACITY)				// Conditions to check for the size of the string, without it's signs, then assigned capacity to either DEFAULT_CAPACITY or used
			capacity = DEFAULT_CAPACITY;
		else
			capacity = used;
		
		digits = new unsigned int[capacity];		// The unsigned int array digits is then created to the size of capacity
		
		if(strin[0] == '0' && strin[used - 1] == '0')		
			digits[0] = 0;
			
		for(unsigned int iterate = 0; iterate < used; iterate++)	// For loop that loops until it reaches the amount of digits within digits
		{
			digits[iterate] = strin[usedTemp] - '0';				// sets the current digit index within the for loop to the placement of the string at used Temp
																	// A TA during a help hour told me to put - 0x30.
			usedTemp--;								// decreases usedTemp by one.
		}
		
		if(digits[used - 1] == 0)					// Check to see if digits needs to be trimmed
			trim();
	}
 
    BigNum::BigNum(const BigNum& anotherBigNum)
    {
		capacity = anotherBigNum.capacity;			// Sets all values current instance to the anotherBigNum instance vars
		used = anotherBigNum.used;
		positive = anotherBigNum.positive;
		digits = new unsigned int[anotherBigNum.capacity];
		copy(anotherBigNum.digits, anotherBigNum.digits + used, digits);
    }

    BigNum::~BigNum()
    {
		delete [] digits;							// Deletes digits array off heap.
    }
    
    void BigNum::resize(unsigned int n)
	{
		if (n < used) return; 						// Can't allocate less than we are using, can't use assert either.
		unsigned int *largerArray;					// Will hold an array with a newly reassigned capacity size.

		capacity = n;
		largerArray = new unsigned int[capacity];
		
		copy(digits, digits + used, largerArray);	// Copies digits into the largerArray
		
		delete [] digits;							// Deletes digits
		digits = largerArray;						// Sets digits as largerArray
	}

	BigNum& BigNum::operator=(const BigNum& anotherBigNum)
	{
		unsigned int *resizeDigits;					// temp var used to reassign digits to a new size

		if (this == &anotherBigNum)					// Checks to see if the digits are the same instance
			return *this;	

		if (capacity != anotherBigNum.capacity)		// Looks to see if the capacities are different, uses temp to resize if they are
		{
			capacity = anotherBigNum.capacity;
			resizeDigits = new unsigned int[anotherBigNum.capacity];
			delete [ ] digits;
			digits = resizeDigits;
		}

		used = anotherBigNum.used;					// Copies num vars and values into this instance of big nums
		positive = anotherBigNum.positive;
		copy(anotherBigNum.digits, anotherBigNum.digits + used, digits);
		return *this;
	}

  
	BigNum& BigNum::operator+=(const BigNum& addend)  
	{
		*this = *this + addend;
		
		if(digits[used - 1] == 0)					// Check to see if digits needs to be trimmed
			trim();
		
		return *this;
	}

	BigNum& BigNum::operator-=(const BigNum& subtractand)
	{
		*this = *this - subtractand;
		
		if(digits[used - 1] == 0)					// Check to see if digits needs to be trimmed
			trim();
		
		return *this;
	}

	BigNum& BigNum::operator*=(const BigNum& multiplicand)
	{
		*this = *this * multiplicand;
		
		if(digits[used - 1] == 0)					// Check to see if digits needs to be trimmed
			trim();
		
		return *this;
	}

	BigNum& BigNum::operator/=(const BigNum& divisor)
	{
		*this = *this / divisor;
		
		if(digits[used - 1] == 0)					// Check to see if digits needs to be trimmed
			trim();
		
		return *this;
	}

	BigNum& BigNum::operator%=(const BigNum& divisor)
	{
		*this = *this % divisor;
		
		if(digits[used - 1] == 0)					// Check to see if digits needs to be trimmed
			trim();
		
		return *this;
	}

	BigNum& BigNum::operator++()
	{
		capacity += 1;								// Increments capacity up once
		unsigned int index = 1;						// Set index to 1 initially

		if(positive == false)						// Checks if number is negative, if so, turn it positive, subtract one from it, turn it back into negative
		{											//	Then check if the number is 0, if so, set positive true, then return the number
			positive = true;
			--*this;
			positive = false;
			if(used == 1 && digits[0] == 0)
				positive = true;
			return *this;
		}

		if(digits[0] != 9)							// Checks if the number is 9 at the front, if so, add one to it
		{
			digits[0] += 1;
			return *this;
		}

		digits[0] = 0;								// Sets the front to zero
		
		while(index < used)							// Loops from one to end of index
		{
			if(digits[index] != 9)					// Loops the process done by nine as before, except with a different index
			{										// If the index isn't 9, set that index as 0 then increase index
				digits[index] += 1;
				return *this;
			}
			else
			{
				digits[index] = 0;
				index++;
			}
		}

		digits[used] = 1;							// Sets the end of digits to 1 and then increases amount used
		used++;
		
		return *this;
	}

	BigNum& BigNum::operator--()
	{
		unsigned int index = 1;						// Sets index to 1 initially
		if (positive == false)						// Checks for negativity, does the oppositive of the ++ operator (increments big number)
		{
			positive = true;
			++*this;
			positive = false;
			return *this;
		}

		if (used == 1 && digits[0] == 0)			// Checks if number is 0
		{
			digits[0] = 1;
			positive = false;
			return *this;
		}

		if (digits[0] != 0)							// Checks if number isn't 0 in the front, if so, decrease it by one
		{
			digits[0] -= 1;
			return *this;
		}

		digits[0] = 9;
		while(index < used)							// loops from index 1 to the end of digits
		{
			if (digits[index] != 0)
			{
				if (index == used - 1 && digits[index] == 1)
					used--;

				digits[index] -= 1;
				return *this;
			}
			else
			{
				digits[index] = 9;
				index++;
			}
		}	
		
		return *this;
	}

	BigNum& BigNum::diff(const BigNum& a, const BigNum& b)
	{
		assert(a.positive && b.positive);			// Method will only run when these conditions are met.
		assert(a >= b);								// Asserts are cool.

		BigNum result = a;							// results set to a initially

		for(unsigned int index = 0; index < b.used; index++)	// Loops through the index of how long b is.
		{
			if(result.digits[index] < b.digits[index])			// Checks if the value is less than b, in which it must
			{													// either decrement the index value by one or check is the value is zero
				result.digits[index] += 10;
				if(result.digits[index+1] == 0)					// If it is zero, change it to 9 and then decrement it by one
				{
					unsigned int indexUp = index + 1;
					while(indexUp < result.used && result.digits[indexUp] == 0)
					{
						result.digits[indexUp] = 9;
						indexUp++;
					}
					result.digits[indexUp] -= 1;
				}
				else
				{
					result.digits[index+1] -= 1;
				}
			}
			result.digits[index] -= b.digits[index];
		}

		*this = result;
		return *this;
	}
  

	BigNum& BigNum::mult(const BigNum& a, const BigNum& b)
	{
		assert(a.positive && b.positive);			// Method will only run when these conditions are met.
		assert(a >= b);								// Asserts are cool.
		
		BigNum result;								// Local BigNums and vars
		BigNum aTemp(a);
		BigNum bTemp(b);
		BigNum addToResult;

		unsigned int carry = 0;	
		unsigned int multiple = 0;
		
		if (aTemp.used + bTemp.used > result.capacity)		// Checks to see if a resize is required
		{
			addToResult.resize(aTemp.used + bTemp.used);
			result.resize(aTemp.used + bTemp.used);
		}
		
		result.used = 0;									// sets used to 0, to restart the BigNums
		addToResult.used = 0;
		
		for (unsigned int index = 0; index < aTemp.used; index++)	// Loops through the amount of digits in a
		{
			unsigned int index3 = index;
	
			for (unsigned int index2 = 0; index2 < bTemp.used; index2++)	// Loops through the amount of digits in b
			{
				multiple =  aTemp.digits[index] * bTemp.digits[index2] + carry;		// Set multiple at a multiple of a and b + carry
				if (multiple >= 10)
				{
					carry = multiple / 10;					// If multiple is double digits set carry and reassign multiple
					multiple %= 10;
				}
				else
				{											// Else just set carry to 0
					carry = 0;
				}

				addToResult.digits[index3] = multiple;		// set the addTo at index3 ( = index initially) to multiple and set it's used values
				++addToResult.used;
				++index3;
			}

			if (carry != 0)									// Checks if there is a lingering carry, if so, add it to the addTo
			{
				addToResult.digits[addToResult.used] = carry;
				++addToResult.used;
			}

			result = result + addToResult;					// sums results and addTo bignums
			carry = 0;
			addToResult.used = index + 1;
			
			for (unsigned int zeroOut = 0; zeroOut < addToResult.used; zeroOut++)		// clears addTo
				addToResult.digits[zeroOut] = 0;
		}
			
		*this = result;
		return *this;
	}
	
	BigNum& BigNum::sum(const BigNum& a, const BigNum& b) 
	{
		assert(a.positive && b.positive);			// Method will only run when these conditions are met.
		assert(a >= b);								// Asserts are cool.
		
		// This information was thanks to Lab.
		BigNum result;
		result.used = 0;
		result.resize(a.capacity + 2);
		
		unsigned int carry = 0;
		
		for(unsigned int index = 0; index < used; index++)
		{
			if(index < b.used)
			{
				// get digit from digits array
				// add it addend
				// add carry (zero first time in loop)
				result.digits[index] = a.digits[index] + b.digits[index]	 + carry;
				if(result.digits[index] >= 10)
				{
					// set digit to result to sum % 10
					result.digits[index] %= 10;
					// set carry (for next loop iteration to carry / 10)
					carry = 1;
				}
				else
					carry = 0;
			}
			else
			{
				result.digits[index] = a.digits[index] + carry;
				if(result.digits[index] >= 10)
				{
					// set digit to result to sum % 10
					result.digits[index] %= 10;
					// set carry (for next loop iteration to carry / 10)
					carry = 1;
				}
				else
					carry = 0;
			}
			result.used++;
		}
		
		// check for any extra carry and add it to results
		if(carry != 0)
		{
			result.digits[result.used] = carry;
			result.used++;
		}
		
		*this = result;
		return *this;
	}

	BigNum operator+(const BigNum& a, const BigNum& b)
	{
		BigNum result;
		BigNum aTemp(a);
		BigNum bTemp(b);

		// a positive and b positive
		if(aTemp.positive == true && bTemp.positive == true)
		{
			if(a >= b)
				result = aTemp.sum(aTemp, bTemp);		
			else
				result = bTemp.sum(bTemp, aTemp);

			result.positive = true;
		}

		// a positive and b negative
		if(aTemp.positive == true && bTemp.positive == false)
		{
			bTemp.positive = true;

			if(aTemp >= bTemp)
			{
				result = aTemp.diff(aTemp, bTemp);
				result.positive = true;
			}
			else
			{
				result = bTemp.diff(bTemp, aTemp);
				result.positive = false;
			}		
		}
		
		// a negative and b positive
		if (a.positive == false && b.positive == true)
		{
			aTemp.positive = true;

			if (aTemp >= bTemp)
			{
				result = aTemp.diff(aTemp, bTemp);
				result.positive = false;
			}
			else
			{
				result = bTemp.diff(bTemp, aTemp);
				result.positive = true;
			}
      	}

		// a negative and b negative
		if (a.positive == false && b.positive == false)
		{
			aTemp.positive = true;
			bTemp.positive = true;
	
			if (aTemp >= bTemp)
				result = aTemp.sum(aTemp, bTemp);
			else
				result = bTemp.sum(bTemp, aTemp);

			result.positive = false;
		}
	
		if(result.digits[result.used - 1] == 0)
			result.trim();
		
		return result;
	}

	BigNum operator-(const BigNum& a, const BigNum& b)
	{
		BigNum result;
		BigNum aTemp(a);
		BigNum bTemp(b);

		// a positive and b positive
		if (a.positive == true && b.positive == true)
		{
			if (aTemp >= bTemp)
			{
				result = aTemp.diff(aTemp, bTemp);
				result.positive = true;
			}
			else
			{
				result = bTemp.diff(bTemp, aTemp);
				result.positive = false;
			}
		}

		// a positive and b negative
		if (a.positive == true && b.positive == false)
		{
			bTemp.positive = true;
	
			if (aTemp >= bTemp)
				result = aTemp.sum(aTemp, bTemp);
			else
				result = bTemp.sum(bTemp, aTemp);
	
			result.positive = true;
		}	

		// a negative and b positive
		if (a.positive == false && b.positive == true)
		{
			aTemp.positive = true;
	
			if (aTemp >= bTemp)
				result = aTemp.sum(aTemp, bTemp);
			else
				result = bTemp.sum(bTemp, aTemp);

			result.positive = false;
      	}

		// a negative and b negative
		if (a.positive == false && b.positive == false)
		{
			aTemp.positive = true;
			bTemp.positive = true;

			if (aTemp > bTemp)
			{
				result = aTemp.diff(aTemp, bTemp);
				result.positive = false;
			}
			else
			{
				result = bTemp.diff(bTemp, aTemp);
				result.positive = true;
			}     
		}

		if (result.digits[result.used - 1] == 0)
			result.trim();

	    return result;
	}
      
	BigNum operator*(const BigNum& a, const BigNum& b)
	{
		BigNum result;
		BigNum aTemp(a);
		BigNum bTemp(b);
		
		// Sets everything to positive
		if (aTemp.positive == false)
			aTemp.positive = true;
		if (bTemp.positive == false)
			bTemp.positive = true;
	
		// multiplies based on which is bigger, the bigger one goes in front of the operator
		if (aTemp >= bTemp)
		{
			result = aTemp.mult(aTemp, bTemp);
		}
		else
		{
			result = bTemp.mult(bTemp, aTemp);
		}
		
		// Sets the sign based on if there was one negative (a mismatch in sign)
		if (a.positive != b.positive)
			result.positive = false;
		
		return result;
	}

	BigNum operator/(const BigNum& a, const BigNum& b)
	{
		BigNum result;
		BigNum aTemp(a);
		BigNum bTemp(b);

      	unsigned int divisor = 0;
		unsigned int multiplier = 1;	

		if (aTemp.capacity > result.capacity)		// Checks if resize is required
			result.resize(aTemp.capacity);
		
		if (aTemp.positive == false)				// Checks for negativity
			aTemp.positive = true;
		if (bTemp.positive == false)
			bTemp.positive = true;

		if (aTemp < bTemp)							// If a is less than be, just return result
			return result;
	
		if (aTemp == bTemp)							// if a and b are equal, return a bignum 1 or -1
		{	
			if (a.positive != b.positive)
				result.positive = false;

			result.digits[0] = 1;
			return result;
		}

		while (bTemp <= aTemp)						// while b is less than a, set multiplier and divisor and change bTemp
		{
			++divisor;
			++multiplier;
			bTemp = b * multiplier;
		}

		result.used = 0;
		while (divisor != 0)						// While divisor isn't 0, divide results by setting indexes at the end to a modulo 10 of divisor
		{
			result.digits[result.used] = divisor % 10;
			divisor /= 10;
			++result.used;
		}

		if (a.positive != b.positive)				// Checks if the result should be negative
			result.positive = false;

		return result;
	}


	BigNum operator%(const BigNum& a, const BigNum& b)
	{
		BigNum result;
		BigNum aTemp(a);
		BigNum bTemp(b);
		
		if (aTemp.positive == false)					// Sets positive
			aTemp.positive = true;
		if (bTemp.positive == false)
			bTemp.positive = true;

		if (aTemp < bTemp)
			return aTemp;

		if (aTemp == bTemp)
			return result;

		result = aTemp - (bTemp * (aTemp / bTemp));		// To get a modulo, a must be subtracted by b times the ratio difference of the two, this gives a integer remainer
		return result;
	}

	bool operator>(const BigNum& a, const BigNum& b)
	{
		return (a >= b && a != b);			// Calls other comparison operators
	}


	bool operator>=(const BigNum& a, const BigNum& b)
	{
		return !(a < b);					// Calls other comparison operators
	}


	bool operator<(const BigNum& a, const BigNum& b)
	{
		// I don't any other way to do this without a bunch of conditionals... So... If else statements... nested
		if (a.positive == false)			// If a is negative
		{
			if (b.positive == true)			// b is bigger if positive, regardless
				return true;
			if (a.used > b.used)			// a number count is larger, then a is less than, if b is also negative
				return true;
			if (a.used < b.used)			// a number count is less, then a is greater than, if b is negative
				return false;
		}

		if (a.positive == true)				// If a is positive
		{
			if (b.positive == false)		// b is smaller is negative, regardless
				return false;
			if (a.used > b.used)			// a has a larger num count, b is smaller, if not negative
				return false;
			if (a.used < b.used)			// a has a smaller num count, b is larger, if not negative
				return true;
		}

		int index = a.used - 1;				// Index variable used to see if which number is bigger (if they are too similar)

		if (a.positive == false)			// If a is negative, use the reverse logic of the else statement while loop
		{
			while (index >= 0)
			{
				if (a.digits[index] > b.digits[index])
					return true;
				if (a.digits[index] < b.digits[index])
					return false;
				index--;
			}    
		}
		else
		{
			while (index >= 0)
			{
				if (a.digits[index] < b.digits[index])
					return true;
				if (a.digits[index] > b.digits[index])
					return false;
				index--;
			}
		}	
		
		return false;  
	}


	bool operator<=(const BigNum& a, const BigNum& b)
	{
		return !(a > b);					// Calls other comparison operators
	}


	bool operator==(const BigNum& a, const BigNum& b)
	{
		// Shortcuts, if both are not the same sign, return false. If they are not the same size, retur false
		if (a.positive != b.positive || a.used != b.used)
			return false;

		// Loop withing each index to see if they match, if they don't, then it returns false
		for(unsigned int index = 0; index < a.used; index++)
		{
			if (a.digits[index] != b.digits[index])
				return false;
		}
	
		// Returns true if all conditions didn't return false.
		return true;
	}


	bool operator!=(const BigNum& a, const BigNum& b)
	{
		return !(a == b);					// Calls other comparison operators
	}

	// Trim leading zeros
	void BigNum::trim()
	{
	    while (used > 1 && digits[used-1] == 0)	// loops through the end of the array digits, and removes all 0s, which would be in the beginning of the BigNum
			used--;								// used is subtracted to remove the 0
	}
	
	
	std::ostream& operator<<(std::ostream &os, const BigNum& bignum)
	{
		unsigned int j = 0;
		
		// Checks for negative number, if so, displays a - symbol
		if (bignum.positive == false)
			os << '-';

		// Goes through the number within each index and displays it
		for (unsigned int index = 0; index < bignum.used; index++)
		{
			os << bignum.digits[bignum.used - index - 1];
			if (j < 60)
				++j; 
			else 
			{
				os << endl;
				j = 0;
			}
		}
		return os;
	}

	std::istream& operator>>(std::istream &is, BigNum& bignum)
	{
		string str;								// Creates a string variable that is the user input
		is >> str;

		BigNum temp = str;						// Creates a BigNum out of the input string
		bignum = temp;							// Sets the temp BigNum to the bignum param and returns input
		return is;
	}
	
	
	BigNum factorial(const BigNum& a)
	{
		BigNum result(a);						// Result set as a
		BigNum factor(a);						// factor set as a as well

		result.resize(1000);
		
		if (a.positive == false)				// Check if a is negative, if so, sets factor to positive
			factor.positive = true;
	
		if (a.used == 1 && a.digits[0] == 0)	// Checks if a is just zero, in this case, result will be 1
		{
			result.used = 1;
			result.digits[0] = 1;
			return result;
		}

		while (factor.used > 1)					// Loops until factor is a single digit
		{   
			--factor;							// Subtracts 1 from factor
			result *= factor;					// Multiples result and factor an
		}
	
		while (factor.digits[0] != 1)			// Loops until factor is a single digit of 1
		{   
			--factor;							// Subtracts 1 from factor
			result *= factor;					// Multiples result and factor an
		}
	
		return result;
    }
  }



#endif
