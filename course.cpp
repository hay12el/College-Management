#include "course.h"
#include "department.h"
#include "student.h"

course::course() : courseName(" "), courseNum(0), studentList(nullptr), studentNum(0), gradesArray(nullptr), courseDep(nullptr){}

course::course(string courseName, int courseNum) : courseName(courseName), courseNum(courseNum), studentList(nullptr), studentNum(0), gradesArray(nullptr), courseDep(nullptr){}

course::course(const course& obj)
{
	courseName = obj.courseName;
	courseNum = obj.courseNum;
	studentNum = obj.studentNum;
	if (studentNum > 0)
	{
		studentList = new student*[studentNum];
		gradesArray = new int[studentNum];
		for (int i = 0; i < studentNum; i++)
			gradesArray[i] = obj.gradesArray[i];
		courseDep = obj.courseDep;
	}
	else
	{
		studentList = NULL;
		gradesArray = nullptr;
	}
}

course::~course()
{
	if (studentList != NULL)
		delete[] studentList;

	if (gradesArray != NULL)
		delete[] gradesArray;
}

course& course::operator=(const course& right)
{
	if (this != &right)
	{
		courseName = right.courseName;
		courseNum = right.courseNum;
		studentNum = right.studentNum;
		if (studentList != nullptr)
		{
			delete[] studentList;
			delete[] gradesArray;
		}
		if (studentNum > 0)
		{
			studentList = new student * [studentNum];
			gradesArray = new int[studentNum];
			for (int i = 0; i < studentNum; i++)
			{
				gradesArray[i] = right.gradesArray[i];
				studentList[i] = right.studentList[i];
			}
		}
		else
		{
			gradesArray = nullptr;
			studentList = nullptr;
		}

		courseDep = right.courseDep;
	}
	return *this;
}

bool course::operator==(const course& right) const
{
	if (courseNum == right.courseNum)
		return true;
	return false;
}

student& course::operator[](int index)
{
	if (index > studentNum || index < 0)
	{
		cout << "error.." << endl;
		exit(1);
	}
	return *studentList[index];
}


istream& operator>>(istream& in, course& course)
{
	cout << "Enter course's name: " << endl;
	cin.ignore();
	getline(in, course.courseName);
	cout << "Enter course's id: " << endl;
	in >> course.courseNum;
	return in;
}

ostream& operator<<(ostream& out, course& course)
{
	cout << "Course name: " << course.courseName << endl;
	cout << "Course ID: " << course.courseNum << endl;
	if (course.courseDep == nullptr)
	{
		cout << "The course is a general course and not belong to any department yet." << endl;
	}
	else {
		cout << "This course belong to " << course.courseDep << endl;
	}

	cout << "Number of students in course: " << course.studentNum << endl;
	if (course.studentNum == 0)
	{
		cout << "No students in this course" << endl;
	}
	else {
		for (int i = 0; i < course.studentNum; i++)
		{
			cout << course.studentList[i];
			cout << "Student's grade in that course: "<< course.gradesArray[i] << endl;
		}
	}
	return out;
}

int course::gradeOfStudent(const student& x)
{
	for (int i = 0; i < studentNum; i++)
	{
		if (&x == studentList[i])
			return gradesArray[i];
	}
	return 0;
}

void course::printCourse()
{
	cout << "Course name: " << courseName << endl;
	cout << "Course ID: " << courseNum << endl;
	if (courseDep == nullptr)
	{
		cout << "The course is a general course and not belong to any department yet." << endl;
	}
	else {
		cout << "This course belong to " << courseDep << endl;
	}

	cout << "Number of students in course: " << studentNum << endl;
	if (studentNum == 0)
	{
		cout << "No students in this course" << endl;
	}
	else {
		for (int i = 0; i < studentNum; i++)
		{
			studentList[i]->printStudent();
			if (gradesArray[i] > -1)
				cout << "Student's grade in that course: " << gradesArray[i] << endl;
		}
	}
	
}

void course::addStudent(Department* add)
{
	cout << "Enter student's name: ";
	string studentName;
	cin.ignore();
	getline(cin, studentName);
	cout << "Enter student's id: ";
	string studentId;
	getline(cin, studentId);
	cout << "Enter gender: ";
	char gender;
	cin >> gender;
	cout << "Enter age: ";
	int age;
	cin >> age;
	add->addStudentToDepartmentFromCourse(studentName, studentId, gender, age);
	int i;
	student** temp = new student * [studentNum + 1];
	int* tempL = new int[studentNum + 1];
	for (i = 0; i < studentNum; i++)
	{
		temp[i] = studentList[i];
		tempL[i] = gradesArray[i];
	}
	temp[i] = new student(studentName, studentId, gender, age, 0, add, this);

	gradesArray = tempL;
	studentList = temp;
	studentNum++;
}

void course::addGradeInCourse(string id)
{
	for (int i = 0; i < studentNum; i++)
	{
		if (id == this->studentList[i]->getId())
		{
			cout << "Enter grade of student: ";
			cin >> gradesArray[i];
		}
	}
}

void course::removeStudent(string ID)
{
	int i, j, remove = 0;
	for (int i = 0; i < this->studentNum; i++)
	{
		if (ID == this->studentList[i]->getId())
		{
			remove = i;
		}
	}
	i = 0;
	student** temp = new student * [studentNum - 1];
	for (j = 0; j < studentNum; j++)
	{
		if (j != remove)
		{
			temp[i] = studentList[j];
			i++;
		}
	}

	studentList = temp;
	studentNum--;
}
