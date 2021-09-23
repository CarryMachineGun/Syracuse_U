//HW2
//Due: 11:59PM, Sept. 25 (Saturday)

//@Yuchen_Qst: Do we have student entity?

//Criticals================================
//@Yuchen: Can have your own Function
// No duplicated Student in System. If a duplication student is tried to add , ignore
// No duplicated course is allowed for a student even in different semester, if a duplicated course is tried to add, ignore

#include <iostream>
#include <list>
#include <map>
#include <string>
#include <tuple>
#include <vector>
#include <iomanip>
using namespace std;

class course
{
public:
	string name;
	int section;
	int credits;
	string grade;
	course() {}
	course(string n, int s, int c, string g)
	{
		name = n;
		section = s;
		credits = c;
		grade = g;
	}
	// return numerical grade A:4.000 A-:3.667
	// can be find on Syracuse University GPA calculator
	//You might need to implement some overloaded operators here.
	float num_grade() const
	{
		map<string, float> gpa{{"A", 4.000}, {"A-", 3.6667}};
		return gpa[grade];
	}

	bool operator==(const course &c)
	{
		return name == c.name;
	}

	bool operator>(const course &c)
	{
		return num_grade() > c.num_grade();
	}
};
//Implement the following functions.
//When adding a student, if the student is already in DB, then ignore the operation.
//When adding a course, if the course is already in DB, then ignore the operation.
//When dropping a course, if the course does not exist, then ignore the operation.
//When removing a student, if the student does not exist, then ignore the operation.
//All courses in a semester need to be sorted based on grade (from low to high).
//All semesters will be sorted (from low to high).
//When dropping or adding a course, overall GPA, semester GPA, overall credits and semester credits all need to be updated.

//Semeser numbers:  Spring 2019: 20191; Fall 2019: 20192, etc.

void add_student(map<int, pair<pair<int, float> *, list<pair<int, tuple<int, float, list<course *> *> *> *> *>> &DB, int id);
void remove_student(map<int, pair<pair<int, float> *, list<pair<int, tuple<int, float, list<course *> *> *> *> *>> &DB, int id);
void add_course(map<int, pair<pair<int, float> *, list<pair<int, tuple<int, float, list<course *> *> *> *> *>> &DB, int semester, int id, course c); //20171 Spring semester of 2017; 20172: Fall semester of 2017
																																					 //All courses in the list should be sorted according to grade (increasing order)
void drop_course(map<int, pair<pair<int, float> *, list<pair<int, tuple<int, float, list<course *> *> *> *> *>> &DB, int semester, int id, course c);
void print_student_semester_courses(map<int, pair<pair<int, float> *, list<pair<int, tuple<int, float, list<course *> *> *> *> *>> &DB, int semester, int id);
void print_student_all_courses(map<int, pair<pair<int, float> *, list<pair<int, tuple<int, float, list<course *> *> *> *> *>> &DB, int id);

//Implement additional functions such that you can do
//cout << DB << endl;

//You might need to implement some overloaded operators in the course class.

int main()
{

	map<int, pair<pair<int, float> *, list<pair<int, tuple<int, float, list<course *> *> *> *> *>> DB;

	add_student(DB, 11111);
	course C1("CIS554", 1, 3, "A-"), C2("CSE674", 1, 3, "B+"), C3("MAT296", 8, 4, "A"), C4("WRT205", 5, 3, "A");

	add_course(DB, 20171, 11111, C1);
	add_course(DB, 20171, 11111, C4);
	add_course(DB, 20171, 11111, C3);
	add_course(DB, 20171, 11111, C2);
	print_student_semester_courses(DB, 20171, 11111); // print in ascending order of grade

	drop_course(DB, 20171, 11111, C1);
	print_student_semester_courses(DB, 20171, 11111); //sorted according to course name

	course C5("CIS351", 2, 3, "A-"), C6("PSY205", 5, 3, "B+"), C7("MAT331", 2, 3, "A"), C8("ECN203", 4, 3, "A");
	add_course(DB, 20172, 11111, C5);
	add_course(DB, 20172, 11111, C6);
	add_course(DB, 20172, 11111, C7);
	add_course(DB, 20172, 11111, C8);
	add_course(DB, 20172, 11111, C3);
	print_student_all_courses(DB, 11111); //ID GPA

	add_student(DB, 11112);
	add_course(DB, 20171, 11112, C2);
	add_course(DB, 20171, 11112, C5);
	add_course(DB, 20171, 11112, C7);
	add_course(DB, 20171, 11112, C4);
	print_student_semester_courses(DB, 20171, 11112);

	add_course(DB, 20172, 11112, C8);
	add_course(DB, 20172, 11112, C3);
	add_course(DB, 20172, 11112, C5);
	add_course(DB, 20172, 11112, C1);
	print_student_semester_courses(DB, 20172, 11112);

	print_student_all_courses(DB, 11112);

	cout << DB << endl;
	remove_student(DB, 11111);
	cout << DB << endl;
	return 0;
}

void add_student(map<int, pair<pair<int, float> *, list<pair<int, tuple<int, float, list<course *> *> *> *> *>> &DB, int id)
{
	//Your code
	if (DB.find(id) != DB.end())
	{
		return;
	}
	DB[id].first = new pair<int, float>{0, 0.0};
	DB[id].second = new list<pair<int, tuple<int, float, list<course *> *> *> *>;
	return;
}
void remove_student(map<int, pair<pair<int, float> *, list<pair<int, tuple<int, float, list<course *> *> *> *> *>> &DB, int id)
{
	//Your code
	if (DB.find(id) == DB.end())
	{
		return;
	}
}

void add_course(map<int, pair<pair<int, float> *, list<pair<int, tuple<int, float, list<course *> *> *> *> *>> &DB, int semester, int id, course c)
{
	//Your code
	//1 add course to DB =============================
	//
	pair<int, float> *&overallGpaAndCredit = DB[id].first;
	list<pair<int, tuple<int, float, list<course *> *> *> *> *&outerList = DB[id].second;

	// check whether the course already exist in any semester. if yes, return;
	for (pair<int, tuple<int, float, list<course *> *> *> *eachSemester : *outerList)
	{
		for (course *i : *(get<2>(*(eachSemester->second))))
		{
			if (i->name == c.name)
			{
				cout << "Course already enrolled" << endl;
				return;
			}
		}
	}




	//Main function starts
	pair<int, tuple<int, float, list<course *> *> *> *semesterAndGrade = nullptr;

	//1.1 - check whether the semesterExist in outerList, if exist set semsetrAndGrade to the pair,
	// If not add the correct one

	if (outerList == nullptr)
	{
		outerList = new list<pair<int, tuple<int, float, list<course *> *> *> *>;
	}

	if (outerList->size() == 0)
	{
		semesterAndGrade = new pair<int, tuple<int, float, list<course *> *> *>;
		semesterAndGrade->first = semester;
		outerList->push_back(semesterAndGrade);
	}
	else
	{
		auto i = outerList->begin();
		bool semesterInserted = false;

		while (i != outerList->end())
		{
			// if semester exist, get it to semesterAndGrade
			if ((*i)->first == semester)
			{
				semesterAndGrade = *i;
				semesterInserted = true;
				break;
			}
			// if find the insert pos, insert in into pos
			if ((*i)->first > semester)
			{
				semesterAndGrade = new pair<int, tuple<int, float, list<course *> *> *>;
				semesterAndGrade->first = semester;
				outerList->insert(i, semesterAndGrade);
				semesterInserted = true;
				break;
			}

			i++;
		}

		// if the new inserted semester is larger than all the exist semesters: write a test case inserting at end!!!!!!!!!!!!!!
		if (!semesterInserted)
		{
			if (semesterAndGrade != nullptr)
			{
				cout << "LOGIC ERROR_1!!!!!!" << endl;
			}
			semesterAndGrade = new pair<int, tuple<int, float, list<course *> *> *>;
			semesterAndGrade->first = semester;
			outerList->push_back(semesterAndGrade);
		}
	}

	//1.2 manipulate semesterAndGrade
	//@Yuchen_Qst: int value may be indertinmate !!!!!!!!!!!!
	int &semesterCredit = get<0>(*(semesterAndGrade->second));
	float &semesterGpa = get<1>(*(semesterAndGrade->second));
	list<course *> *&semesterCourses = get<2>(*(semesterAndGrade->second));

	semesterCredit += c.credits;
	//semesterGpa : need GPA calculation!!!!!!!!!!!!!!!!!!!!!!!!!

	//Insert course
	if (semesterCourses == nullptr)
	{
		semesterCourses = new list<course *>;
	}

	if (semesterCourses->size() == 0)
	{
		semesterCourses->push_back(&c);
	}
	else
	{
		auto j = semesterCourses->begin();
		bool courseInserted = false;

		while (j != semesterCourses->end())
		{
			// if the course already in List, the toppest check fails 
			if ((*j)->num_grade() == c.num_grade()){
				cout << "LOGIC ERROR_2!!!!!!!"  << endl;
			}
			// if find the insert pos, insert in into pos
			if ((*j)->num_grade() < c.num_grade())
			{
				semesterCourses->insert(j, &c);
				courseInserted = true;
				break;
			}

			j++;
		}

		if (!courseInserted)
		{
			semesterCourses->push_back(&c);
		}
	}

	//2. Update overall GPA and over all Credit ======================
}

void drop_course(map<int, pair<pair<int, float> *, list<pair<int, tuple<int, float, list<course *> *> *> *> *>> &DB, int semester, int id, course c)
{
	//Your code
}

void print_student_semester_courses(map<int, pair<pair<int, float> *, list<pair<int, tuple<int, float, list<course *> *> *> *> *>> &DB, int semester, int id)
{
	//Your code
}
void print_student_all_courses(map<int, pair<pair<int, float> *, list<pair<int, tuple<int, float, list<course *> *> *> *> *>> &DB, int id)
{
	//Your code
}
