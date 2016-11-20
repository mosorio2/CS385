/*******************************************************************************
 * Name        : unique.cpp
 * Author      : Michael Osorio
 * Date        : 9/25/15
 * Description : Determining uniqueness of chars with int as bit vector.
 * Pledge      : I pledge my honor that I have abided by the Stevens Honor System
 ******************************************************************************/
#include <iostream>
#include <cctype>

using namespace std;

/*
 * Checks if all characters in the given string are lowercase letters in the
 * English alphabet.
 */
bool is_all_lowercase(const string &s) {
	int count = 0;
	for (unsigned int i = 0; i < s.length(); i++)
	{
		if ((isupper(s[i]) || !isalpha(s[i])))
		{
			count ++;
		}
	}
		if (count == 0)
		{
			return true;
		}
		else
		{
			return false;
		}
}

/*
 * Checks to make sure all letters in the string are unique
 * (no duplicates are found) using only one
 * int for storage and using bitwise and
 * bitshifting operators.
 */
bool all_unique_letters(const string &s)
{
	 if (s.length() == 0)
		 return true;
	 unsigned int value = 0;
	 for (unsigned int i = 0; i < s.length(); i++)
	 {
		 int asciival = s[i] - 97;
		 if ((value & (1 << asciival)) > 0)
			 return false;
		 value |= (1 << asciival);
	 }
	 return true;
}

/*
 * main function for testing. Reads and parses line arguments.
 * Calls other functions to produce correct output.
 */
int main(int argc, char * const argv[]) {
	if (argc != 2)
	{
		cerr << "Usage: " << argv[0] << " <string>" << endl;
		return 1;
	}
	if(!is_all_lowercase(argv[1]))
	{
		cerr << "Error: String must contain only lowercase letters." << endl;
		return 1;
	}
	if(!all_unique_letters(argv[1]))
	{
		cerr << "Duplicate letters found." << endl;
		return 1;
	}
	if(all_unique_letters(argv[1]))
	{
	cout << "All letters are unique." << endl;
	}
}
