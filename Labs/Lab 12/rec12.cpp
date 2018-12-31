// Fahmid Kamal
// fk786, rec12
// A doubly linked list class with copy control

// #include <cstdlib>
#include <iostream>
using namespace std;

class List {
	struct Node {
		Node(int data = 0, Node* next = nullptr, Node* prior = nullptr) :
			data(data), next(next), prior(prior) {}
		int data;
		Node* next;
		Node* prior;
	};
	friend ostream& operator<<(ostream& os, const List& rhs) {
		Node* currNode = rhs.header->next;
		while (currNode != rhs.trailer) {
			os << currNode->data << ' ';
			currNode = currNode->next;
		}
		return os;
	}
public:
	class iterator {
		friend List;
		friend bool operator==(const iterator& lhs, const iterator& rhs) {
			return (lhs.where == rhs.where);
		}
	public:
		iterator(Node* rhs) : where(rhs) {}
		bool operator!=(const iterator& rhs) {
			return !(*this == rhs);
		}
		int operator*() {
			return where->data;
		}
		iterator& operator++() {
			where = where->next;
			return *this;
		}
		iterator& operator--() {
			where = where->prior;
			return *this;
		}

	private:
		Node* where;
	};

	List() : theSize(0) {
		header->next = trailer;
		trailer->prior = header;
	}

	~List() {
		cout << "~List()\n";
		if (theSize != 0) {
			Node* currPointer = header->next;
			Node* nextPointer = currPointer->next;
			while (currPointer != trailer) {
				//cout << "Deleting " << currPointer->data << endl;
				delete currPointer;
				currPointer = nextPointer;
				nextPointer = nextPointer->next;
			}
		}
		//cout << "Deleteing header and trailer\n";
		delete header;
		delete trailer;
	}

	List(const List& rhs) {
		cout << "List(List)\n";
		header = new Node(rhs.header->data);
		trailer = new Node(rhs.trailer->data);
		theSize = rhs.theSize;
		Node* rhsCurrPointer = rhs.header;
		Node* lhsCurrPointer = header;
		while (rhsCurrPointer->next != rhs.trailer) {
			//cout << "Copying " << rhsCurrPointer->next->data << endl;
			Node* newNode = new Node(rhsCurrPointer->next->data);
			newNode->prior = lhsCurrPointer;
			lhsCurrPointer->next = newNode;
			lhsCurrPointer = newNode;
			rhsCurrPointer = rhsCurrPointer->next;
		}
		lhsCurrPointer->next = trailer;
		trailer->prior = lhsCurrPointer;
	}

	List& operator=(const List& rhs) {
		cout << "List::operator=(List)\n";
		if (this != &rhs) {
			if (theSize != 0) {
				Node* currPointer = header->next;
				Node* nextPointer = currPointer->next;
				while (currPointer != trailer) {
					delete currPointer;
					currPointer = nextPointer;
					nextPointer = nextPointer->next;
				}
			}
			delete header;
			delete trailer;
			header = new Node(rhs.header->data);
			trailer = new Node(rhs.trailer->data);
			theSize = rhs.theSize;
			Node* rhsCurrPointer = rhs.header;
			Node* lhsCurrPointer = header;
			while (rhsCurrPointer->next != rhs.trailer) {
				Node* newNode = new Node(rhsCurrPointer->next->data);
				newNode->prior = lhsCurrPointer;
				lhsCurrPointer->next = newNode;
				lhsCurrPointer = newNode;
				rhsCurrPointer = rhsCurrPointer->next;
			}
			lhsCurrPointer->next = trailer;
			trailer->prior = lhsCurrPointer;
		}
		return *this;
	}

	int& front() const { return header->next->data; }
	int& back() const { return trailer->prior->data; }
	size_t size() const { return theSize; }

	void push_back(int data) {
		Node* prevNode = trailer->prior;
		Node* currNode = new Node(data);
		prevNode->next = currNode;
		currNode->prior = prevNode;
		currNode->next = trailer;
		trailer->prior = currNode;
		++theSize;
	}

	void pop_back() {
		if (theSize == 0) { return; }
		Node* oldLastNode = trailer->prior;
		Node* newLastNode = oldLastNode->prior;
		newLastNode->next = trailer;
		trailer->prior = newLastNode;
		delete oldLastNode;
		--theSize;
	}

	void push_front(int data) {
		Node* nextNode = header->next;
		Node* currNode = new Node(data);
		currNode->prior = header;
		header->next = currNode;
		currNode->next = nextNode;
		nextNode->prior = currNode;
		++theSize;
	}

	void pop_front() {
		if (theSize == 0) { return; }
		Node* oldFirstNode = header->next;
		Node* newFirstNode = oldFirstNode->next;
		header->next = newFirstNode;
		newFirstNode->prior = header;
		delete oldFirstNode;
		--theSize;
	}

	void clear() {
		if (theSize == 0) { return; }
		Node* currPointer = header->next;
		Node* nextPointer = currPointer->next;
		while (currPointer != trailer) {
			delete currPointer;
			currPointer = nextPointer;
			nextPointer = nextPointer->next;
			--theSize;
		}
		header->next = trailer;
		trailer->prior = header;
	}
	
	int& operator[](size_t index)  {
		// cout << "I am  modifying this\n";
		Node* currPointer = header->next;
		for (size_t i = 0; i < index; ++i) {
			currPointer = currPointer->next;
		}
		return currPointer->data;
	}

	const int& operator[](size_t index) const  {
		// cout << "I am not modifying this\n";
		Node* currPointer = header->next;
		for (size_t i = 0; i < index; ++i) {
			currPointer = currPointer->next;
		}
		return currPointer->data;
	}

	iterator insert(iterator iter, int val) {
		Node* currNode = iter.where;
		Node* oldPriorNode = currNode->prior;
		Node* newNode = new Node(val);
		newNode->prior = oldPriorNode;
		oldPriorNode->next = newNode;
		newNode->next = currNode;
		currNode->prior = newNode;
		++theSize;
		return iterator(newNode);
	}
	iterator erase(iterator iter) {
		Node* currNode = iter.where;
		Node* priorNode = currNode->prior;
		Node* nextNode = currNode->next;
		priorNode->next = nextNode;
		nextNode->prior = priorNode;
		--theSize;
		return iterator(nextNode);
	}
	iterator begin() { return iterator(header->next); }
	iterator end() { return iterator(trailer); }

private:
	Node* header = new Node();
	Node* trailer = new Node();
	size_t theSize;
};

void printListInfo(List& myList) {
	cout << "size: " << myList.size()
		<< ", front: " << myList.front()
		<< ", back: " << myList.back()
		<< ", list: " << myList << endl;
}

// Task 8
void doNothing(List aList) {
	cout << "In doNothing\n";
	printListInfo(aList);
	cout << endl;
	cout << "Leaving doNothing\n";
}

int main() {

	// Task 1
	cout << "\n------Task One------\n";
	List myList;
	cout << "Fill empty list with push_back: i*i for i from 0 to 9\n";
	for (int i = 0; i < 10; ++i) {
		cout << "myList.push_back(" << i * i << ");\n";
		myList.push_back(i*i);
		printListInfo(myList);
	}
	cout << "===================\n";
	cout << "Remove the items with pop_back\n";
	while (myList.size()) {
		printListInfo(myList);
		myList.pop_back();
	}
	cout << "===================\n";

	// Task2
	cout << "\n------Task Two------\n";
	cout << "Fill empty list with push_front: i*i for i from 0 to 9\n";
	for (int i = 0; i < 10; ++i) {
		cout << "myList2.push_front(" << i * i << ");\n";
		myList.push_front(i*i);
		printListInfo(myList);
	}
	cout << "===================\n";
	cout << "Remove the items with pop_front\n";
	while (myList.size()) {
		printListInfo(myList);
		myList.pop_front();
	}
	cout << "===================\n";

	// Task3
	cout << "\n------Task Three------\n";
	cout << "Fill empty list with push_back: i*i for i from 0 to 9\n";
	for (int i = 0; i < 10; ++i) {
		myList.push_back(i*i);
	}
	printListInfo(myList);
	cout << "Now clear\n";
	myList.clear();
	cout << "Size: " << myList.size() << ", list: " << myList << endl;
	cout << "===================\n";
//
	// Task4
	cout << "\n------Task Four------\n";
	cout << "Fill empty list with push_back: i*i for i from 0 to 9\n";
	for (int i = 0; i < 10; ++i)  myList.push_back(i*i);
	cout << "Display elements with op[]\n";
	for (size_t i = 0; i < myList.size(); ++i) cout << myList[i] << ' ';
	cout << endl;
	cout << "Add one to each element with op[]\n";
	for (size_t i = 0; i < myList.size(); ++i) myList[i] += 1;
	cout << "And print it out again with op[]\n";
	for (size_t i = 0; i < myList.size(); ++i) cout << myList[i] << ' ';
	cout << endl;
//
	// Task 5
	cout << "\n------Task Five------\n";
	cout << "Fill empty list with push_back: i*i for i from 0 to 9\n";
	myList.clear();
	for (int i = 0; i < 10; ++i)  myList.push_back(i*i);
	printListInfo(myList);
	cout << "Now display the elements in a ranged for\n";
	for (int x : myList) cout << x << ' ';
	cout << endl;
	cout << "And again using the iterator type directly:\n";
	for (List::iterator iter = myList.begin(); iter != myList.end(); ++iter) {
		cout << *iter << ' ';
	}
	cout << endl;
	cout << "WOW!!! (I thought it was cool.)\n"; 

	// Task 6
	cout << "\n------Task Six------\n";
	cout << "Filling an empty list with insert at end: i*i for i from 0 to 9\n";
	myList.clear();
	for (int i = 0; i < 10; ++i) myList.insert(myList.end(), i*i);
	printListInfo(myList);
	cout << "Filling an empty list with insert at begin(): "
		<< "i*i for i from 0 to 9\n";
	myList.clear();
	for (int i = 0; i < 10; ++i) myList.insert(myList.begin(), i*i);
	printListInfo(myList);
	// ***Need test for insert other than begin/end***
	cout << "===================\n";

	// Task 7
	cout << "\n------Task Seven------\n";
	cout << "Filling an empty list with insert at end: i*i for i from 0 to 9\n";
	myList.clear();
	for (int i = 0; i < 10; ++i) myList.insert(myList.end(), i*i);
	cout << "Erasing the elements in the list, starting from the beginning\n";
	while (myList.size()) {
		printListInfo(myList);
		myList.erase(myList.begin());
	}
	// ***Need test for erase other than begin/end***
	cout << "===================\n";

	// Task 8
	cout << "\n------Task Eight------\n";
	cout << "Copy control\n";
	cout << "Filling an empty list with insert at end: i*i for i from 0 to 9\n";
	myList.clear();
	for (int i = 0; i < 10; ++i) myList.insert(myList.end(), i*i);
	printListInfo(myList);
	cout << "Calling doNothing(myList)\n";
	doNothing(myList);
	cout << "Back from doNothing(myList)\n";
	printListInfo(myList);

	cout << "Filling listTwo with insert at begin: i*i for i from 0 to 9\n";
	List listTwo;
	for (int i = 0; i < 10; ++i) listTwo.insert(listTwo.begin(), i*i);
	printListInfo(listTwo);
	cout << "listTwo = myList\n";
	listTwo = myList;
	cout << "myList: ";
	printListInfo(myList);
	cout << "listTwo: ";
	printListInfo(listTwo);
	cout << "===================\n";
}