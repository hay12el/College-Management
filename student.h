#ifndef __STUDENT_H
#define __STUDENT_H

#include <iostream>
#include <string>
#include "student.h"
#include "department.h"

using namespace std;

class course;
class Department;

class student
{
private:
	string studentName;
	string id;
	char gender;
	int age;
	course** courses;
	int courseAmount;
	Department* stuDep;

public:
	student();
	student(string, string, char, int, int, Department*, course*);
	student(const student&);
	~student();
	student& operator= (const student&);
	bool operator== (const student&)const;
	course& operator[] (int);
	friend istream& operator>> (istream&, student&);
	friend ostream& operator<< (ostream&, student&);
	int average();
	friend class Department;
	string getId() { return this->id; };
	void printStudent();
};


#endif