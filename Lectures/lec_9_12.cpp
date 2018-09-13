#include <string>
#include <vector>
#include <string>
#include <fstream>
#include <iostream>
using namespace std;

struct Person {
	string name;
	int age;
};

// Globals 
// int n; // DONT, NOT OK, LOT OF BUGS, FORBIDDEN JUTSU
// const int THE_ANSWER = 42; // OK, because it is constant throughout, Not a problem

int main() {
	vector <Person> people;
	ifstream ifs("person.txt");

	if (!ifs) { //Checking whether or not the stream is good, weather open succeeded
		cerr << "failed to open people" << endl; // Console error
		exit(1);
	}

	// string line;
	// getline(ifs, line);

	string name;
	int age;
	// ifs >> name;
	// ifs >> age;
	//ifs >> name >> age;

	//Person fred; 

	//fred.name = name;
	//fred.age = age;

	//people.push_back(fred); //  Pushes a copy of fred, not reference

	while (ifs >> name >> age) {
		Person somebody;
		somebody.name = name;
		somebody.age = age;
		people.push_back(somebody);
	}

	ifs.close();

	for (size_t i = 0; i < people.size(); ++i) {
		cout << people[i].name << ' ' << people[i].age << endl;
	}

}

