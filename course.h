#ifndef __COURSE_H
#define __COURSE_H

#include <iostream>
#include "student.h"
#include "department.h"

using namespace std;

class student;
class Department;

class course
{
private:
	string courseName;
	int courseNum;
	student** studentList;
	int studentNum;
	int* gradesArray;
	Department* courseDep;
public:
	course();
	course(string, int);
	course(const course& obj);
	~course();
	course& operator= (const course& right);
	bool operator== (const course&) const;
	student& operator[] (int index);
	friend istream& operator>> (istream&, course&);
	friend ostream& operator<< (ostream&, course&);
	int gradeOfStudent(const student&);
	int getId() { return this->courseNum; };
	void addStudent(Department*);
	void addGradeInCourse(string);
	void removeStudent(string);
	void printCourse();
	string getCourseName() { return this->courseName; };
};

#endif