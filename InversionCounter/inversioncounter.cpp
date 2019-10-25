/*******************************************************************************
 * Name        : inversioncounter.cpp
 * Author      : Miles Rosenberg
 * Version     : 1.0
 * Date        : 10/25/19
 * Description : Counts the number of inversions in an array.
 * Pledge      : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/
#include <iostream>
#include <algorithm>
#include <sstream>
#include <vector>
#include <cstdio>
#include <cctype>
#include <cstring>
 
using namespace std;
 
// Function prototype.
static long mergesort(int array[], int scratch[], int low, int high);
 
/**
 * Counts the number of inversions in an array in theta(n^2) time.
 */
long count_inversions_slow(int array[], int length) {
    // TODO
    long sum = 0;
    for(int i = 0; i < length; i++){
        for(int j = i + 1; j < length; j++) {
            if(array[i] > array[j])
                sum+=1;
        }
    }
    return sum;
}
 
/**
 * Counts the number of inversions in an array in theta(n lg n) time.
 */
long count_inversions_fast(int array[], const int length) {
    // TODO
    // Hint: Use mergesort!
    int* scratch = new int[length];
    long n = mergesort(array, scratch, 0, length - 1);
    delete scratch;
    return n;
}
 
static long mergesort(int array[], int scratch[], int low, int high) {
    // TODO
    if(low < high) {
        int mid = low + (high - low) / 2;
        long sum = mergesort(array, scratch, low, mid);
        sum += mergesort(array, scratch, mid+1, high);
        int i = low;
        int L = low;
        int H = mid + 1;
        while(L <= mid && H <= high) {
            if(array[L] <= array[H]) {
                scratch[i] = array[L];
                L++;
            } else {
                scratch[i] = array[H];
                sum += mid - L + 1;
                H++;
            }
            i++;
        }
        while(L <= mid){
            scratch[i] = array[L];
            L++;
            i++;
        }
        while(H <= high) {
            scratch[i] = array[H];
            H++;
            i++;
        }
        for(i = low; i <= high; i++) {
            array[i] = scratch[i];
        }
        return sum;
    }
    return 0;
}
 
int main(int argc, char *argv[]) {
    // TODO: parse command-line argument
    if(argc != 1 && argc != 2) {
        cout << "Usage: " << argv[0] << " [slow]";
        return 0;
    }
    bool Slow = false;
    if(argc == 2) {
        Slow = true;
        if(strcmp(argv[1],"slow")) {
            cout << "Error: Unrecognized option '" << argv[1] << "'.";
            return 0;
        }
 
    }
    cout << "Enter sequence of integers, each followed by a space: " << flush;
 
    istringstream iss;
    int value, index = 0;
    vector<int> values;
    string str;
    str.reserve(11);
    char c;
    while (true) {
        c = getchar();
        const bool eoln = c == '\r' || c == '\n';
        if (isspace(c) || eoln) {
            if (str.length() > 0) {
                iss.str(str);
                if (iss >> value) {
                    values.push_back(value);
                } else {
                    cerr << "Error: Non-integer value '" << str
                         << "' received at index " << index << "." << endl;
                    return 1;
                }
                iss.clear();
                ++index;
            }
            if (eoln) {
                break;
            }
            str.clear();
        } else {
            str += c;
        }
    }
    long n;
    // TODO: produce output
    if(Slow)
        n = count_inversions_slow(&values[0], values.size());
    else
        n = count_inversions_fast(&values[0], values.size());
    cout << "Number of inversions: " << n;
    return 0;
}
