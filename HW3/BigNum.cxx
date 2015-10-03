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
			digits[iterate] = strin[usedTemp] - 0x30;				// sets the current digit index within the for loop to the placement of the string at used Temp
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
		assert(n < used);							// Catch all where it won't run unless if n is less than used
		unsigned int multiplier = 1;				// unsigned int used to set a bigger capacity
		while (multiplier * DEFAULT_CAPACITY < n)
			multiplier *= 2;
		unsigned int *newDigits;					// Temp unsigned int for new digits array
		
		if(multiplier * DEFAULT_CAPACITY == capacity)
			return;									// Checks to see if the multiplied default capacity is equal to current capacity
		
		capacity = multiplier * DEFAULT_CAPACITY;	// capacity is set as a multiple of Default Capacity grater than n.
		newDigits = new unsigned int[capacity];
		copy(digits, digits + used, newDigits);		// Copies digits into newDigits
		delete [] digits;
		digits = newDigits;
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
		return *this;
	}

	BigNum& BigNum::operator--()
	{
		return *this;
	}

	BigNum& BigNum::diff(const BigNum& a, const BigNum& b)
	{
		return *this;
	}
  

	BigNum& BigNum::mult(const BigNum& a, const BigNum& b)
	{
		return *this;
	}
	
	BigNum& BigNum::sum(const BigNum& a, const BigNum& b) 
	{
		assert (a.positive && b.positive);			// Method will only run when these conditions are met.
		assert (a >= b);
		
		BigNum results;
		result.used = 0;
		
		unsigned int sum = 0;
		unsigned int carry = 0;
		unsigned int index;	
		
		for(index = 0; index < used; index++)
		{
			if (index < a.used)
			{
				// get digit from digits array
				// add it addend
				// add carry (zero first time in loop)
				sum += (a.digits[index] + b.digits[index]) + carry;
				if (sum >= 10)
				{
					// set digit to result to sum % 10
					results.digits[index] = sum % 10;
					// set carry (for next loop iteration to carry / 10)
					carry = sum / 10;
				}
				else
				{
					results.digits[index] = sum;
					carry = 0;
				}
			}
			else
			{
				sum += a.digits[index] + carry;
				if (sum >= 10)
				{
					// set digit to result to sum % 10
					results.digits[index] = sum % 10;
					// set carry (for next loop iteration to carry / 10)
					carry = sum / 10;
				}
				else
				{
					results.digits[index] = sum;
					carry = 0;
				}
			}
			result.used++;
		}
		
		// check for any extra carry and add it to results
		if(carry != 0)
			results.digits[index+1] = carry;
			
		return result;
	}

	BigNum operator+(const BigNum& a, const BigNum& b)
	{
		BigNum result;
		return result;
	}

	BigNum operator-(const BigNum& a, const BigNum& b)
	{
		BigNum result;
		return result;
	}
      
	BigNum operator*(const BigNum& a, const BigNum& b)
	{
		BigNum result;
		return result;
	}

	BigNum operator/(const BigNum& a, const BigNum& b)
	{
		BigNum result;
		return result;
	}


	BigNum operator%(const BigNum& a, const BigNum& b)
	{
		BigNum result;
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
		// Shortcuts, if both are not the same sign, return false
		if (a.positive != b.positive)
			return false;

		// If they are not the same size, retur false
		if (a.used != b.used)
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
		// Indexes through digits and moves it a space back within the array if there is a leading zero, which is in the front.
		unsigned int index = used - 1; 
	    while (digits[index] == 0 && digits[0] != 0)
	    {
			digits[index] = digits[index - 1];
			index--;
			used--;
	    }
	}
	
	
	std::ostream& operator<<(std::ostream &os, const BigNum& bignum)
	{
		// Checks for negative number, if so, displays a - symbol
		if (bignum.positive == false)
			os << '-';

		// Goes through the number within each index and displays it
		for (unsigned int index = 0; index < bignum.used; index++)
		{
			os << bignum.digits[bignum.used - index - 1];
		}
		return os;
	}

	std::istream& operator>>(std::istream &is, BigNum& bignum)
	{
		// Loops until used size is met, adds numbers into index of bignum digits array
		for (unsigned int index = 0; index < bignum.used; index++)
			is >> bignum.digits[index];
		return is;
	}
	
	BigNum factorial(const BigNum& a)
	{
		BigNum result;
		return result;
    }
  }



#endif



