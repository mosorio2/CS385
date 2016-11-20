/*******************************************************************************
 * Name: sieve.cpp
 * Author: Michael Osorio
 * Date:  9/18/15      :
 * Description : Sieve of Eratosthenes
 * Pledge : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/
#include <cmath>
#include <iomanip>
#include <iostream>
#include <sstream>

using namespace std;

/*
 * creates class for the Sieve of Eratosthenes
 */
class PrimesSieve {
public:
	/*
	 * Constructor
	 */
    PrimesSieve(int limit) : is_prime_(new bool[limit + 1]), limit_(limit) {
        for(int i = 0; i <= limit; i++)
        {
        	is_prime_[i] = true;
        }
    	sieve();
    	num_primes_ = count_num_primes();
    }

    /*
     * Deconstructor
     */
    ~PrimesSieve() {
        delete [] is_prime_;
    }

    /*
     * Number of primes
     */
    inline int num_primes() const {
        return num_primes_;
    }

    /*
     * Makes display for the sieve according to a given format
     */
    void display_primes() const {
    	const int max_prime_width = num_digits(max_prime_);
    	const int primes_per_row = 80 / (max_prime_width + 1);
        	if(num_primes_ >= primes_per_row)
        	{
        		int counter = 0;
        		for(int i = 2; i <= limit_; i++)
        		{
        			if(counter <= primes_per_row)
        			{
        				if (is_prime_[i] == true && i < max_prime_)
        				{
        					cout  << setw(max_prime_width) << i << " ";
        					counter++;
        				}
        				else
        				{
        					if (is_prime_[i] == true)
        					{
        						cout << setw(max_prime_width) << i;
        						counter++;
        					}
        				}
        			}
        			else
        			{
        				counter = 0;
        				cout << endl;
        			}
        		}
        	}
        	else
        	{
        		for(int i = 2; i <= limit_; i++)
        		{
        			if (is_prime_[i] == true)
        			{
        				cout << i;
        			}
        			int counter = 0;
        			if(is_prime_[i+1] == true)
        			{
        				cout << " ";
        				counter++;
        			}
        			else
        			{
        				counter = 0;
        			}
        		}
        	}
    }

private:
    bool * const is_prime_;
    const int limit_;
    int num_primes_, max_prime_;

    /*
     * Counts the number of primes in the sieve
     */
    int count_num_primes()  {
    	for (int i = 2; i <= limit_; i++)
    	{
    		if (is_prime_[i] == true)
    		{
    			num_primes_++;
    			max_prime_ = i;
    		}
    	}
    	return num_primes_;
    }

    /*
     * Number of digits in a number in the sieve.
     */
    int num_digits(int num) const {
    	int count = 1;
    	while (num/10 != 0)
    	{
    		num = num/10;
    		count++;
    	}
    	return count;
    }

    /*
     * Creates sieve for prime numbers.
     */
    void sieve() {
    	for (int i = 2; i <= sqrt(limit_); i++)
    	{
    		if (is_prime_[i])
    		{
    			for (int j = i*i; j <= limit_; j+=i)
    			{
    				is_prime_[j] = false;
    			}
    		}
    	}
    }
};

/*
 * Main function for calling methods and testing.
 */
int main(void) {
    cout << "**************************** " <<  "Sieve of Eratosthenes" <<
            " ****************************" << endl;
    cout << "Search for primes up to: ";
    string limit_str;
    cin >> limit_str;
    int limit;

    // Use stringstream for conversion. Don't forget to #include <sstream>
    istringstream iss(limit_str);

    // Check for error.
    if ( !(iss >> limit) ) {
        cerr << "Error: Input is not an integer." << endl;
        return 1;
    }
    if (limit < 2) {
        cerr << "Error: Input must be an integer >= 2." << endl;
        return 1;
    }
    cout << endl;
    PrimesSieve sieve1(limit);
    cout << "Number of primes found: " << sieve1.num_primes() << endl;
    cout << "Primes up to " << limit << ":" << endl;
    sieve1.display_primes();
    return 0;
}
