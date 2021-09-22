#include "department.h"

Department::Department() : depName(""), code(0), courses(nullptr), studentList(nullptr), studentAmount(0), failStudent(nullptr), failAmount(0), courseAmount(0){}

Department::Department(string depName, int code) : depName(depName), code(code), courses(nullptr), studentList(nullptr), studentAmount(0), failStudent(nullptr), failAmount(0), courseAmount(0){}

Department::Department(const Department& right) : depName(right.depName), code(right.code), courseAmount(right.courseAmount), failAmount(right.failAmount), studentAmount(right.studentAmount)
{
	int i = 0;
	if (courseAmount > 0)
	{
		this->courses = new course * [courseAmount];
		for (i = 0; i < courseAmount; i++)
			this->courses[i] = courses[i];
	}
	else
	{
		this->courses = nullptr;
	}

	if (studentAmount > 0)
	{
		this->studentList = new student * [studentAmount];
		for (i = 0; i < studentAmount; i++)
			this->studentList[i] = studentList[i];
	}
	else
	{
		studentList = nullptr;
	}

	if (failAmount > 0)
	{
		this->failStudent = new student * [failAmount];
		for (i = 0; i < failAmount; i++)
			this->failStudent[i] = failStudent[i];
	}
	else
	{
		failStudent = nullptr;
	}
}

Department::~Department()
{
	int i = 0;
	for (i = 0; i < courseAmount; i++)
		delete [] courses[i];
	delete[] courses;
	for (i = 0; i < studentAmount; i++)
		delete[] studentList[i];
	delete[] studentList;
	for (i = 0; i < failAmount; i++)
		delete[] failStudent[i];
	delete[] failStudent;
}

Department& Department::operator=(const Department& right)
{
	int i = 0;
	if (this != &right)
	{
		depName = right.depName;
		code = right.code;

		if (courses != nullptr)
		{
			for (i = 0; i < courseAmount; i++)
				delete[] courses[i];
			delete[] courses;
		}
		courseAmount = right.courseAmount;
		courses = new course * [courseAmount];
		for (i = 0; i < studentAmount; i++)
			courses[i] = right.courses[i];

		if (studentList != nullptr)
		{
			for (i = 0; i < studentAmount; i++)
				delete studentList[i];
			delete[] studentList;
		}
		studentAmount = right.studentAmount;
		studentList = new student * [studentAmount];
		for (i = 0; i < studentAmount; i++)
			studentList[i] = right.studentList[i];

		if (failStudent != nullptr)
		{
			for (i = 0; i < failAmount; i++)
				delete[] failStudent[i];
			delete[] failStudent;
		}
		failAmount = right.failAmount;
		failStudent = new student * [failAmount];
		for (i = 0; i < failAmount; i++)
			failStudent[i] = right.failStudent[i];
	}

	return *this;
}

bool Department::operator==(const Department& right) const
{
	if (code == right.code)
		return true;
	return false;
}

course& Department::operator[](int index)
{
	if (index > courseAmount || index < 0)
	{
		cout << "invalid value..." << endl;
		exit(1);
	}
	return *courses[index];
}


istream& operator>>(istream& in, Department& dep)
{
	cout << "Enter department's name: " << endl;
	cin.ignore();
	getline(in, dep.depName);
	cout << "Enter department's id: " << endl;
	in >> dep.code;

	return in;
}

ostream& operator<<(ostream& out, Department& dep)
{
	int i = 0;
	cout << "Department: " << dep.depName << endl;
	cout << "Department code: " << dep.code << endl;
	if (dep.courseAmount == 0)
	{
		cout << "There are 0 courses in the department." << endl;
	}
	else
	{
		cout << "Department's courses:" << endl;
		for (i = 0; i < dep.courseAmount; i++)
			cout << dep.courses[i] << endl;
	}
	
	if (dep.studentAmount == 0)
	{
		cout << "There are 0 students in the department." << endl;
	}
	else
	{
		cout << "Department's students: " << endl;
		for (i = 0; i < dep.studentAmount; i++)
			cout << dep.studentList[i] << endl;
	}

	if (dep.failAmount == 0)
	{
		cout << "There are 0 failing students in the department." << endl;
	}
	else
	{
		cout << "Failing students: " << endl;
		for (i = 0; i < dep.failAmount; i++)
			cout << dep.failStudent[i] << endl;
	}

	return out;
}

student& Department::operator+= (student& newF)
{
	if (newF.average() < 60)
	{
		int i;
		failAmount++;
		student** temp = new student * [failAmount];
		for (i = 0; i < (failAmount - 1); i++) // copy previus fail student list
		{
			temp[i] = failStudent[i];
		}
		// add new fail student to list
		temp[i + 1] = &newF;
		//delete old list
		delete[]failStudent;
		//copy adrres of temp
		failStudent = temp;
	}
	return newF;
}

void Department::addCourse()
{
	cout << "Enter course's name: ";
	string courseName;
	cin.ignore();
	getline(cin, courseName);
	cout << "Enter course's id: ";
	int courseId;
	cin >> courseId;

	int i;
	course** temp = new course * [courseAmount+1];
	for (i = 0; i < this->courseAmount; i++)
		temp[i] = this->courses[i];
	temp[i] = new course(courseName, courseId);

	courses = temp;
	courseAmount++;
}

void Department::addStudent(Department* add)
{
	cout << "Enter student's name: ";
	string studentName;
	cin.ignore();
	getline(cin, studentName);
	cout << "Enter student's id: ";
	string studentId;
	cin.ignore();
	getline(cin, studentId);
	cout << "Enter gender: ";
	char gender;
	cin >> gender;
	cout << "Enter age: ";
	int age;
	cin >> age;

	int i;
	student** temp = new student * [studentAmount + 1];
	for (i = 0; i < studentAmount; i++)
		temp[i] = studentList[i];
	temp[i] = new student(studentName, studentId, gender, age, 0, add, NULL);

	studentList = temp;
	studentAmount++;
}

void Department::addStudentToDepartmentFromCourse(string stuName, string ID, char gender, int age)
{
	if (studentList == NULL)
	{
		studentList = new student * [1];
		studentList[0] = new student(stuName, ID, gender, age, 0, this, NULL);
		studentAmount = 1;
	}
	else
	{
		int i;
		student** temp = new student * [studentAmount + 1];
		for (i = 0; i < studentAmount; i++)
			temp[i] = studentList[i];
		temp[i] = new student(stuName, ID, gender, age, 0, this, NULL);

		studentList = temp;
		this->studentAmount++;
	}
}

void Department::addStudentToCourse(int index, Department* add)
{
	for (int i = 0; i < courseAmount; i++)
	{

		if (courses[i]->getId() == index)
		{
			courses[i]->addStudent(add);
		}
	}
}

void Department::addGrade(int courseNum, string Id)
{
	for (int i = 0; i < courseAmount; i++)
	{
		if (courses[i]->getId() == courseNum)
			courses[i]->addGradeInCourse(Id);
	}
	return;
}

void Department::printCourse(int courseN)
{
	for (int i = 0; i < this->courseAmount; i++)
	{
		if (courseN == courses[i]->getId())
			courses[i]->printCourse();
	}
}

void Department::printStudent(string ID)
{
	for (int i = 0; i < this->studentAmount; i++)
	{
		if (studentList[i]->getId() == ID)
			studentList[i]->printStudent();
	}
}

void Department::printFailStudent()
{
	for (int i = 0; i < failAmount; i++)
		failStudent[i]->printStudent();
}

void Department::removeStudent(int courseN, string ID)
{
	for (int i = 0; i < this->courseAmount; i++)
	{
		if (courseN == courses[i]->getId())
			courses[i]->removeStudent(ID);
	}
}

void Department:: printDep()
{
	int i = 0;
	cout << "Department: " << depName << endl;
	cout << "Department code: " << code << endl;
	if (courseAmount == 0)
	{
		cout << "There are 0 courses in the department." << endl;
	}
	else
	{
		cout << "Department's courses:" << endl;
		for (i = 0; i < courseAmount; i++)
			courses[i]->printCourse();
	}

	if (studentAmount == 0)
	{
		cout << "There are 0 students in the department." << endl;
	}
	else
	{
		cout << "Department's students: " << endl;
		for (i = 0; i < studentAmount; i++)
			studentList[i]->printStudent();
	}

	if (failAmount == 0)
	{
		cout << "There are 0 failing students in the department." << endl;
	}
	else
	{
		cout << "Failing students: " << endl;
		for (i = 0; i < failAmount; i++)
			failStudent[i]->printStudent();
	}
}


