// Fahmid Kamal
// fk786
// rec05.cpp
// This program creates instances of lab sections
// Lab sections hold student records which have grades stored inside
// Each lab section has a Lab Worker that is responsible for that lab section, and adding grades

# include <iostream>
# include <string>
# include <vector>
using namespace std;

class Section {
public:
	Section(const string& name, const string& day, int hour) : name(name), timeSlot(day, hour) {}

	Section(const Section& rhs) : name(rhs.name), timeSlot(rhs.timeSlot) {
		for (Student *currPointer : rhs.studentPointers) {
			studentPointers.push_back(new Student(*currPointer));
		}
	}

	~Section() { // Destructor
		cout << name << " is being deleted." << endl;
		for (Student * currPointer : studentPointers) {
			cout << "Deleting " << currPointer->getName() << endl;
			delete currPointer;
		}
		studentPointers.clear();
	}

	friend ostream& operator << (ostream& os, const Section& section) { // Overloading output operator for Section
		os << "Section: " << section.name << " " << section.timeSlot << ", Students:\n";
		for (Student *currPointer : section.studentPointers) {
			os << *currPointer << "\n";
		}
		return os;
	}

	void addStudent(const string& studentName) {
		studentPointers.push_back(new Student(studentName));
	}

	bool addGrade(const string& name, int grade, int week) {
		for (Student *currPointer : studentPointers) {
			if (currPointer->getName() == name) {
				return (currPointer->addGrade(grade, week));
			}
		}
		return false;
	}

private:
	class Student {
	public:
		Student(const string& name) : name(name) {
			for (int i = 0; i < 14; ++i) {
				vectorOfGrades.push_back(-1);
			}
		}

		Student(const Student& rhs) : name(rhs.name) { // Copy for student
			for (int grade : rhs.vectorOfGrades)
				vectorOfGrades.push_back(grade);
		}

		friend ostream& operator << (ostream& os, const Student& student) { // Overloading output operator for Student
			os << "Name: " << student.name << ", Grades: ";
			for (size_t i = 0; i < student.vectorOfGrades.size(); ++i) {
				os << student.vectorOfGrades[i] << " ";
			}
			return os;
		}

		bool addGrade(int grade, int week) {
			if (week > 14) { return false; }
			vectorOfGrades[week - 1] = grade;
			return true;
		}

		string getName() const { return name; }

	private:
		string name;
		vector <int> vectorOfGrades; 
	};

	class TimeSlot {
	public:
		TimeSlot(const string& day, int hour) : day(day), hour(hour) {}

		TimeSlot(const TimeSlot& rhs) : day(rhs.day), hour(rhs.hour) {}

		friend ostream& operator << (ostream& os, const TimeSlot& timeSlot) { // Overloading output operator for TimeSlot
			os << "Time slot: [Day: " << timeSlot.day << ", " << "Start Time: ";
			if (timeSlot.hour > 12) {
				os << timeSlot.hour - 12 << "pm]";
			}

			else if (timeSlot.hour == 24) {
				os << "12 am]";
			}
			else if (timeSlot.hour == 12) {
				os << "12 pm]";
			}
			else {
				os << timeSlot.hour << "am]";
			}
			return os;
		}

		string getDay() const { return day; }

		int getHour() const { return hour; }

	private:
		string day;
		int hour;
	};
	string name;
	TimeSlot timeSlot;
	vector <Student*> studentPointers;
};

class LabWorker {
public:
	LabWorker(const string& name) : name(name) {}

	friend ostream& operator << (ostream& os, const LabWorker& labWorker) { // Overloading output operator for labworker
		if (labWorker.sectionPointer == nullptr) {
			os << labWorker.name << " does not have a lab section";
			return os;
		}
		os << labWorker.name << " has " << *(labWorker.sectionPointer) << endl;
		return os;
	}

	bool addSection(Section& section) {
		if (sectionPointer != nullptr) { return false; } // LabWorker already has a section
		sectionPointer = &section;
		return true;
	}
	bool addGrade(const string&name, int grade, int week) {
		return (sectionPointer->addGrade(name, grade, week));
	}

private:
	string name;
	Section *sectionPointer = nullptr;
};


void doNothing(Section sec) {
	cout << sec << endl;;
}

int main() {

	cout << "Test 1: Defining a section\n";
	Section secA2("A2", "Tuesday", 16);
	cout << secA2 << endl;

	cout << "\nTest 2: Adding students to a section\n";
	secA2.addStudent("John");
	secA2.addStudent("George");
	secA2.addStudent("Paul");
	secA2.addStudent("Ringo");
	cout << secA2 << endl;

	cout << "\nTest 3: Defining a lab worker.\n";
	LabWorker moe("Moe");
	cout << moe << endl;

	cout << "\nTest 4: Adding a section to a lab worker.\n";
	moe.addSection(secA2);
	cout << moe << endl;

	cout << "\nTest 5: Adding a second section and lab worker.\n";
	LabWorker jane("Jane");
	Section secB3("B3", "Thursday", 11);
	secB3.addStudent("Thorin");
	secB3.addStudent("Dwalin");
	secB3.addStudent("Balin");
	secB3.addStudent("Kili");
	secB3.addStudent("Fili");
	secB3.addStudent("Dori");
	secB3.addStudent("Nori");
	secB3.addStudent("Ori");
	secB3.addStudent("Oin");
	secB3.addStudent("Gloin");
	secB3.addStudent("Bifur");
	secB3.addStudent("Bofur");
	secB3.addStudent("Bombur");
	jane.addSection(secB3);
	cout << jane << endl;

	cout << "\nTest 6: Adding some grades for week one\n";
	moe.addGrade("John", 17, 1);
	moe.addGrade("Paul", 19, 1);
	moe.addGrade("George", 16, 1);
	moe.addGrade("Ringo", 7, 1);
	cout << moe << endl;

	cout << "\nTest 7: Adding some grades for week three (skipping week 2)\n";
	moe.addGrade("John", 15, 3);
	moe.addGrade("Paul", 20, 3);
	moe.addGrade("Ringo", 0, 3);
	moe.addGrade("George", 16, 3);
	cout << moe << endl;

	cout << "\nTest 8: We're done (almost)! \nWhat should happen to all "
		<< "those students (or rather their records?)\n";

	cout << "\nTest 9: Oh, IF you have covered copy constructors in lecture, "
		<< "then make sure the following call works properly, i.e. no memory leaks\n";
	doNothing(secA2);
	cout << "Back from doNothing\n\n";
} // main