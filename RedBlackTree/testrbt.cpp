/*******************************************************************************
 * Name          : testrbt.cpp
 * Author        : Brian S. Borowski
 * Version       : 1.1
 * Date          : October 8, 2014
 * Last modified : April 9, 2015
 * Description   : Driver program to test implementation of red-black tree.
 ******************************************************************************/
#include "rbtree.h"
#include <iostream>
#include <sstream>
#include <iomanip>
#include <sstream>
#include <string>

using namespace std;

Tree *rbt;
RedBlackTree<int, int> *rbti;
RedBlackTree<string, string> *rbts;
bool using_ints = false;

string inorder_traversal() {
    ostringstream oss;
    oss << "[";
    if (using_ints) {
        RedBlackTree<int, int>::iterator it = rbti->begin();
        while (it != rbti->end()) {
            if (it != rbti->begin()) {
                oss << ", ";
            }
            oss << (*it).first;
            ++it;
        }
    } else {
        RedBlackTree<string, string>::iterator it = rbts->begin();
        while (it != rbts->end()) {
            if (it != rbts->begin()) {
                oss << ", ";
            }
            oss << (*it).first;
            ++it;
        }
    }
    oss << "]";
    return oss.str();
}

void test_find() {
    if (using_ints) {
        RedBlackTree<int, int>::iterator it = rbti->begin();
        while (it != rbti->end()) {
            int key = (*it).first;
            if (rbti->find(key) == rbti->end()) {
                ostringstream oss;
                oss << "Cannot find key '" << key << "' in tree.";
                throw tree_exception(oss.str());
            }
            ++it;
        }
    } else {
        RedBlackTree<string, string>::iterator it = rbts->begin();
        while (it != rbts->end()) {
            string key = (*it).first;
            if (rbts->find(key) == rbts->end()) {
                throw tree_exception("Cannot find key '" + key + "' in tree.");
            }
            ++it;
        }
    }
}

int main(int argc, char *argv[]) {
    if (argc > 1) {
        istringstream iss(argv[1]);
        int value;
        if (iss >> value) {
            using_ints = true;
        }
    }

    if (using_ints) {
        rbt = new RedBlackTree<int, int>();
        rbti = static_cast<RedBlackTree<int, int> *>(rbt);
    } else {
        rbt = new RedBlackTree<string, string>();
        rbts = static_cast<RedBlackTree<string, string> *>(rbt);
    }

    if (using_ints) {
        for (int i = 1; i < argc; ++i) {
            istringstream iss(argv[i]);
            int value;
            if (!(iss >> value)) {
                cerr << "Error: Invalid integer '" << argv[i]
                     << "' found at index " << i << "." << endl;
                return 1;
            }
            try {
                rbti->insert(value, value);
            } catch (const tree_exception &te) {
                cerr << "Warning: " << te.what() << endl;
            }
        }
    } else {
        for (int i = 1; i < argc; ++i) {
            try {
                static_cast<RedBlackTree<string, string> *>(rbt)->insert(argv[i], argv[i]);
            } catch (const tree_exception &te) {
                cerr << "Warning: " << te.what() << endl;
            }
        }
    }

    cout << rbt->to_ascii_drawing() << endl << endl;
    cout << "Height:                   " << rbt->height() << endl;
    cout << "Total nodes:              " << rbt->size() << endl;
    cout << "Leaf count:               " << rbt->leaf_count() << endl;
    cout << "Internal nodes:           " << rbt->internal_node_count() << endl;
    cout << "Diameter:                 " << rbt->diameter() << endl;
    cout << "Maximum width:            " << rbt->max_width() << endl;
    cout << fixed;
    cout << "Successful search cost:   " << setprecision(3)
         << rbt->successful_search_cost() << endl;
    cout << "Unsuccessful search cost: " << setprecision(3)
         << rbt->unsuccessful_search_cost() << endl;
    cout << "Inorder traversal:        " << inorder_traversal() << endl;

    try {
        test_find();
    } catch (const tree_exception &te) {
        cerr << "Error: " << te.what() << endl;
    }

    delete rbt;
    return 0;
}
