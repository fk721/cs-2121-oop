#ifndef STUDENT_H
#define STUDENT_H
#include <string>
#include <vector>
#include <iostream>

namespace BrooklynPoly {
	class Course;

	class Student {
		friend std::ostream& operator<<(std::ostream& os, const Student& stu);
	public:
		Student(const std::string& name);
		std::string getName() const;
		void addCourse(Course* coursePtr);
		bool removeCourse(const std::string& courseName);
	private:
		std::string name;
		std::vector<Course*> courses;
	};
}
#endif
