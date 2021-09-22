#include "College.h"

void College::addDepartment()
{
	cout << "Enter department's name:" << endl;
	string name;
	cin.ignore();
	getline(cin, name);
	cout << "Enter department's code:" << endl;
	int code;
	cin >> code;
	if (findDepartment(code) != -1) {
		cout << "A department with this code already exists." << endl;
		return;
	}

	Department* newDepartment = new Department(name, code);
	if (numOfDepartments > 0) {
		Department** temp = new Department * [++numOfDepartments];
		for (int i = 0; i < numOfDepartments - 1; i++) {
			temp[i] = departments[i];
		}
		delete[] departments;
		departments = temp;
	}
	else {                                                                                                  
		departments = new Department * [++numOfDepartments];
	}
	departments[numOfDepartments - 1] = newDepartment;
}

void College::addCourseToDepartment()
{
	int codeDep, i;
	cout << "Enter department's code: ";
	cin >> codeDep;
	for (i = 0; i < numOfDepartments; i++)
	{
		if (departments[i]->getCode() == codeDep)
			departments[i]->addCourse();
	}
}

void College::addStudentToDepartment()
{
	int codeDep, i;
	cout << "Enter department's code: ";
	cin >> codeDep;
	for (i = 0; i < numOfDepartments; i++)
	{
		if (departments[i]->getCode() == codeDep)
			departments[i]->addStudent(departments[i]);

	}
}

void College::registerStudentToCourse()
{
	int codeDep, courseNum, i;
	cout << "Enter department's code: ";
	cin >> codeDep;
	cout << "Enter course's number: ";
	cin >> courseNum;

	for (i = 0; i < numOfDepartments; i++)
	{
		if (departments[i]->getCode() == codeDep)
		{
			departments[i]->addStudentToCourse(courseNum, departments[i]);
		}
	}
}

void College::gradingStudentsInCourse()
{
	int codeDep, courseNum, i;
	string studentId;
	cout << "Enter department's code: ";
	cin >> codeDep;
	cout << "Enter course's number: ";
	cin >> courseNum;
	cin.ignore();
	cout << "Enter student's id: ";
	getline(cin, studentId);
	for (i = 0; i < numOfDepartments; i++)
	{
		if (departments[i]->getCode() == codeDep)
		{
			departments[i]->addGrade(courseNum, studentId);
		}
	}
}

void College::printCourseInfo() const
{
	int codeDep, courseNum, i;
	cout << "Enter department's code: ";
	cin >> codeDep;
	cout << "Enter course's number: ";
	cin >> courseNum;

	for (i = 0; i < numOfDepartments; i++)
	{
		if (departments[i]->getCode() == codeDep)
		{
			departments[i]->printCourse(courseNum);
		}
	}
}

void College::printStudentInfo() const
{
	cout << "Enter student's department: ";
	int codeDep;
	cin >> codeDep;
	cout << "Enter student's ID: ";
	cin.ignore();
	string ID;
	getline(cin, ID);

	for (int i = 0; i < numOfDepartments; i++)
	{
		if (departments[i]->getCode() == codeDep)
		{
			departments[i]->printStudent(ID);
		}
	}
}

void College::printDepartmentInfo() const
{
	int codeDep, i;
	cout << "Enter department's code: ";
	cin >> codeDep;

	for (i = 0; i < numOfDepartments; i++)
	{
		if (departments[i]->getCode() == codeDep)
		{
			departments[i]->printDep();
		}
	}
}

void College::findStudentsWithBadAcademicStat()
{
	int codeDep, i;
	cout << "Enter department's code: ";
	cin >> codeDep;

	for (i = 0; i < numOfDepartments; i++)
	{
		if (departments[i]->getCode() == codeDep)
		{
			departments[i]->printFailStudent();
		}
	}
}

int College::findDepartment(int code) const
{
	int i;
	for (i = 0; i < numOfDepartments; i++)
	{
		if (departments[i]->getCode() == code)
		{
			return i;
		}
	}
	return -1;
}


void College::addStudentToCollege(student& newStud) {
	if (numOfStudents > 0) {
		for (int i = 0; i < numOfStudents; i++) {
			if (newStud == *students[i]) {
				cout << "This student is already signed to this college." << endl;
				return;
			}
		}
		student** temp = new student * [++numOfStudents];
		for (int i = 0; i < numOfStudents - 1; i++) {
			temp[i] = students[i];
		}
		delete[] students;
		students = temp;
	}
	else {
		students = new student * [++numOfStudents];
	}
	students[numOfStudents - 1] = new student(newStud);
}

void College::removeStudentFromCourse()
{
	int codeDep, courseNum, i;
	string studentId;
	cout << "Enter department's code: ";
	cin >> codeDep;
	cout << "Enter course's number: ";
	cin >> courseNum;
	cin.ignore();
	cout << "Enter student's id: ";
	getline(cin, studentId);
	for (i = 0; i < numOfDepartments; i++)
	{
		if (departments[i]->getCode() == codeDep)
		{
			departments[i]->removeStudent(courseNum, studentId);
		}
	}
}

College::College(const College& other) : collegeName(other.collegeName), collegeId(other.collegeId), numOfDepartments(other.numOfDepartments), numOfStudents(other.numOfStudents)
{
	if (numOfDepartments > 0)
	{
		departments = new Department * [numOfDepartments];
		for (int i = 0; i < numOfDepartments; i++)
			departments[i] = other.departments[i];
	}
	else
	{
		departments = nullptr;
	}

	if (numOfStudents > 0)
	{
		students = new student * [numOfStudents];
		for (int i = 0; i < numOfStudents; i++)
			students[i] = other.students[i];
	}
	else
	{
		students = nullptr;
	}
}

College::~College()
{
	if (departments != nullptr)
		delete[] departments;
	if (students != nullptr)
		delete[] students;
}

College& College::operator=(const College& other)
{
	if (this != &other)
	{
		this->collegeId = other.collegeId;
		this->collegeName = other.collegeName;
		this->numOfDepartments = other.numOfDepartments;
		this->numOfStudents = other.numOfStudents;
		if (departments != nullptr)
			delete[] departments;
		if (numOfDepartments > 0)
		{
			departments = new Department*[numOfDepartments];
			for (int i = 0; i < numOfDepartments; i++)
				this->departments[i] = other.departments[i];
		}
		else
		{
			departments = nullptr;
		}		
		
		if (numOfStudents > 0)
		{
			students = new student*[numOfStudents];
			for (int i = 0; i < numOfStudents; i++)
				this->students[i] = other.students[i];
		}
		else
		{
			students = nullptr;
		}
	}
	return *this;
}

void College::menu()
{
	while (1)
	{
		fflush(stdin);
		cout << "*************************************************************************" << endl;
		cout << "Welcome to sce. What would you like to do?" << endl;
		cout << "*************************************************************************" << endl;
		cout << "[1] - Add a department to the college." << endl;
		cout << "[2] - Add a course to a department." << endl;
		cout << "[3] - Add a student to a department." << endl;
		cout << "[4] - Register a student to a course." << endl;
		cout << "[5] - Grade a course." << endl;
		cout << "[6] - Print a course's information." << endl;
		cout << "[7] - Print a student's information." << endl;
		cout << "[8] - Print a department's information." << endl; 
		cout << "[9] - Calculate the students with bad academic status." << endl;
		cout << "[10]- Remove a student from a course." << endl;
		cout << "[11]- Exit." << endl;
		cout << "*************************************************************************" << endl;

		int choice;
		cin >> choice;

		switch (choice)
		{
		case 1:
			addDepartment();
			break;
		case 2:
			addCourseToDepartment();
			break;
		case 3:
			addStudentToDepartment();
			break;
		case 4:
			registerStudentToCourse();
			break;
		case 5:
			gradingStudentsInCourse();
			break;
		case 6:
			printCourseInfo();
			break;
		case 7:
			printStudentInfo();
			break;
		case 8:
			printDepartmentInfo();
			break;
		case 9:
			findStudentsWithBadAcademicStat();
			break;
		case 10:
			removeStudentFromCourse();
			break;
		case 11:
			cout << "Thank you, goodbye." << endl;
			return;
			break;
		default:
			cout << "No such option , sorry. Choose again please." << endl;
		}
	}
}