	#include "poly.h"
using namespace std;

namespace main_savitch_5
{
	/*
	 * Polynomial Member Variables
	 * 
	 * EPSILON is a constant that is set to a very small number, found within numeric limits that will be used to set values to 0 if there is something smaller than EPSILON
	 * head_ptr is a polynode instance that is the polynomial of the 0 exponent of the function linked list
	 * tail_ptr is a polynode instance that is the highest exponent polynomial of the function linked list
	 * recent_ptr is a polynode instance that is a used to show the most recently used/manipulated part of the linked list
	 * current_degree is the unsigned integer used to show our highest exponent value.
	 * 
	 */
	
	
	/*
	 * Default Constructor used to create the linked polynomial head and tail
	 * 
	 */
	polynomial::polynomial(double c, unsigned int exponent)
	{
		// store machine epsilon
		EPSILON = std::numeric_limits<double>::epsilon();
		// write the rest
		head_ptr = new polynode();
		
		if(fabs(c) < EPSILON)											// Checks to see if the coeff c is too close to small, if it is, just keep the coeff 0
		{
			tail_ptr = head_ptr;										// Sets tail_ptr to head_ptr, meaning there is only one node
			current_degree = 0;											// Sets current degree to 0, meaning there is only a number 0 in the polynomial equation
		}
		else if(exponent == 0)											// Else, if c is greater than EPSILON and the passed exponent is 0, set the coeff to c
		{
			if(fabs(c) > EPSILON)
			{
				head_ptr->set_coef(c);
			}
			tail_ptr = head_ptr;
			current_degree = 0;
		}
		else															// If the two conditions don't check out, set everything normally
		{
			tail_ptr = new polynode();
			tail_ptr->set_coef(c);										// Sets coeff, exponent, and node links
			tail_ptr->set_exponent(exponent);
			tail_ptr->set_back(head_ptr);
			head_ptr->set_fore(tail_ptr);
			current_degree = exponent;
		}
		
		set_recent(0);													// Sets recent to head pointer
    }

	/*
	 * Operator = used to reassign a polynomial within the linked list
	 * 
	 */
    polynomial& polynomial::operator=(const polynomial& source)
    {
		// store machine epsilon
		EPSILON = std::numeric_limits<double>::epsilon();
		// write the rest
		if (this == &source)											// Checks if the passed source is the address of this, meaning they are the same exact thing, just return the node value
			return *this;

		if (head_ptr != nullptr)											// Clears the node if it isn't already empty
			this->clear();

		unsigned int degree = 0;										// Temp int to hold degree

		do
		{
			assign_coef(source.coefficient(degree), degree);			// Reassigns coeffs at the degree degree
			degree = source.next_term(degree);							// Finds the next degree after the current degree
		} while(degree != 0);											// Goes through all of the nodes/polynomial pieces and reassigns their values

		current_degree = source.degree();								// Sets current degree to the new degree
		
		return *this;
	}
	
	/*
	 * Constructor used to copy other polynomials
	 * 
	 */
    polynomial::polynomial(const polynomial& source)
    {
		// store machine epsilon
		EPSILON = std::numeric_limits<double>::epsilon();
		// write the rest
		this->head_ptr = new polynode();		// Reset head_ptr
		this->tail_ptr = head_ptr;				// Reset tail_ptr
		// I will now use the power of laziness to call the = operator instead.
		*this = source;
    }

	/*
	 * Destructor used to destroy reserved memory for this program, calls clear
	 * 
	 */
    polynomial::~polynomial()
    {
		clear();
    }

	/*
	 * Clear function that does all of the work for the destruction and ending of this program
	 * 
	 */
    void polynomial::clear()
    {	
		polynode* destroy;												// Temp polynode that is used to hold the polynode linked after the one that is being deleted

		while (head_ptr->fore() != nullptr)
		{
			destroy = head_ptr->fore();									// Sets the temp node pointer to the node after head_ptr
			delete head_ptr;											// deletes head_ptr node
			head_ptr = destroy;											// reset head_ptr to destroy and repeat
        }

		head_ptr->set_coef(0);											// Clears out everything to 0
		head_ptr->set_exponent(0);
		current_degree = 0;
		
		head_ptr->set_fore(nullptr);										// Nulls out all links
		head_ptr->set_back(nullptr);
		
		recent_ptr = head_ptr;											// recent_ptr is set toe head_ptr, which is deleted
		destroy = nullptr;												// Nulls our destroy
		

    }
    
    double polynomial::coefficient(unsigned int exponent) const
    {
		
		set_recent(exponent);											// Find the most recent node

		if (recent_ptr->exponent() != exponent)							// If this is not the node we're looking, then return 0
			return 0;

		else
			return recent_ptr->coef();									// Returns the coefficent otherwise if there is a matchup
    }

    void polynomial::add_to_coef(double amount, unsigned int exponent)
    {
		set_recent(exponent);

		if (fabs(amount) < EPSILON)										// Checks if the amount is smaller then EPSILON, if so, end the function
			return;

		else if(recent_ptr->exponent() == exponent)						// Checks if the exponents match, if so, just reassign the coeff to sum it with amount
		{
			assign_coef((recent_ptr->coef() + amount), recent_ptr->exponent());
		}

		else
			assign_coef(amount, exponent);								// Else, just set the coeff to amount, this means a new node is nonzero now.
	}

    void polynomial::assign_coef(double coefficient, unsigned int exponent)
    {
		set_recent(exponent);
		polynode* backward = recent_ptr->back();						// Sets temp polynode pointers to recent back and forth
		polynode* forward = recent_ptr->fore();

		if(fabs(coefficient) <= EPSILON)								// Checks if we need to set coeff to 0
			coefficient = 0;

		if(exponent == 0)												// Checks if we are changing the head_ptr
		{
			head_ptr->set_coef(coefficient);
			return;
		}

		else if (fabs(coefficient) < EPSILON)
		{
			// If exponents are same, set the coef to 0
			if (exponent == recent_ptr->exponent())
			{
				if (recent_ptr == head_ptr)
				{
					recent_ptr->set_coef(0);
					return;
				}
				// If it is the tail_ptr
				else if (recent_ptr->exponent() == current_degree)
				{
					recent_ptr = recent_ptr->back();
					recent_ptr->set_fore(nullptr);
					delete tail_ptr;
					tail_ptr = recent_ptr;
					current_degree = tail_ptr->exponent();
				}
				// Else if it is in the middle
				else
				{
					forward->set_back(backward);
					backward->set_fore(forward);
					delete recent_ptr;
					set_recent(exponent);
				}
			}
			else
				return;
		}
		
		else if (exponent > current_degree)								// Checks if the exponent is greater than current degree, creates new tail node
		{
			polynode* node = new polynode();
            node->set_coef(coefficient);
			node->set_exponent(exponent);
			node->set_fore(nullptr);
			node->set_back(recent_ptr);
			
			recent_ptr->set_fore(node);
			recent_ptr = node;
			tail_ptr = node;
			current_degree = exponent;
		}

		else if(recent_ptr->exponent() < exponent)						// Checks if the recent exponent is less that the pass exponent, creates a new node after recent (not tail)
        {
			polynode* node = new polynode();
			node->set_coef(coefficient);
			node->set_exponent(exponent);
			node->set_fore(forward);
			node->set_back(recent_ptr);
			
			recent_ptr->set_fore(node);
			forward->set_back(node);
			recent_ptr = node;
        }
        
		else if (recent_ptr->exponent() > exponent)						// Checks if we need to create a new node before recent
		{
			polynode* node = new polynode();
            node->set_coef(coefficient);
			node->set_exponent(exponent);
			node->set_fore(recent_ptr);
			node->set_back(backward);
            
			recent_ptr->set_back(node);
			backward->set_fore(node);
			recent_ptr = node;
		}
		else
			recent_ptr->set_coef(coefficient);							// else, if the coef is targeting recent, reassigne coeff of recent
    }

	/*
	 * function used to move to the next linked polynomial node
	 * 
	 */
    unsigned int polynomial::next_term(unsigned int exponent) const
    {
		if (exponent >= current_degree)									// Next term will not try to move backwards, thats wha previous_term is for, returns 0
			return 0;

		set_recent(exponent);											// set recent to the polynomial with the exponent passed

		if (recent_ptr->fore() == nullptr)								// If the movement is trying to move to null, return 0
			return 0;

		else
			return recent_ptr->fore()->exponent();						// Returns the next node's exponent if all other conditions pass
    }

	unsigned int polynomial::previous_term(unsigned int exponent) const
    {
		if (exponent <= 0)												// Similar logic as next_term, except done in a backwards manner, will not try to move forward
			return UINT_MAX;

		set_recent(exponent-1);											// Sets the recent to the node before the node with the same exponent param

		if (fabs(recent_ptr->coef()) < EPSILON)							// The the coeff is to close to 0, return UINT MAX
			return UINT_MAX;

		if (recent_ptr == nullptr)										// If the previous is null, return UNINT MAX
			return UINT_MAX;

		else
			return recent_ptr->exponent();								// Else, returns the previous exponent
    }
    
    /*
     * Function used to reassign the recent_ptr polynode instance into a latest list part called/used.
     * 
     */
    void polynomial::set_recent(unsigned int exponent) const
    {
		if(exponent == 0)												// Checks to see if the recent needs to be the head_ptr
		{
			recent_ptr = head_ptr;
			return;
		}
		
		else if(exponent >= current_degree)								// Checks to see if the exponent exceeds the highest degree, if so, set recent to tail_ptr
		{
			recent_ptr = tail_ptr;
			return;
		}
		
		else if(recent_ptr->exponent() == exponent)						// If recent exponent matches with passed exponent param, don't change recent
			return;	
		
		else if(recent_ptr->exponent() > exponent)						// If the param exponent is less then the current recent ptr exponent, loop backwards until they match
		{
			while(recent_ptr->back() != nullptr && recent_ptr->exponent() > exponent)
				recent_ptr = recent_ptr->back();
			if(recent_ptr->exponent() < exponent)						// If the recent_ptr has been set back too far, move if forward once.
				recent_ptr = recent_ptr->fore();
		}
		
		else
		{																// Similar logic to the previous conditional, except backwards.
			while(recent_ptr->fore() != nullptr && recent_ptr->exponent() < exponent)
				recent_ptr = recent_ptr->fore();
		}
	}
    
    double polynomial::eval(double x) const
    {
		double total = 0;
		return total;
    }

    polynomial polynomial::derivative() const
    {
		polynomial p_prime;
		return p_prime;
    }
    
    polynomial operator+(const polynomial& p1, const polynomial& p2)
    {
		polynomial p;
		return p;
    }
    
    polynomial operator-(const polynomial& p1, const polynomial& p2)
    {
		polynomial p;
		return p;
    }
    
    polynomial operator*(const polynomial& p1, const polynomial& p2)
    {		
		polynomial p;
		return p;
    }

    ostream& operator << (ostream& out, const polynomial& p)
    {
		unsigned int expo = 0;											// Temp int expo to represent exponent of the desired output
		do 
		{ 
			out << p.coefficient(expo) << "*x^" << expo; 				// Outputs the coefficent at the exponent expo then x^ then the exponent
			expo = p.next_term(expo);									// Moves forwards and repeats
			if (expo != 0) out << " + "; 								// If the exponent isn't zero, so after head_ptr if there is a node after, print a +
		} while(expo != 0); 

		return out;
    }
    
    void polynomial::find_root(
	double& answer,
	bool& success,
	unsigned int& iterations,
	double guess,
	unsigned int maximum_iterations,
	double epsilon) const
    {
		
	}
}
