/*
 * practice.cpp
 *
 *  Created on: Sep 3, 2015
 *      Author: O112
 */
#include <iostream>
#include <string>
#include <sstream>
#include <vector>

using namespace std;

int sum(int a, int b)
{
	return a + b;
}

int main()
{
	int *array = new int[5];
	array[0] = 2;
	cout << array[0] << endl;
	return 0;
	delete[] array;
}
