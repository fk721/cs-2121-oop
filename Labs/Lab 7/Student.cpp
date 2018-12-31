#include "Student.h"
#include "Course.h"
#include <iostream>
#include <string>
using namespace std;

namespace BrooklynPoly {
	ostream& operator<<(ostream& os, const Student& stu) {
		os << stu.name << ": ";
		if (stu.courses.size() == 0) {
			os << "No courses";
			return os;
		}
		for (size_t i = 0; i < stu.courses.size(); ++i) {
			os << stu.courses[i]->getName() << " ";
		}
		return os;
	}
	Student::Student(const string& name) : name(name) {}
	string Student::getName() const { return this->name; }
	void Student::addCourse(Course* coursePtr) { courses.push_back(coursePtr); }
	bool Student::removeCourse(const string& courseName) {
		for (size_t i = 0; i < courses.size(); ++i) {
			if (courses[i]->getName() == courseName) {
				// swap with the last
				Course* temp = courses[i];
				courses[i] = courses[courses.size() - 1];
				courses[courses.size() - 1] = temp;
				temp = nullptr;
				courses.pop_back();
				return true;
			}
		}
		return false;
	}
}