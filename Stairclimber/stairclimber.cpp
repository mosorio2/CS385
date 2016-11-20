/*******************************************************************************
 * Name     : stairclimber.cpp
 * Author      : Michael Osorio
 * Date        : 10/2/15
 * Description : Lists the number of ways to climb n stairs.
 * Pledge      : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/
#include <iostream>
#include <vector>
#include <algorithm>
#include <sstream>
#include <iomanip>

using namespace std;

vector< vector<int> > varname;
vector<int> way;
int size;

/* Return a vector of vectors of ints representing
 * the different combinations of ways to climb num_stairs
 * stairs, moving up either 1, 2, or 3 stairs at a time.*/
vector< vector<int> > get_ways(int num_stairs) {
	if (num_stairs == 0)
	{
		varname.push_back(way);
	}
	if (num_stairs >= 1)
	{
		way.push_back(1);
		get_ways(num_stairs-1);
		way.pop_back();
	}
	if (num_stairs >= 2)
	{
		way.push_back(2);
		get_ways(num_stairs-2);
		way.pop_back();
	}
	if (num_stairs >= 3)
	{
		way.push_back(3);
		get_ways(num_stairs-3);
		way.pop_back();
	}
	else
	{
		return varname;
	}
	return varname;
}

/*Display the ways to climb stairs by iterating over
 * the vector of vectors and printing each combination.
 */
void display_ways(const vector< vector<int> > &ways) {
	for (unsigned int i = 0; i < ways.size(); i++)
	{
		if (ways.size() > 9)
		{
			if (i < 9)
			{
				cout << " " << i+1 << ". " << "[";
			}
			else
				cout << i+1 << ". " << "[";
	    }
		else
			cout << i+1 << ". " << "[";
		for (unsigned int j = 0; j < ways[i].size(); j++)
		{
			if (j != ways[i].size()-1)
				cout << ways[i][j] << ", ";
			else
				cout << ways[i][j];
		}
		cout << "]" << endl;
	}
}

/* Main function for testing and calling methods
 *
 */
int main(int argc, char * const argv[]) {
	if (argc != 2)
	{
		cerr << "Usage: " << argv[0] << " <number of stairs>" << endl;
		return 1;
	}
	if (atoi(argv[1]) <= 0)
	{
		cerr << "Error: Number of stairs must be a positive integer." << endl;
		return 1;
	}
	vector< vector<int> > ways = get_ways(atoi(argv[1]));
	if (atoi(argv[1]) == 1)
	{
		cout << "1 way to climb 1 stair." << endl;
	}
	else
	{
		cout << varname.size() << " ways to climb " << argv[1] << " stairs." << endl;
	}
	display_ways(ways);
}
