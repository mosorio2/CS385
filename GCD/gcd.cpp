/*
 * gcd.cpp
 *
 *  Created on: Sep 6, 2015
 *      Author: O112
 */
#include <iostream>
#include <sstream>
using namespace std;

int r=1;
int gcd_iterative(int m, int n)
{
	if (m == 0 || n == 0)
	{
		return max(m,n);
	}
	while (r != 0)
	{
		r= m%n;
		m=n;
		n=r;
	}
	return m;
}


int gcd_recursive(int m, int n)
{
	if (m == 0 || n == 0)
	{
		return max(m,n);
	}
	if (m%n == 0)
	{
		return n;
	}
	else
	{
		return gcd_recursive(n, m%n);
	}
}

int main(int argc, char *argv[])
{
	int m,n;

	if (argc != 3)
	{
		cerr << "Usage: " << argv[0] << " <integer m>" " <integer n>" << endl;
		return 1;
	}
	istringstream iss;

	iss.str(argv[1]);
	if (iss >> m)
	{
		iss.clear();
		iss.str(argv[2]);
		if (iss >> n)
		{
			cout << "Iterative: gcd(" << m << ", " << n <<") = " << gcd_iterative(m,n) << endl;
			cout << "Recursive: gcd(" << m << ", " << n <<") = " << gcd_recursive(m,n) << endl;
		}
		else
		{
			cerr << "Error: The second argument is not a valid integer." << endl;
		}
	}
	else
	{
		iss.clear();
		iss.str(argv[2]);
		if (iss >> n)
		{
			cerr <<"Error: The first argument is not a valid integer." << endl;
		}
	else
	{
		cerr <<"Error." << endl;
	}
	}
}


