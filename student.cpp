#include "student.h"
#include "course.h"
#include "department.h"

student::student(): id(""), studentName(""), gender(' '), age(0), courses(nullptr), stuDep(nullptr), courseAmount(0){}

student::student(string studentName, string id, char gender, int age, int courseAmount, Department* add, course* cou) : studentName(studentName), id(id), gender(gender), age(age), stuDep(add)
{
	if (cou != NULL)
	{
		if (courses == NULL)
		{
			courses = new course * [1];
			courses[0] = cou;
			this->courseAmount = 1;
		}
		else
		{
			int i;
			course** temp = new course * [courseAmount + 1];
			for (i = 0; i < courseAmount; i++)
			{
				temp[i] = courses[i];
			}
			temp[i] = cou;
			courses = temp;
			courseAmount++;
		}
	}
	else
	{
		courses = NULL;
		courseAmount = 0;
	}
}

student::student(const student& obj) : studentName(obj.studentName), id(obj.id), gender(obj.gender), age(obj.age), courseAmount(obj.courseAmount)
{
	if (courseAmount > 0)
	{
		courses = new course * [courseAmount];
		for (int i = 0; i < courseAmount; i++)
			courses[i] = obj.courses[i];
	}
	else
	{
		courses = NULL;
	}
	stuDep = obj.stuDep;
}

student::~student()
{
	if (courses != NULL)
		delete[] courses;
}

student& student::operator=(const student& right)
{
	if (this != &right)
	{
		studentName = right.studentName;
		id = right.id;
		gender = right.gender;
		age = right.age;

		if (courses != NULL)
		{
			delete[] courses;
		}

		courseAmount = right.courseAmount;

		courses = new course * [courseAmount];
		for (int i = 0; i < courseAmount; i++)
			courses[i] = right.courses[i];
		stuDep = right.stuDep;
	}
	return *this;
}

bool student::operator==(const student& right) const
{
	if (id == right.id)
		return true;
	return false;
}

course& student::operator[](int index)
{
	if (index < 0 || index > courseAmount)
	{
		cout << "invalid value!.." << endl;
		exit(1);
	}
	return *courses[index];
}



istream& operator>>(istream& in, student& input)
{
	bool flag;
	do {
		flag = true;
		cout << "Enter student's name: " << endl;
		cin.ignore();
		getline(in, input.studentName);
		for (int i = 0; i < input.studentName.length(); i++)
		{
			if (input.studentName[i] < 'A' || (input.studentName[i] > 'Z' && input.studentName[i] < 'a') || input.studentName[i] > 'z')
				flag = false;
		}
	} while (flag == false);
	cout << "Enter student's id: " << endl;
	cin.ignore();
	getline(in, input.id);
	cout << "Enter student's gender <F-female/M-male>: " << endl;
	in >> input.gender;
	cout << "Enter student's age: " << endl;
	in >> input.age;
	return in;
}

ostream& operator<<(ostream& out, student& output)
{
	cout << "Name: " << output.studentName << endl;
	cout << "ID: " << output.id << endl;
	cout << "Gender: " << output.gender << endl;
	cout << "Age: " << output.age << endl;
	
	if (output.stuDep == nullptr)
	{
		cout << "The student is not registered to any department." << endl;
	}
	else
	{
		cout << "Student's department: " << output.stuDep << endl;
	}


	if (output.courseAmount == 0)
	{
		cout << "The student is not registered to any courses." << endl;
	}
	else
	{
		for (int i = 0; i < output.courseAmount; i++)
		{
			cout << output.courses[i] << endl;
		}
	}
	return out;
}

int student::average()
{
	int sum = 0;
	if(courseAmount == 0)
		return 0;

	for (int i = 0; i < courseAmount; i++)
		sum += this->courses[i]->gradeOfStudent(*this);
	return sum / courseAmount;
}

void student::printStudent()
{
	cout << "***********************************************************" << endl;
	cout << "Name: " << studentName << endl;
	cout << "ID: " << id << endl;
	cout << "Gender: " << gender << endl;
	cout << "Age: " << age << endl;

	if (stuDep == nullptr)
	{
		cout << "The student is not registered to any department." << endl;
	}
	else
	{
		cout << "Student's department: " << stuDep->getDepName() << endl;
	}


	if (courseAmount == 0)
	{
		cout << "The student is not registered to any courses." << endl;
	}
	else
	{
		cout << "Student's Courses: " << endl;
		for (int i = 0; i < courseAmount; i++)
		{
			cout << courses[i]->getCourseName() << endl;
		}
	}
}


