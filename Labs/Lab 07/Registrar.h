#ifndef REGISTRAR_H
#define REGISTRAR_H

#include <vector>
#include <string>
#include <iostream>

namespace BrooklynPoly {
	class Course;
	class Student;
	class Registrar {
		friend std::ostream& operator<<(std::ostream&os, const Registrar& reg);
	public:
		Registrar();
		bool addCourse(const std::string& name);
		bool addStudent(const std::string& name);
		bool enrollStudentInCourse(const std::string& studentName, const std::string& courseName);
		bool cancelCourse(const std::string& courseName);
		void purge();
	private:
		size_t findStudent(const std::string& name);
		size_t findCourse(const std::string& name);
		std::vector<Course*> courses;
		std::vector<Student*> students;
	};
}
#endif
