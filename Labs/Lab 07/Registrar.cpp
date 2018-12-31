#include "Registrar.h"
#include "Student.h"
#include "Course.h"
#include <iostream>

using namespace std;
namespace BrooklynPoly {
	ostream& operator<<(ostream&os, const Registrar& reg) {
		os << "Registrar's Report\nCourses:\n";
		for (size_t i = 0; i < reg.courses.size(); ++i) {
			os << *(reg.courses[i]) << endl;
		}
		os << "Students:\n";
		for (size_t i = 0; i < reg.students.size(); ++i) {
			os << *(reg.students[i]) << endl;
		}
		return os;
	}

	Registrar::Registrar() {}
	bool Registrar::addCourse(const string& name) {
		if (findCourse(name) == -1) { // course name is unique, add
			courses.push_back(new Course(name));
			return true;
		}
		cerr << "Error: Course already exists" << endl;
		return false; // course with same name already exists
	}
	bool Registrar::addStudent(const string& name) {
		if (findStudent(name) == -1) { // student with same name does not exist, add
			students.push_back(new Student(name));
			return true;
		}
		cerr << "Error: Student already exists" << endl;
		return false; // student with same name already exists
	}
	bool Registrar::enrollStudentInCourse(const string& studentName, const string& courseName) {
		size_t studentInd = findStudent(studentName);
		if (studentInd == -1) {
			cerr << "Error: Student is not enrolled in the registry" << endl;
			return false;
		}
		size_t courseInd = findCourse(courseName);
		if (courseInd == -1) {
			cerr << "Error: Course does not exist" << endl;
			return false;
		}
		students[studentInd]->addCourse(courses[courseInd]);
		courses[courseInd]->addStudent(students[studentInd]);
		return true;
	}
	bool Registrar::cancelCourse(const string& courseName) {
		size_t courseInd = findCourse(courseName);
		if (courseInd == -1) {
			cerr << "Error: Course does not exist" << endl;
			return false;
		}
		for (size_t i = 0; i < students.size(); ++i) {
			students[i]->removeCourse(courseName);
		}
		courses[courseInd]->purge();
		// Swap with last
		Course* temp = courses[courseInd];
		courses[courseInd] = courses[courses.size() - 1];
		courses[courses.size() - 1] = temp;
		courses.pop_back();
		delete temp;
		return true;
	}
	void Registrar::purge() {
		for (size_t i = 0; i < courses.size(); ++i) {
			courses[i]->purge();
			delete courses[i];
		}
		for (size_t i = 0; i < students.size(); ++i) {
			delete students[i];
		}
		courses.clear();
		students.clear();
	}


	size_t Registrar::findStudent(const string& name) {
		for (size_t i = 0; i < students.size(); ++i) {
			if (students[i]->getName() == name) {
				return i;
			}
		}
		return -1;
	}
	size_t Registrar::findCourse(const string& name) {
		for (size_t i = 0; i < courses.size(); ++i) {
			if (courses[i]->getName() == name) {
				return i;
			}
		}
		return -1;
	}
}