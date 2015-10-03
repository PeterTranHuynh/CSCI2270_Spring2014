#ifndef Lab6_LCS_CXX
#define Lab6_LCS_CXX
#include <algorithm>   // Provides copy function
#include <cstdlib>
#include <iostream>
#include <string>
#include <cstring>
#include <cassert>
#include "Aligner.h"
using namespace std;

namespace Lab6
{
	Aligner::Aligner()
	{
		matches = NULL;
		matched = false;
		maximum_match = -1;
		sequence1 = "";
		sequence2 = "";
	}    

    Aligner::~Aligner()
    {
		clear();
    }
 
	void Aligner::clear()
	{
		for (unsigned int k = 0; k < rows; ++k)
		{
			delete [] matches[k];
		}
		delete [] matches;
		matches = NULL;
		rows = 0;
		cols = 0;
		sequence1 = "";
		sequence2 = "";
	}
	
	void Aligner::initialize()
	{
		if (sequence1.length() == 0)
		{
			cout << "Enter sequence 1: ";
			cin >> sequence1;
		}
		if (sequence2.length() == 0)
		{
			cout << "Enter sequence 2: ";
			cin >> sequence2;
		}
		assert (sequence1.length() > 0 && sequence2.length() > 0);
		
		rows = sequence1.length();
		cols = sequence2.length();
		
		// create the 2D matches array and breadcrumbs array
		matches = new unsigned int*[rows + 1];
		for (unsigned int k = 0; k < rows + 1; ++k)
		{
			matches[k] = new unsigned int[cols + 1];
		}
		
		// initialize first row and column to 0
		for (unsigned int k = 0; k < rows + 1; ++k)
			matches[k][0] = 0;
		for (unsigned int k = 1; k < cols + 1; ++k)
			matches[0][k] = 0;
	}
	
    unsigned int Aligner::match()
    {
		for (unsigned int q = 1; q < rows + 1; ++q)
		{
			for (unsigned int r = 1; r < cols + 1; ++r)
			{
				// possibility 1: 2 letters match
				/*
				 * If the letters at sequence1[q-1] and sequence2[r-1] match, then set the matching at row q, column r to the maximum of
				 * (1+ the matching at row q-1, column r-1 
				 * OR the matching at row q-1, column r
				 * OR the matching at row q, column r-1).
				 * 
				 */
				if (sequence1[q - 1] == sequence2[r - 1])
				{
					if(matches[q-1][r-1] > matches[q-1][r] && matches[q-1][r-1] > matches[q][r-1])
						matches[q][r] = 1 + matches[q-1][r-1];
					else if(matches[q-1][r] > matches[q-1][r-1] && matches[q-1][r] > matches[q][r-1])
						matches[q][r] = matches[q-1][r];
					else if(matches[q][r-1] > matches[q-1][r-1] && matches[q][r-1] > matches[q-1][r])
						matches[q][r] = matches[q][r-1];
					else
						matches[q][r] = 1 + matches[q-1][r-1];
				}
				// possibility 2: 2 letters do not match 
				/*
				 * 
				 * If the letters do not match, then set the matching at row q, column r to the maximum of 
				 * (the matching at row q-1, column r OR the matching at row q, column r-1).
				 * 
				 */
				else
				{
					if(matches[q-1][r] > matches[q-1][r])
						matches[q][r] = matches[q-1][r];
					else if(matches[q][r-1] > matches[q-1][r])
						matches[q][r] = matches[q][r-1];
					else
						matches[q][r] = matches[q-1][r];
				}
			}
		}
		matched = true;
		maximum_match = matches[rows][cols];
		return matches[rows][cols];
		
	}
	
	
	bool Aligner::is_matched() const
	{
		return matched;
	}
	
	unsigned int Aligner::get_rows() const
	{
		return rows;
	}
	
	unsigned int Aligner::get_cols() const
	{
		return cols;
	}
	
	char Aligner::get_seq1_letter(unsigned int i) const
	{
		assert (i < rows);
		return sequence1[i];
	}
	
	char Aligner::get_seq2_letter(unsigned int j) const
	{
		assert (j < cols);
		return sequence2[j];
	}

	unsigned int Aligner::get_match(unsigned int m, unsigned int n) const
	{
		assert(matched);
		assert(m <= rows && n <= cols); 
		return matches[m][n];
	}
	
	unsigned int Aligner::count_digits(int num) const
	{
		if (num == 0) return 1;
		else
		{
			if (num < 0)
				num = -num;
			unsigned int i = 0;
			while (num != 0)
			{
				++i;
				num /= 10;
			}
			return i;
		}
	}
	
	ostream& operator<<(std::ostream& os, const Aligner& a)
	{
		if (a.is_matched() == false)
		{
			os << "unmatched alignment" << endl;
		}
		else
		{
			os << "\t";
			for (unsigned int j = 0; j < a.get_cols(); ++j)
			{
				os << a.get_seq2_letter(j);
				os << "\t";
			}
			os << endl;
			for (unsigned int i = 0; i < a.get_rows(); ++i)
			{
				os << a.get_seq1_letter(i);
				os << "\t";

				for (unsigned int j = 0; j < a.get_cols(); ++j)
				{
					os << a.get_match(i + 1, j + 1) << "\t";
				}
				os << endl;
			}
		}
		return os;
	}

		
}



#endif



