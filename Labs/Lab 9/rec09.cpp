// Fahmid Kamal
// fk786
// rec09
// Intro to Inheritance

#include <iostream>
#include <vector>
using namespace std;

#include <iostream>
using namespace std;

class PrintedMaterial {
public:
	PrintedMaterial(unsigned numPages): numOfPages(numPages) {}
	virtual void displayNumPages() const = 0;
protected:
private:
	unsigned numOfPages;
};

void PrintedMaterial::displayNumPages() const { cout << numOfPages << endl; }

class Magazine : public PrintedMaterial {
public:
	Magazine(unsigned numPages): PrintedMaterial(numPages) {}
	void displayNumPages() const {
		PrintedMaterial::displayNumPages();
	}
protected:
private:
};

class Book : public PrintedMaterial {
public:
	Book(unsigned numPages): PrintedMaterial(numPages) {}
	void displayNumPages() const {
		PrintedMaterial::displayNumPages();
	}
protected:
private:
};

class TextBook : public Book {
public:
	TextBook(unsigned numPages, unsigned numIndxPgs): Book(numPages), numOfIndexPages(numIndxPgs) {}
	void displayNumPages() const {
		cout << "Number of index pages: " << numOfIndexPages << endl;
		cout << "Number of total pages: ";
		Book::displayNumPages();
	}
protected:
private:
	unsigned numOfIndexPages;
};

class Novel : public Book {
public:
	Novel(unsigned numPages) : Book(numPages) {}
	void displayNumPages() const {
		PrintedMaterial::displayNumPages();
	}
protected:
private:
};

void displayNumberOfPages(const PrintedMaterial& pm) {
	pm.displayNumPages();
}

// tester/modeler code
int main()
{
	// PrintedMaterial(12);
	TextBook t(5430, 234);
	Novel n(213);
	Magazine m(6);

	t.displayNumPages();
	n.displayNumPages();
	m.displayNumPages();

	vector<PrintedMaterial*> pmVector;
	pmVector.push_back(&t);
	pmVector.push_back(&n);
	pmVector.push_back(&m);
	cout << "Iterating through vector:\n";
	for (size_t i = 0; i < pmVector.size(); ++i) {
		pmVector[i]->displayNumPages();
	}

	cout << "Using function to display number of pages:\n";
	displayNumberOfPages(t);
	displayNumberOfPages(n);
	displayNumberOfPages(m);
}

// Task 4:
// The base class initializes the number of pages
// Task 5:
// Constructors are not inherited