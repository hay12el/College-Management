#ifndef __DEPARTMENT_H
#define __DEPARTMENT_H
#include <iostream>
#include "course.h"
#include "student.h"

using namespace std;

class course;
class student;

class Department
{
private:
	string depName;
	int code;
	int courseAmount;
	course **courses;
	student** studentList;
	int studentAmount;
	student** failStudent;
	int failAmount;

public:
	Department();
	Department(string, int);
	Department(const Department&);
	~Department();
	Department& operator= (const Department&);
	bool operator== (const Department&)const;
	course& operator[] (int);
	friend istream& operator>>(istream&, Department&);
	friend ostream& operator<<(ostream&, Department&);
	student& operator+=(student&);
	int getCode() { return this->code; };
	void addCourse();
	void addStudent(Department*);
	void addStudentToCourse(int, Department*);
	void addGrade(int, string);
	void printCourse(int);
	void printStudent(string);
	void printFailStudent();
	void removeStudent(int, string);
	void printDep();
	string getDepName() { return this->depName; };
	void addStudentToDepartmentFromCourse(string, string, char, int);
};



#endif // !__DEPARTMENT_H
