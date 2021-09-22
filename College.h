#ifndef __COLLEGE_H
#define __COLLEGE_H

#include <iostream>
#include <stdlib.h>
#include <string>
#include "student.h"
#include "course.h"
#include "department.h"

using namespace std;

class student;
class course;
class Department;

class College
{
	string collegeName;
	int collegeId;
	Department** departments;
	int numOfDepartments;
	student** students;
	int numOfStudents;

	void addDepartment();
	void addCourseToDepartment();
	void addStudentToDepartment();
	void registerStudentToCourse();
	void gradingStudentsInCourse();
	void printCourseInfo() const;
	void printStudentInfo() const;
	void printDepartmentInfo() const;
	void findStudentsWithBadAcademicStat();
	int findDepartment(int code) const;
	void addStudentToCollege(student& newStud);
	void removeStudentFromCourse();
public:
	College() : collegeName(""), collegeId(0),departments(NULL), numOfDepartments(0), students(NULL), numOfStudents(0) {}
	College(const College&);
	~College();
	College& operator=(const College& other);
	void menu();
};

#endif