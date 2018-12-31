/* Fahmid Kamal
	Lab 14| Recursion
*/
#include <iostream>
#include <vector>
#include <stdexcept>
using namespace std;

// Task 1

bool hasEvenOnes(int x) {
	if (x == 0 ) { return true; }
	else if (x % 2 == 0) {
		return hasEvenOnes(x / 2);
	}
	return !hasEvenOnes(x / 2);
}

// Task 2
struct Node {
	Node(int data = 0, Node* next = nullptr) : data(data), next(next) {}
	int data;
	Node* next;
};

void listInsertHead(Node*& headPtr, int entry) {
	headPtr = new Node(entry, headPtr);
}

Node* listBuild(const vector<int>& vals) {
	Node* result = nullptr;
	for (size_t index = vals.size(); index > 0; --index) {
		listInsertHead(result, vals[index - 1]);
	}
	return result;
}
void listDisplay(const Node* headPtr) {
	const Node* p = headPtr;
	while (p != nullptr) {
		cout << p->data << ' ';
		p = p->next;
	}
	cout << endl;
}

/*int sumList(Node* listOne, Node* listTwo) {
	if (listOne == nullptr && listTwo == nullptr) { return 0; }
	int lval = 0;
	int rval = 0;
	if (listOne) {lval = listOne->data; }
	if (listTwo) { rval = listTwo->data; }
	return lval+ rval +
		sumList(listOne == nullptr ? nullptr : listOne->next, listTwo == nullptr ? nullptr : listTwo->next);
} */

Node* sumList(Node* listOne, Node* listTwo) {
	if (listOne == nullptr && listTwo == nullptr) {
		return nullptr;
	}
	int lval;
	int rval;
	listOne == nullptr ? lval = 0 : lval = listOne->data;
	listTwo == nullptr ? rval = 0 : rval = listTwo->data;
	return new Node(lval + rval,
		sumList(listOne == nullptr ? nullptr : listOne->next, listTwo == nullptr ? nullptr : listTwo->next));
}

// Task 3
struct TNode {
	TNode(int data = 0, TNode *left = nullptr, TNode *right = nullptr)
		: data(data), left(left), right(right) {}
	int data;
	TNode *left, *right;
};

int max(TNode* root) {
	if (!root) { throw invalid_argument("Root is a nullptr\n"); }
	if (root->left == nullptr && root->right == nullptr) { return root->data; }
	else if (root->left == nullptr) {
		int maxVal;
		int curr = root->data;
		int right = max(root->right);
		curr >= right ? maxVal = curr : maxVal = right;
		return maxVal;
	}
	else if (root->right == nullptr) {
		int maxVal;
		int curr = root->data;
		int left = max(root->left);
		curr >= left ? maxVal = curr : maxVal = left;
		return maxVal;
	}
	else {
		int maxVal;
		int curr = root->data;
		int left = max(root->left);
		int right = max(root->right);
		left >= right ? maxVal = left : maxVal = right;
		curr >= maxVal ? maxVal = curr : maxVal = maxVal;
		return maxVal;
	}
}

// Task 4
bool palindrome(char word[], int len) {
	if (word >= &word[len - 1]) { return true; }
	//cout << *word << word[len - 1] << endl;
	if (*word != word[len - 1]) { return false; }
	return palindrome(word + 1, len - 2 );
}

// Task 5
// RECURSION
int towers(int n, char start, char spare, char target) {
	if (n == 0) {
		return 0;
	}
	return 1 + towers(n - 1, spare, target, start) + towers(n - 1, start, spare, target);
}
// Task 6
void mystery(int n) {
	if (n > 1) {
		cout << 'a';
		mystery(n / 2);
		cout << 'b';
		mystery(n / 2);
	}
	cout << 'c';
}

// Test code

int main() {
	// Task 1, modify val to see output for different vals
	int val(91);
	bool res = hasEvenOnes(val);
	if (res) { cout << val << " in binary has an even number of ones\n"; }
	else { cout << val << " in binary does not have an even number of ones\n"; }
	// Task 2, modify v2 and v2 to change the two lists
	vector<int> v1{ 5,7,9,3}; Node* listOne = listBuild(v1);
	vector<int> v2{ 6,3,2}; Node* listTwo = listBuild(v2);
	Node* sum = sumList(listOne, listTwo);
	cout << "listOne is\n"; listDisplay(listOne);
	cout << "listTwo is\n"; listDisplay(listTwo);
	cout << "The sum of listOne and listTwo is\n"; listDisplay(sum);
	// Task 3
	TNode a(1), b(2), c(4), d(8, &a, &b), e(16, &c), f(32, &d, &e);
	try {
		cout << "The max val of Tnode is " << max(&f) << endl;
	}
	catch (invalid_argument e) {
		cerr << e.what() << endl;
	}
	// Task 4, modify s and size to test
	char s[] = "racecar";
	int size = 7;
	cout << "Checking if " << s << " is a palindrome\n";
	if (palindrome(s, size)) { cout << "Yes!\n"; }
	else { cout << "No!\n"; }
	// Task 5
	int towerCount = towers(10, 'A', 'B', 'C');
	cout << "towers(10, 'A', 'B', 'C'): "<< towerCount << endl;
	// Task 6
	// mystery(2);
}