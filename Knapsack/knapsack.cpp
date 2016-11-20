/*******************************************************************************
 * Name: knapsack.cpp
 * Author: Michael Osorio
 * Date:  9/18/15      :
 * Description : Knapsack problem
 * Pledge : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

struct Item {
	unsigned int item_number, weight, value;
	string description;
	explicit Item(const unsigned int item_number, const unsigned int weight,
			const unsigned int value, const string &description) :
			item_number(item_number), weight(weight), value(value), description(
					description) {
	}

	friend ostream& operator<<(ostream& os, const Item &item) {
		os << "Item " << item.item_number << ": " << item.description << " ("
				<< item.weight << (item.weight == 1 ? " pound" : " pounds")
				<< ", $" << item.value << ")";
		os.flush();
		return os;
	}
};

/*
 * finds max of two integers
 */
int max(int i, int j) {
	if (i >= j) {
		return i;
	}

	else {
		return j;
	}
}

/*
 * creates array that contains all items and their info
 */
vector<vector<unsigned int> > knapsack(unsigned int cap, vector<Item> items,
		unsigned int n) {
	vector<vector<unsigned int> > K(n + 1, vector<unsigned int>(cap + 1));
	for (unsigned int i = 0; i <= n; ++i) {
		for (unsigned int j = 0; j <= cap; ++j) {
			if (i == 0 || j == 0) {
				K[i][j] = 0;
			}

			else if (items[i - 1].weight <= j) {
				K[i][j] = max(
						items[i - 1].value + K[i - 1][j - items[i - 1].weight],
						K[i - 1][j]);
			}

			else {
				K[i][j] = K[i - 1][j];
			}
		}
	}

	return K;
}
/*
 * splits information to be read
 */
void reader(const string &s, vector<string> &things, char delim) {
	things.clear();
	stringstream ss(s);
	string item;
	while (getline(ss, item, delim)) {
		things.push_back(item);
	}
}

/*
 * main function for testing and parsing.
 */
int main(int argc, char * const argv[]) {
	vector<string> things;
	vector<Item> items;
	ifstream ifs(argv[2]);
	int capacity;
	int weight;
	int value;
	int line = 1;

	if (argc != 3) {
		cerr << "Usage: ./knapsack <capacity> <filename>";
		return -1;
	}

	stringstream iss(argv[1]);

	if (!(iss >> capacity) || (capacity < 0)) {
		cerr << "Error: Bad value '" << argv[1] << "' for capacity." << endl;
		return -1;
	}

	string inrf;
	if (ifs.is_open()) {
		while (getline(ifs, inrf)) {
			string descriptionA;
			string description_again;
			string description;
			reader(inrf, things, ',');

			if (things.size() != 3) {
				cerr << "Error: Line number " << line
						<< " does not contain 3 fields." << endl;
				return -1;
			}

			stringstream iss;
			iss.str(things[0]);
			iss >> descriptionA;
			getline(iss, description_again);
			description = descriptionA + description_again;

			bool in_weight = istringstream(things[1]) >> weight;

			if ((!in_weight) || (weight < 0)) {
				cerr << "Error: Invalid weight '" << things[1]
						<< "' on line number " << line << "." << endl;
				return -1;
			}

			bool isintvalue = istringstream(things[2]) >> value;
			if ((!isintvalue) || (value < 0)) {
				cerr << "Error: Invalid value '" << things[2]
						<< "' on line number " << line << "." << endl;
				return -1;
			}
			Item item = Item(line, weight, value, description);
			items.push_back(item);
			line++;
		}

		ifs.close();
		cout << "Candidate items to place in knapsack:\n";

		for (unsigned int i = 0; i < items.size(); i++)
			cout << "   " << items[i] << "\n";

		vector<vector<unsigned int> > ksack = knapsack(capacity, items,
				items.size());
		int n = items.size();
		vector<int> in_bag;
		int total_value = ksack[n][capacity];
		int sum_weight = 0;

		if (capacity > 1) {
			cout << "Capacity: " << capacity << " pounds\n";
		} else {
			cout << "Capacity: " << capacity << " pound\n";
		}

		while ((n > 0) && (capacity > 0)) {
			if (ksack[n][capacity] != ksack[n - 1][capacity]) {
				n = n - 1;
				capacity = capacity - items[n].weight;
				in_bag.push_back(n);
			} else
				n = n - 1;
		}

		cout << "Items to place in knapsack:\n";

		for (int i = in_bag.size() - 1; i >= 0; i--) {
			cout << "   " << items[in_bag[i]] << "\n";
			sum_weight += items[in_bag[i]].weight;
		}

		if (in_bag.size() > 1) {
			cout << "Total weight: " << sum_weight << " pounds\n";
		} else {
			cout << "Total weight: " << sum_weight << " pound\n";
		}

		cout << "Total value : $" << total_value;
	}

	else {
		cerr << "Error: Cannot open file '" << argv[2] << "'." << endl;
		return -1;
	}

	return 0;
}
