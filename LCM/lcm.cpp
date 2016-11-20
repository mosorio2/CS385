/*
 * lcm.cpp
 *
 *  Created on: Sep 7, 2015
 *      Author: O112
 */
#include <iostream>
#include <sstream>
using namespace std;


int gcd(int m, int n)
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
		return gcd(n, m%n);
	}
}
int lcm_recursive(int m, int n)
{
	return (m*n)/gcd(m,n);
}



int main(int argc, char *argv[])
{
	int m,n;
	int r;
	int q;
	istringstream iss;
	iss.str(argv[1]);
	iss >> m;
	iss.clear();
	iss.str(argv[2]);
	iss >> n;
	cout << lcm_recursive(m,n) << endl;
}
