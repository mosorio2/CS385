/*******************************************************************************
 * Name     : waterjugpuzzle.cpp
 * Author      : Michael Osorio and Anthony Picone
 * Date        : 10/25/15
 * Description : Solves waterjug puzzle with bredth-first search.
 * Pledge      : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/

#include <iostream>
#include <string>
#include <sstream>
#include <queue>
#include <vector>

using namespace std;

int capacity_a, capacity_b, capacity_c;
int goal[2];
bool reach = 0;
string parse;

//Creates a class used for the states of each jug of water.
class JugState {
private:
	vector<string> edges;
	int jug_a;
	int jug_b;
	int jug_c;
public:
	JugState(int a, int b, int c, vector<string> adjacent);
	vector<string> get_edges();
	void create_vector();
	int get_a();
	int get_b();
	int get_c();

};

//Constructs each variable for each jug.
JugState::JugState(int a, int b, int c, vector<string> adjacent) {
	jug_a = a;
	jug_b = b;
	jug_c = c;
	edges = adjacent;
}

//Gets jug A.
int JugState::get_a() {
	return jug_a;
}

//Gets Jug B.
int JugState::get_b() {
	return jug_b;
}

//Gets jug C
int JugState::get_c() {
	return jug_c;
}

//Gets the edges for each state.
vector<string> JugState::get_edges() {
	return edges;
}

//Creates a vector for the edges of the states.
void JugState::create_vector() {
	for (unsigned int i = 0; i < edges.size(); ++i) {
		cout << edges[i] << endl;
	}
}

//Tells if the goal state has been reached.
bool goal_reached(int a, int b) {
	if ((a == goal[0]) && (b == goal[1]))
		return true;
	return false;
}

//Creates a string for formatting and testing.
string make_string(int a, int b, int c) {
	string str;
	stringstream iss;
	iss << "(" << a << ", " << b << ", " << c << ")";
	str = iss.str();
	return str;
}

//Creates the edges for the vector.
vector<string> edge_creator(int a, int b, int c) {
	vector<string> edges;
	stringstream iss;
	iss << "Initial state. (" << a << ", " << b << ", " << c << ")";
	edges.push_back(iss.str());
	return edges;
}

//Queue used in BFS.
queue<JugState> pours;

//Finds the best way to reach the goal state from the initial state
//using a breadth-first search and several different orders of pours.
void breadth(int jug_a, int jug_b, int jug_c) {
	bool **visited = new bool*[capacity_a + 1];
	for (int i = 0; i < capacity_a + 1; ++i) {
		visited[i] = new bool[capacity_b + 1];
		// Fill the array with zeros.
		fill(visited[i], visited[i] + capacity_b + 1, false);
	}
	JugState states(jug_a, jug_b, jug_c, edge_creator(jug_a, jug_b, jug_c));
	pours.push(states);
	while (!pours.empty()) {
		jug_a = pours.front().get_a();
		jug_b = pours.front().get_b();
		jug_c = pours.front().get_c();
		visited[jug_a][jug_b] = true;
		if (goal_reached(jug_a, jug_b)) {
			pours.front().create_vector();
			reach = 1;
			break;
		}
		JugState top = pours.front();
		pours.pop();

		//Pours from jug A to jug C.
		if (jug_a < capacity_a) {
			int a = jug_a + jug_c;
			int b = jug_b;
			if (a > capacity_a)
				a = capacity_a;
			int c = jug_c - (a - jug_a);
			if (b > capacity_b)
				b = capacity_b;
			stringstream iss;
			if ((a - jug_a) > 1) {
				iss << a - jug_a;
				parse = "Pour " + iss.str() + " gallons from C to A. ";
			} else {
				iss << a - jug_a;
				parse = "Pour " + iss.str() + " gallon from C to A. ";
			}
			//if visited
			if (!visited[a][b]) {
				vector<string> way = top.get_edges();
				way.push_back(parse + make_string(a, b, c));
				JugState c_a(a, b, c, way);
				pours.push(c_a);
			}
		}

		//Pours from jug B to jug A.
		if (jug_a < capacity_a) {
			if (jug_b != 0) {
				int c = jug_c;
				int a = jug_a + jug_b;
				if (a > capacity_a)
					a = capacity_a;
				int b = jug_b - (a - jug_a);
				if (b < 0)
					b = 0;
				if (b > capacity_b)
					b = capacity_b;
				//if visited
				stringstream iss;
				if ((jug_b - b) > 1) {
					iss << jug_b - b;
					parse = "Pour " + iss.str() + " gallons from B to A. ";
				} else {
					iss << jug_b - b;
					parse = "Pour " + iss.str() + " gallon from B to A. ";
				}
				if (!visited[a][b]) {
					vector<string> way = top.get_edges();
					way.push_back(parse + make_string(a, b, c));
					JugState b_a(a, b, c, way);
					pours.push(b_a);
				}
			}
		}

		//Pours from jug C to jug B.
		if (jug_b < capacity_b) {
			int b = jug_c + jug_b;
			int a = jug_a;
			if (b > capacity_b)
				b = capacity_b;
			int c = jug_c - (b - jug_b);
			if (a > capacity_a)
				a = capacity_a;
			stringstream iss;
			if ((b - jug_b) > 1) {
				iss << b - jug_b;
				parse = "Pour " + iss.str() + " gallons from C to B. ";
			} else {
				iss << b - jug_b;
				parse = "Pour " + iss.str() + " gallon from C to B. ";
			}
			if (!visited[a][b]) {
				vector<string> way = top.get_edges();
				way.push_back(parse + make_string(a, b, c));
				JugState c_b(a, b, c, way);
				pours.push(c_b);
			}
		}

		//Pours from jug A to jug B.
		if (jug_b < capacity_b) {
			if (jug_a != 0) {
				int c = jug_c;
				int a;
				int b = jug_a + jug_b;
				if (b > capacity_b) {
					b = capacity_b;
					a = jug_a - (b - jug_b);
				} else
					a = 0;
				if (a < 0)
					a = 0;
				if (a > capacity_a)
					a = capacity_a;
				stringstream iss;
				if ((b - jug_b) > 1) {
					iss << b - jug_b;
					parse = "Pour " + iss.str() + " gallons from A to B. ";
				} else {
					iss << b - jug_b;
					parse = "Pour " + iss.str() + " gallon from A to B. ";
				}
				if (!visited[a][b]) {
					vector<string> way = top.get_edges();
					way.push_back(parse + make_string(a, b, c));
					JugState a_b(a, b, c, way);
					pours.push(a_b);
				}
			}
		}

		//Pours from jug B to jug C.
		if (jug_a + jug_b < capacity_c) {
			if (jug_b != 0) {
				int c = jug_c + jug_b;
				if (c > capacity_c)
					c = capacity_c;
				int b = jug_c - c;
				int a = jug_a;
				if (b > capacity_b)
					b = capacity_b;
				if (b < 0)
					b = 0;
				if (a > capacity_a)
					a = capacity_a;
				stringstream iss;
				if ((jug_b - b) > 1) {
					iss << jug_b - b;
					parse = "Pour " + iss.str() + " gallons from B to C. ";
				} else {
					iss << jug_b - b;
					parse = "Pour " + iss.str() + " gallon from B to C. ";
				}
				if (!visited[a][b]) {
					vector<string> way = top.get_edges();
					way.push_back(parse + make_string(a, b, c));
					JugState b_c(a, b, c, way);
					pours.push(b_c);
				}
			}
		}

		//Pours from jug A to jug C.
		if (jug_a + jug_b < capacity_c) {
			if (jug_a != 0) {
				int c = jug_a + jug_c;
				if (c > capacity_c)
					c = capacity_c;
				int a = jug_a - (c - jug_c);
				if (a > capacity_a)
					a = capacity_a;
				if (a < 0)
					a = 0;
				int b = jug_b;
				stringstream iss;
				if ((jug_a - a) > 1) {
					iss << jug_a - a;
					parse = "Pour " + iss.str() + " gallons from A to C. ";
				} else {
					iss << jug_a - a;
					parse = "Pour " + iss.str() + " gallon from A to C. ";
				}
				if (!visited[a][jug_b]) {
					vector<string> way = top.get_edges();
					way.push_back(parse + make_string(a, b, c));
					JugState a_c(a, b, c, way);
					pours.push(a_c);
				}
			}
		}
	}
	if (!reach)
		cout << "No solution." << endl;

	for (int i = 0; i <= capacity_a; ++i) {
		delete[] visited[i];
	}

	delete[] visited;
}

//Main function for calling, formatting the program, and testing.
int main(int argc, char * const argv[]) {

	if (argc != 7) {
		cerr << "Usage: " << argv[0]
				<< " <cap A> <cap B> <cap C> <goal A> <goal B> <goal C>"
				<< endl;
		return 1;
	}

	for (int i = 1; i <= 6; ++i) {
		int temp;
		istringstream iss(argv[i]);
		if (!(iss >> temp) || (temp < 0) || (temp == 0 && i == 3)) {
			if (i == 1) {
				cerr << "Error: Invalid capacity '" << argv[i] << "' for jug A."
						<< endl;
				return 1;
			}
			if (i == 2) {
				cerr << "Error: Invalid capacity '" << argv[i] << "' for jug B."
						<< endl;
				return 1;
			}
			if (i == 3) {
				cerr << "Error: Invalid capacity '" << argv[i] << "' for jug C."
						<< endl;
				return 1;
			}
			if (i == 4) {
				cerr << "Error: Invalid goal '" << argv[i] << "' for jug A."
						<< endl;
				return 1;
			}
			if (i == 5) {
				cerr << "Error: Invalid goal '" << argv[i] << "' for jug B."
						<< endl;
				return 1;
			}
			if (i == 6) {
				cerr << "Error: Invalid goal '" << argv[i] << "' for jug C."
						<< endl;
				return 1;
			}
		}
	}
	for (int i = 1, j = 4; i <= 3 && j <= 6; i++, j++) {
		int temp_i, temp_j;
		istringstream iss_i(argv[i]);
		iss_i >> temp_i;
		istringstream iss_j(argv[j]);
		iss_j >> temp_j;
		if ((temp_j > temp_i) && i == 1) {
			cerr << "Error: Goal cannot exceed capacity of jug A." << endl;
			return 1;
		}
		if ((temp_j > temp_i) && i == 2) {
			cerr << "Error: Goal cannot exceed capacity of jug B." << endl;
			return 1;
		}
		if ((temp_j > temp_i) && i == 3) {
			cerr << "Error: Goal cannot exceed capacity of jug C." << endl;
			return 1;
		}
	}

	int sum, max;
	sum = 0;
	istringstream iss(argv[3]);
	iss >> max;
	for (int i = 4; i <= 6; ++i) {
		int temp;
		istringstream it(argv[i]);
		it >> temp;
		sum += temp;
	}
	if (sum != max) {
		cerr
				<< "Error: Total gallons in goal state must be equal to the capacity of jug C."
				<< endl;
		return 1;
	}

	for (int i = 4; i <= 6; ++i) {
		istringstream iss(argv[i]);
		int temp;
		iss >> temp;
		goal[i - 4] = temp;
	}
	istringstream iss1(argv[1]);
	int temp;
	iss1 >> temp;
	capacity_a = temp;
	istringstream iss2(argv[2]);
	iss2 >> temp;
	capacity_b = temp;
	istringstream iss3(argv[3]);
	iss3 >> temp;
	capacity_c = temp;

	breadth(0, 0, capacity_c);
}
