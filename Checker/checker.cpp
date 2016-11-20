/*
 * checker.cpp
 *
 *  Created on: Sep 24, 2015
 *      Author: O112
 */
#include <iostream>
#include <sstream>
using namespace std;



void mystery2(int values[], int i, int j) {
    values[i] = values[i] ^ values[j];
    values[j] = values[i] ^ values[j];
    values[i] = values[i] ^ values[j];
}
