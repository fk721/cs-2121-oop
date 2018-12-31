/* Fahmid Kamal
	Lab 13 | Tutorial Lab on STL, iterators, containers,
			 templated classes, algorithms
*/
#include <iostream>
#include <fstream>
#include <vector>      // task 1
#include <list>        // task 2
#include <algorithm>   // task 3
#include <string>      // task 21
#include <set>         // task 22
#include <map>         // task 23
using namespace std;

// Task 16
class isEvenFunctor {
public:
	bool operator()(int val) { return val % 2 == 0; }
};

// Task 9
// Must use const iter if passing in a const list
void displayListUsingIterators(const list<int>& l1) {
	cout << "Displaying list using iterators\n";
	for (list<int>::const_iterator start = l1.begin(); start != l1.end(); ++start) {
		cout << *start << " ";
	}
}

// Task 10
// No problemo with const list
void displayListUsingRangedFor(const list<int>& l1) {
	cout << "Displaying list using ranged for\n";
	for (int x : l1) {
		cout << x << ' ';
	}
}

// Task 11
void displayListUsingIteratorsAuto(const list<int> & l1) {
	cout << "Displaying list using iterators and AUTO \n";
	for (auto start = l1.begin(); start != l1.end(); ++start) {
		cout << *start << " ";
	}
}

// Task 12
list<int>::const_iterator findListVal(const list<int>& l1, int target) {
	for (list<int>::const_iterator start = l1.begin(); start != l1.end(); ++start) {
		if (*start == target) { return start; }
	}
	return l1.end();
}

// Task 13, modified, with auto
auto findListValAuto(const list<int>& l1, int target) {
	for (auto start = l1.begin(); start != l1.end(); ++start) {
		if (*start == target) { return start; }
	}
	return l1.end();
}

// Tasl 15
bool isEven(int val) {
	return val % 2 == 0;
}

// Task 19

/* list<int>::iterator ourFind(list<int>::iterator start, list<int>::iterator end, int target) {
	for (start; start != end; ++start) {
		if (*start == target) { return start; }
	}
	cerr << "Could not find target in list\n";
	return end;
} */

// Task 20
template<class T, class U>
T ourFind(T start, T end, U target) {
	for (start; start != end; ++start) {
		if (*start == target) { return start; }
	}
	cerr << "Could not find target in list\n";
	return end;
}

int main() {
	// 1. Create a vector with some values and display using ranged for
	cout << "Task 1:\n";
	vector<int> v1({ 12,5,21,34,63,21,24,27 });
	for (int x : v1) {
		cout << x << ' ';
	}
	cout << "\n=======\n";
	// 2. Initalize a list as a copy of values from the vector
	cout << "Task 2:\n";
	list<int> l1({ v1.begin(), v1.end() });
	for (int x : l1) {
		cout << x << ' ';
	}
	cout << "\n=======\n";

	// 3. Sort the original vector.  Display both the vector and the list
	cout << "Task 3:\n";
	sort(v1.begin(), v1.end());
	cout << "Printing vector v1 after sort\n";
	for (int x : v1) {
		cout << x << ' ';
	}
	cout << "\nPrinting list l1\n";
	for (int x : l1) {
		cout << x << ' ';
	}
	cout << "\n=======\n";

	// 4. print every other element of the vector.
	cout << "Task 4:\n";
	cout << "Printing every other element of the vector\n";
	for (size_t i = 0; i < v1.size(); i += 2) {
		cout << v1[i] << ' ';
	}
	cout << "\n=======\n";
	// 5. Attempt to print every other element of the list using the
	//    same technique.
	cout << "Task 5:\nCommented out, list does not have [] operator";
	/*
	cout << "Printing every other element of the list\n";
	for (size_t i = 0; i < l1.size(); ++++i) {
		cout << l1[i] << ' ';
	}
	*/
	cout << "\n=======\n";

	//
	// Iterators
	//

	// 6. Repeat task 4 using iterators.  Do not use auto;
	cout << "Task 6:\nUsing iterators to print out every other element of vector v1\n";
	for (vector<int>::iterator iter = v1.begin(); iter != v1.end(); iter += 2) {
		cout << *iter << ' ';
	}
	cout << "\n=======\n";

	// 7. Repeat the previous task using the list.  Again, do not use auto.
	//    Note that you cannot use the same simple mechanism to bump
	//    the iterator as in task 6.
	cout << "Task 7:\nUsing iterators to print out every other element of list l1\n";
	// Note: List iters do not support random access
	for (list<int>::iterator iter = l1.begin(); iter != l1.end(); ++++iter) {
		cout << *iter << ' ';
	}
	cout << "\n=======\n";
	// 8. Sorting a list
	cout << "Task 8:\n";
	cout << "Before the sort, list l1 is:\n";
	for (list<int>::iterator iter = l1.begin(); iter != l1.end(); ++iter) {
		cout << *iter << ' ';
	}
	cout << "\nAfter the sort, list l2 is:\n";
	l1.sort();
	for (list<int>::iterator iter = l1.begin(); iter != l1.end(); ++iter) {
		cout << *iter << ' ';
	}
	cout << "\n=======\n";

	// 9. Calling the function to print the list
	cout << "Task 9:\n";
	displayListUsingIterators(l1);
	cout << "\n=======\n";

	// 10. Calling the function that prints the list, using ranged-for
	cout << "Task 10:\n";
	displayListUsingRangedFor(l1);
	cout << "\n=======\n";

	//
	// Auto
	//

	// 11. Calling the function that, using auto, prints alterate
	// items in the list
	cout << "Task 11:\n";
	displayListUsingIteratorsAuto(l1);
	cout << "\n=======\n";


	// 12.  Write a function find that takes a list and value to search for.
	//      What should we return if not found
	cout << "Task 12:\n";
	cout << "Searching for 12 in list l1\n";
	list<int>::const_iterator val1 = findListVal(l1, 12);
	if (val1 != l1.end()) { cout << "12 is in l1\n"; }
	else { cout << "12 is not in l1\n";}
	cout << "Search for 100 in list l1\n";
	list<int>::const_iterator val2 = findListVal(l1, 100);
	if (val2 != l1.end()) { cout << "100 is in l1\n"; }
	else { cout << "100 is not in l1\n"; }
	cout << "=======\n";

	// 13.  Write a function find that takes a list and value to search for.
	//      What should we return if not found
	cout << "Task 13:\n";
	cout << "Finding the list value using auto\n";
	cout << "Searching for 12 in list l1\n";
	auto val3 = findListValAuto(l1, 12);
	if (val3 != l1.end()) { cout << "12 is in l1\n"; }
	else { cout << "12 is not in l1\n"; }
	cout << "Searching for 100 in list l1\n";
	auto val4 = findListVal(l1, 100);
	if (val4 != l1.end()) { cout << "100 is in l1\n"; }
	else { cout << "100 is not in l1\n"; }
	cout << "=======\n";

	//
	// Generic Algorithms
	//

	// 14. Generic algorithms: find
	cout << "Task 14:\nUsing find algorithm\n";
	list<int>::iterator val5 = find(l1.begin(), l1.end(), 12);
	// auto val = find(l1.begin(), l1.end(), 12);
	cout << "Searching for 12 in list l1 using generic algorithm find\n";
	if (val5 != l1.end()) { cout << "12 is in l1\n"; }
	else { cout << "12 is not in l1\n"; } 
	cout << "=======\n";
	// 15. Generic algorithms: find_if
	cout << "Task 15:\n";
	cout << "Using a function to find the first even element\n";
	list<int>::iterator evenVal1 = find_if(l1.begin(), l1.end(), isEven);
	cout << "The first even element in list l1 is " << *evenVal1 << endl;
	cout << "=======\n";
	// 16. Functor
	cout << "Task 16:\n";
	cout << "Using a functor to find the first even element\n";
	list<int>::iterator evenVal2 = find_if(l1.begin(), l1.end(), isEvenFunctor());
	cout << "The first even element in list l1 is " << *evenVal2;
	cout << "\n=======\n";

	// 17. Lambda
	cout << "Task 17:\n";
	cout << "Using lambda expressions to find the first even element\n";
	list<int>::iterator evenVal3 = find_if(l1.begin(), l1.end(), [] (int val) {return val % 2 == 0; });
	cout << "The first even element in list l1 is " << *evenVal3;
	cout << "\n=======\n";

	// 18. Generic algorithms: copy to an array
	cout << "Task 18:\nUsing copy\n";
	int a1[8];
	copy(l1.begin(), l1.end(), a1);
	cout << "The contents in array a1 are:\n";
	for (size_t i = 0; i < 8; ++i) {
		cout << a1[i] << ' ';
	}
	int* where  = find_if(a1, a1 + 8, isEven);
	cout << "The first even value in array a1 is " << *where;
	cout << "\n=======\n";
	//
	// Templated Functions
	//

	// 19. Implement find as a function for lists
	cout << "Task 19:\n";
	cout << "Using ourFind to search for 21\n";
	list<int>::iterator where2 = ourFind(l1.begin(), l1.end(), 21);
	if (where2 == l1.end()) {
		cerr << "Could not find 21 in list l1\n";
	}
	else {cout << "21 is in list l1\n";}
	cout << "=======\n";

	// 20. Implement find as a templated function
	cout << "Task 20:\n";
	cout << "Using the templated function ourFind to search for 21\n";
	list<int>::iterator where3 = ourFind(l1.begin(), l1.end(), 21);
	if (where3 == l1.end()) {
		cerr << "Could not find 21 in list\n";
	}
	else {cout << "21 is in list l1\n";}
	cout << "=======\n";

	//
	// Associative collections
	//

	// 21. Using a vector of strings, print a line showing the number
	//     of distinct words and the words themselves.
	cout << "Task 21:\n";
	vector<string> poohVector;
	string word;
	ifstream ifs("pooh-nopunc.txt");
	if (!ifs) {
		cerr << "Couldn't open the pooh file.\n";
	}
	while (ifs >> word) {
		if (find(poohVector.begin(), poohVector.end(), word) == poohVector.end()) {
			poohVector.push_back(word);
		}
	}
	cout << "Contents of poohVector\nSize: " << poohVector.size() << endl;
	for (string word : poohVector) {
		cout << word << ' ';
	}
	cout << "\n=======\n";

	// 22. Repeating previous step, but using the set
	cout << "Task 22:\n";
	set<string> poohSet;
	ifs.clear();
	ifs.seekg(0);
	while (ifs >> word) {
		poohSet.insert(word);
	}
	cout << "Contents of poohSet \nSize: " << poohSet.size() << endl;
	for (string word : poohSet) {
		cout << word << ' ';
	}
	cout << "\n=======\n";

	// 23. Word co-occurence using map
	cout << "Task 23:\n";
	map<string, vector<int>> poohMap;
	int position(1);
	ifs.clear();
	ifs.seekg(0);
	while (ifs >> word) {
		poohMap[word].push_back(position);
		position += 1;
	}
	cout << "Contents of poohMap \nSize: " << poohMap.size() << endl;
	for (auto val: poohMap) {
		cout << val.first << ":\t";
		for (int x : val.second) {
			cout << x << ' ';
		}
		cout << endl;
	}
	cout << "=======\n";
	ifs.close();
}