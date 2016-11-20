/*
 * complexity.cpp
 *
 *  Created on: Nov 5, 2015
 *      Author: O112
 */


#include <iostream>

using namespace std;

int function0(int n) {
    int temp = 1;
    if (n <= 1) {
        return temp;
    }
    temp += function0(n - 1);
    return temp;
}

int function1(int n) {
    int temp = 1;
    if (n <= 1) {
        return temp;
    }
    temp += function1(n / 2);
    temp += function1(n / 2);
    return temp;
}

int function2(int n) {
    int temp = 0;
    if (n > 1) {
        for (int i = 1; i <= n; ++i) {
            ++temp;
        }
        temp += function2(n / 2);
    }
    return temp;
}

int function3(int n) {
    if (n <= 1) {
        return 0;
    }
    int temp = 0;
    for (int i = 1; i <= 8; ++i) {
        temp += function3(n / 2);
    }
    for (int i = 1, max = n * n * n; i <= max; ++i) {
        ++temp;
    }
    return temp;
}

int function4(int n) {
    int temp = 1;
    for (int i = 1; i <= n; ++i) {
        ++temp;
    }
    temp += function1(n / 2);
    temp += function1(n / 2);
    return temp;
}

int main() {
    cout << function0(16) << endl;
    cout << function1(16) << endl;
    cout << function2(16) << endl;
    cout << function3(16) << endl;
    cout << function4(16) << endl;
    cout << endl;
    cout << function0(64) << endl;
    cout << function1(64) << endl;
    cout << function2(64) << endl;
    cout << function3(64) << endl;
    cout << function4(64) << endl;
    return 0;
}

