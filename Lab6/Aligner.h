#ifndef Lab6_LCS_H
#define Lab6_LCS_H
#include <cstdlib>  // Provides unsigned int
#include <iostream> // Provides istream and ostream

namespace Lab6
{
    class Aligner 
    {
    public:
	
	// CONSTRUCTORS and DESTRUCTORS
	Aligner();                            
	~Aligner();
	
	// MEMBER FUNCTIONS
	std::string& get_sequence1() const;
	std::string& get_sequence2() const;

	unsigned int get_rows() const;
	unsigned int get_cols() const;

	bool is_matched() const;
	
	char get_seq1_letter(unsigned int index) const;
	char get_seq2_letter(unsigned int index) const;
	
	unsigned int get_match(unsigned int i, unsigned int j) const;
	void initialize();
	unsigned int match();
	
	// FRIEND FUNCTIONS
	friend std::ostream& operator<<(std::ostream& os, const Aligner& a);
	
  private:
	
	unsigned int count_digits(int num) const;
	void clear();
	
	unsigned int** matches;         // Pointer to the 2D array of matched letters 
	unsigned int** breadcrumbs;
	std::string sequence1;
	std::string sequence2;
	unsigned int rows;
	unsigned int cols;
	unsigned int maximum_match;
	bool matched;	          		// Indicates whether matching is done yet
	
    };

}

#endif

