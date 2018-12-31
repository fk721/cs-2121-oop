// Fahmid Kamal
// fk786
// Practicing Linked Lists

#include <iostream>
#include <vector>
using namespace std;

struct Node {
	Node(int data = 0, Node* next = nullptr) : data(data), next(next) {}
	int data;
	Node* next;
};


void listInsertHead(Node*& headPtr, int entry) {
	headPtr = new Node(entry, headPtr);
}

void listClear(Node*& headPtr) {
	while (headPtr) {
		Node* next = headPtr->next;
		delete headPtr;
		headPtr = next;
	}
}


Node* listBuild(const vector<int>& vals) {
	Node* result = nullptr;
	for (size_t index = vals.size(); index > 0; --index) {
		listInsertHead(result, vals[index - 1]);
	}
	return result;
}

void listDisplay(const Node* headPtr) {
	// Declare a temporary variable to use to "walk down" the list.
	const Node* p = headPtr;
	// Loop through the list.  Note the test condition.  If p is NULL
	// that means that we are not pointing to a node anymore.
	while (p != nullptr) {
		// If we came into the loop then we must be pointing to a node
		// so display the data.
		cout << p->data << ' ';
		// Now we need to set the pointer to the point to the next node.
		// Be careful to note that we CANNOT just say, "p++;".  Be sure
		// that you know why!
		p = p->next;
	}
	cout << endl;
}

// Task 1

void splice(Node*& original, Node*& spliced) {
	// 1. Make the next of original point to spliced
	// 2. Have the next of splice point to what was once the next of original
	// What is the next of original? What is the next of splice?
	Node* originalNext = original->next;
	Node* splicedNext = spliced;
	while (splicedNext->next) { // != nullptr
		splicedNext = splicedNext->next;
	}
	original->next = spliced;
	splicedNext->next = originalNext;
}

// Task 2

bool isSubListHelper(Node* searchHeadPtr, Node* subListHeadPtr) {
	Node* resNode = nullptr;
	while (searchHeadPtr && subListHeadPtr) {
		if (searchHeadPtr->data != subListHeadPtr->data) {
			return false;
		}
		else {
			searchHeadPtr = searchHeadPtr->next;
			subListHeadPtr = subListHeadPtr->next;
		}
	}
	if (!subListHeadPtr) { return true; }
	return false;
}

Node* isSublist(Node* lookingFor, Node* lookingIn) {
	Node* searchHeadPtr = lookingFor;
	Node* subListHeadPtr = lookingIn;
	Node* resNode = nullptr;
	while (searchHeadPtr) {
		if (searchHeadPtr->data == subListHeadPtr->data) {
			bool res = isSubListHelper(searchHeadPtr, subListHeadPtr);
			if (res) { return searchHeadPtr; }
			else { searchHeadPtr = searchHeadPtr->next; subListHeadPtr = lookingIn; }
		}
		else { searchHeadPtr = searchHeadPtr->next; }
	}
	// couldn't find anything, failed to match
	return resNode;
}

// Task 3

Node* sharedListBruteForce(Node* listOne, Node* listTwo) {
	int sizeListOne = 0;
	int sizeListTwo = 0;
	Node* tailOne = listOne;
	Node* tailTwo = listTwo;
	while (tailOne->next) {
		++sizeListOne;
		tailOne = tailOne->next;
	}
	while (tailTwo->next) {
		++sizeListTwo;
		tailTwo = tailTwo->next;
	}
	// If the two lists "intersect", then they should have the same last node
	if (tailOne != tailTwo) { return nullptr; }
	// Make listOne the "Longer List"
	if (sizeListTwo > sizeListOne) {
		int temp;
		temp = sizeListOne;
		sizeListOne = sizeListTwo;
		sizeListTwo = temp;
		Node* tempNode = nullptr;
		tempNode = listOne;
		listOne = tailTwo;
		listTwo = tempNode;
	}
	//  Give listOne a "head start" so we can make the lists the same lengths
	for (size_t i = 0; i < (sizeListOne - sizeListTwo); ++i) {
		listOne = listOne->next;
	}
	// Now iterate together
	while (listOne && listTwo) {
		if (listOne == listTwo) {
			return listOne;
		}
		listOne = listOne->next;
		listTwo = listTwo->next;
	}
}

int main() {
	cout << "Part One:\n";
	vector<int> testOne{ 5,7,9,1}; Node* listOne = listBuild(testOne);
	vector<int> testTwo{ 6,3,2 }; Node* listTwo = listBuild(testTwo);
	Node* target = listOne->next; // Node of val 7
	cout << "L1: "; listDisplay(listOne);
	cout << "L2: "; listDisplay(listTwo);
	cout << "Target: "; listDisplay(target);
	cout << "Splicing L2 at Target in T1\n";
	splice(target, listTwo);
	cout << "L1: "; listDisplay(listOne);
	cout << "L2: "; listDisplay(listTwo);
	cout << "============================\n\n";
	cout << "Part Two:\n";
	vector<int> testThree{ 1,2,3,2,3,2,4,5,6 }; Node* listThree = listBuild(testThree);
	// Note: Modify testFour vector to change the attempted match
	vector<int> testFour{2,3,2,4}; Node* listFour = listBuild(testFour);
	cout << "Target: "; listDisplay(listThree);
	cout << "Attempt match: "; listDisplay(listFour);
	Node* res = isSublist(listThree, listFour);
	if (res) { listDisplay(res); }
	else { cout << "Failed to match\n"; }
	cout << "============================\n\n";

	// Get things off of the heap
	listClear(listOne);
	//listClear(listTwo); // listTwo is a part of listOne at this point, don't have to delete
	listClear(listThree);
	listClear(listFour);
}