#include "Course.h"
#include "Student.h"
#include <iostream>
#include <string>
using namespace std;

namespace BrooklynPoly {
	ostream& operator<<(ostream& os, const Course& crs) {
		os << crs.name << ": ";
		if (crs.students.size() == 0) {
			os << "No students";
			return os;
		}
		for (size_t i = 0; i < crs.students.size(); ++i) {
			os << crs.students[i]->getName() << " ";
		}
		return os;
	}
	Course::Course(const string& courseName) : name(courseName) {}
	string Course::getName() const { return this->name; }
	void Course::addStudent(Student* studentPtr) { students.push_back(studentPtr); }
	void Course::purge() {
		students.clear();
	}
}