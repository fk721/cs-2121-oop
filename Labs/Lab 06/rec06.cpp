// Fahmid Kamal
// rec06.cpp
// A program that models a directory of workers with specific positions

#include <iostream>
#include <string>
using namespace std;

class Position {
	friend ostream& operator<<(ostream& os, const Position& rhs) {
		os << '[' << rhs.title << ',' << rhs.salary << ']';
		return os;
	}
public:
	Position(const string& aTitle, double aSalary)
		: title(aTitle), salary(aSalary) {}
	const string& getTitle() const { return title; }
	double getSalary() const { return salary; }
	void changeSalaryTo(double d) { salary = d; }
private:
	string title;
	double salary;
}; // class Position

class Entry {
	friend ostream& operator<<(ostream& os, const Entry& rhs) {
		os << rhs.name << ' ' << rhs.room
			<< ' ' << rhs.phone << ", " << *rhs.pos;
		return os;
	}
public:
	Entry(const string& name, unsigned room, unsigned phone, Position& position)
		: name(name), room(room), phone(phone), pos(&position) {
	}
	//Entry (const Entry& rhs): name(rhs.name), room(rhs.room), phone(rhs.phone), pos(rhs.pos) {}
	const string& getName() const { return name; }
	const unsigned& getPhone() const { return phone; }
private:
	string name;
	unsigned room;
	unsigned phone;
	Position* pos;
}; // class Entry

class Directory {
	// Overload output operator
	friend ostream& operator <<(ostream& os, const Directory& rhs) {
		for (size_t i = 0; i < rhs.size; ++i) {
			os << *(rhs.entries[i]) << endl;
		}
		return os;
	}

public:
	Directory() : size(0), capacity(1), entries(new Entry*[1]) {}

	Directory(const Directory& rhs) {
		size = rhs.size;
		capacity = rhs.capacity;
		entries = new Entry*[rhs.capacity];
		for (size_t i = 0; i < rhs.size; ++i) {
			entries[i] = new Entry(*rhs.entries[i]); // DEEP COPY
		}
	}

	~Directory() {
		// Must delete each entry on the heap
		for (size_t i = 0; i < size; ++i) {
			delete entries[i]; // deletes individual entry on the heap
		}
		delete[] entries; // delete the dynamic array itself
	}

	Directory& operator=(const Directory& rhs) { // return by reference, chaining
		// check for self-assignment
		if (this != &rhs) {
			for (size_t i = 0; i < size; ++i) {
				delete entries[i]; // deletes individual entry on the heap
			}
			delete[] entries; // free up
			size = rhs.size;
			capacity = rhs.capacity;
			entries = new Entry*[rhs.capacity]; // allocate
			for (size_t i = 0; i < size; ++i) {
				entries[i] = new Entry(*rhs.entries[i]); // assign
			}
		}
		// return yourself
		return *this;
	}

	unsigned operator[] (const string& name) const { // GETTER
		for (size_t i = 0; i < size; ++i) {
			if (entries[i]->getName() == name) {
				return entries[i]->getPhone();
			}
		}
		// Did not find the name
		cerr << "Employee with name " << name << " does not exist in this directory" << endl;
		return (0000); // default value
	}

	void add(const string& name, unsigned room, unsigned ph, Position& pos) {
		if (size == capacity) {
			// PUSH BACK FOR A VECTOR
			// something is missing!!!  Add it!
			// Resize
			Entry** oldEntry = entries;
			entries = new Entry*[capacity * 2];
			for (size_t i = 0; i < size; ++i) {
				entries[i] = oldEntry[i];
			}
			capacity *= 2;
			delete[] oldEntry;
		} // if
		entries[size] = new Entry(name, room, ph, pos);
		++size;
	} // add

private:
	Entry** entries;
	size_t size;
	size_t capacity;
}; // class Directory

void doNothing(Directory dir) { cout << dir << endl; }

int main() {

	// Note that the Postion objects are NOT on the heap.
	Position boss("Boss", 3141.59);
	Position pointyHair("Pointy Hair", 271.83);
	Position techie("Techie", 14142.13);
	Position peon("Peonissimo", 34.79);

	// Create a Directory
	Directory d;
	d.add("Marilyn", 123, 4567, boss);
	cout << d << endl;

	Directory d2 = d;	// What function is being used??
	d2.add("Gallagher", 111, 2222, techie);
	d2.add("Carmack", 314, 1592, techie);
	cout << d << endl;

	cout << "Calling doNothing\n";
	doNothing(d2);
	cout << "Back from doNothing\n";

	Directory d3;
	d3 = d2;

	// Should display 1592
	cout << d2["Carmack"] << endl;
} // main