//HW2 By Biyuan Yang
//SU NetID: byang02  SUID:647598250
//HW2
//Due: 11:59PM, Sept. 25 (Saturday)

#include <iostream>
#include <list>
#include <map>
#include <string>
#include <tuple>
#include <vector>
#include <iomanip>
#include<tuple>
using namespace std;

class course {
public:
	string name;
	int section;
	int credits;
	string grade;
	course() {}
	course(string n, int s, int c, string g) { name = n; section = s; credits = c; grade = g; }

	float num_grade() const
	{
		map<string, float> gpa{ {"A", 4.000}, {"A-", 3.667}, {"B+", 3.333}, {"B", 3.000}, {"B-", 2.667}, {"C+", 2.333}, {"C", 2.000}, {"C-", 1.667}, {"D", 1.000}, {"D-", 0.667}, {"F", 0.000} };
		return gpa[grade];
	}

	bool operator==(const course& c)
	{
		return name == c.name;
	}

	bool operator>(const course& c)
	{
		return num_grade() > c.num_grade();
	}

};


ostream& operator<<(ostream& str, const course *c);
ostream& operator<<(ostream& str, const  list<course*  > &list);
ostream& operator<<(ostream& str, const tuple<int, float, list<course*  >*  > &T);
ostream& operator<<(ostream& str, const pair < pair<int, float>*, list<pair<int, tuple<int, float, list<course*  >*  >* >*>*>&pair);
ostream& operator<<(ostream& str, const map<int, pair < pair<int, float>*, list<pair<int, tuple<int, float, list<course*  >*  >* >*>*>>& DB);

//Implement the following functions.
//When adding a student, if the student is already in DB, then ignore the operation.
//When adding a course, if the course is already in DB, then ignore the operation.
//When dropping a course, if the course does not exist, then ignore the operation.
//When removing a student, if the student does not exist, then ignore the operation.
//All courses in a semester need to be sorted based on grade (from low to high).
//All semesters will be sorted (from low to high).
//When dropping or adding a course, overall GPA, semester GPA, overall credits and semester credits all need to be updated.

//Semeser numbers:  Spring 2019: 20191; Fall 2019: 20192, etc. 

void add_student(map<int, pair < pair<int, float>*, list<pair<int, tuple<int, float, list<course*  >*  >* >*>*>>& DB, int id);
void remove_student(map<int, pair < pair<int, float>*, list<pair<int, tuple<int, float, list<course*  >*  >* >*>*>>& DB, int id);
void add_course(map<int, pair < pair<int, float>*, list<pair<int, tuple<int, float, list<course*  >*  >* >*>*>>& DB, int semester, int id, course c); //20171 Spring semester of 2017; 20172: Fall semester of 2017
																//All courses in the list should be sorted according to grade (increasing order)
void drop_course(map<int, pair < pair<int, float>*, list<pair<int, tuple<int, float, list<course*  >*  >* >*>*>>& DB, int semester, int id, course c);
void print_student_semester_courses(map<int, pair < pair<int, float>*, list<pair<int, tuple<int, float, list<course*  >*  >* >*>*>>& DB, int semester, int id);
void print_student_all_courses(map<int, pair < pair<int, float>*, list<pair<int, tuple<int, float, list<course*  >*  >* >*>*>>& DB, int id);




//You might need to implement some overloaded operators in the course class.

int main() {


	map<int, pair < pair<int, float>*, list<pair<int, tuple<int, float, list<course*  >*  >* >*>*>>    DB;

	add_student(DB, 11111);
	//add_student(DB, 11113);
	course C1("CIS554", 1, 3, "A-"), C2("CSE674", 1, 3, "B+"), C3("MAT296", 8, 4, "A"), C4("WRT205", 5, 3, "A");


	add_course(DB, 20171, 11111, C1);
	add_course(DB, 20171, 11111, C4);
	add_course(DB, 20171, 11111, C3);
	add_course(DB, 20171, 11111, C2);
	
	print_student_semester_courses(DB, 20171, 11111);
	
	drop_course(DB, 20171, 11111, C1);
	print_student_semester_courses(DB, 20171, 11111); //sorted according to course name
	

	course C5("CIS351", 2, 3, "A-"), C6("PSY205", 5, 3, "B+"), C7("MAT331", 2, 3, "A"), C8("ECN203", 4, 3, "A");
	add_course(DB, 20172, 11111, C5);
	add_course(DB, 20172, 11111, C6);
	add_course(DB, 20172, 11111, C7);
	add_course(DB, 20172, 11111, C8);
	add_course(DB, 20172, 11111, C3);
	add_course(DB, 20172, 11111, C2);


	print_student_all_courses(DB, 11111);//ID GPA

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

void add_student(map<int, pair < pair<int, float>*, list<pair<int, tuple<int, float, list<course*  >*  >* >*>*>>& DB, int id) {
	//Your code
	if (DB.find(id) != DB.end()) return;
	DB[id].first = new pair<int, float>{ 0, 0.0};
	DB[id].second = new list<pair<int, tuple<int, float, list<course*  >*  >* >*>;
}
void remove_student(map<int, pair < pair<int, float>*, list<pair<int, tuple<int, float, list<course*  >*  >* >*>*>>& DB, int id) {
	//Your code
	if (DB.find(id) == DB.end()) return;

	//delete map
	auto it = DB[id].first;
	auto it1 = DB[id].second;

	// erase data
	for (auto it2:*it1)
	{
		//erase course
		for (auto it3 : *(get<2>(*(it2->second)))) {
			delete it3;
		}


		// earse tuple list
		list<course*>* l = get<2>(*(it2->second));
		delete l;

		//earse tuple
		tuple<int, float, list<course*>*>* t = it2->second;
		delete t;

		//earse pair
		delete it2;
		
	}

	delete it1;
	delete it;


	DB.erase(id);

	return;

}


void add_course(map<int, pair < pair<int, float>*, list<pair<int, tuple<int, float, list<course*  >*  >* >*>*>>& DB, int semester, int id, course c) {
	//Your code
	//Check if student exists
	if (DB.find(id) == DB.end()) return;
	bool find_course = false;
	bool find_semester = false;
	//Check if course exists
	for (auto it : *DB[id].second) {
		for (auto it1 : *get<2>(*it->second)) {
			if (*it1 == c) {
				find_course = true;
				return;
			}
		}
	}
	
	for (auto it : *DB[id].second){
		//Check if semester exists
		if (it->first == semester){
			find_semester = true;
			//Check if course exists
			for (auto it1 : *get<2>(*it->second)) {
				if (*it1 == c) {
					find_course = true;
					return;
				}
				//add course
				auto it3 = (get<2>(*it->second))->begin();
				while (it3 != (get<2>(*it->second))->end()) {
					if ((*it3)->num_grade() < c.num_grade()) {
						it3++;
					}
					else {
						get<2>(*it->second)->insert(it3, new course{ c });
						//updata GPA and credit
						//overall
						DB[id].first->second = ((c.num_grade() * c.credits) + (DB[id].first->second * DB[id].first->first)) / (DB[id].first->first + c.credits);
						DB[id].first->first += c.credits;
						//semester
						get<1>(*it->second) = (c.num_grade() * c.credits + get<1>(*it->second) * get<0>(*it->second)) / (c.credits + get<0>(*it->second));
						get<0>(*it->second) += c.credits;
						return;
					}
					

				}
				get<2>(*it->second)->insert(it3, new course{ c });
				//updata GPA and credit
				//overall
				DB[id].first->second = ((c.num_grade() * c.credits) + (DB[id].first->second * DB[id].first->first)) / (DB[id].first->first + c.credits);
				DB[id].first->first += c.credits;
				//semester
				get<1>(*it->second) = (c.num_grade() * c.credits + get<1>(*it->second) * get<0>(*it->second)) / (c.credits + get<0>(*it->second));
				get<0>(*it->second) += c.credits;
				return;

			}
		}
	}
	//Add a new semester if semester not exists
	if (find_semester == false) {
		auto ll = new list<course*  >;
		ll->push_back(new course{ c });
		auto tp = new tuple<int, float, list<course*>*>{ c.credits,c.num_grade(),ll };
		auto pp = new pair<int, tuple<int, float, list<course*>*>* >{ semester, tp };
		//sort semester
		auto it2 = (DB[id].second->begin());
		while (it2 != (DB[id].second->end()))
		{	
			
			if ((*it2)->first>semester) {
				DB[id].second->insert(it2, pp);
				//cout << *((get<2>(*((*(DB[id].second->begin()))->second)))->begin()) << endl;
				//updata GPA and credit
				//overall
				DB[id].first->second = ((c.num_grade() * c.credits) + (DB[id].first->second * DB[id].first->first)) / (DB[id].first->first + c.credits);
				DB[id].first->first += c.credits;
				return;
			}
			it2++;
		}
		
		DB[id].second->push_back(pp);
		DB[id].first->second = ((c.num_grade() * c.credits) + (DB[id].first->second * DB[id].first->first)) / (DB[id].first->first + c.credits);
		DB[id].first->first += c.credits;
		return;
	}
	return;
}

	void drop_course(map<int, pair < pair<int, float>*, list<pair<int, tuple<int, float, list<course*  >*  >* >*>*>>&DB, int semester, int id, course c) {
		//Your code
		if (DB.find(id) == DB.end()) return;
		bool find_course = false;
		bool find_semester = false;
		for (auto it : *DB[id].second) {
			//Check if semester exists
			if (it->first == semester) {
				find_semester = true;
				auto it1 = get<2>(*(it->second));
				for (auto i = it1->begin(); i != it1->end(); i++)
				{
					if (*(*i) == c)
					{
						//cout << *i << endl;
						find_course = true;
						it1->erase(i);
						//updata GPA and credit
						//overall
						DB[id].first->second = ((DB[id].first->second * DB[id].first->first) - (c.num_grade() * c.credits)) / (DB[id].first->first - c.credits);
						DB[id].first->first -= c.credits;
						//semester
						get<1>(*it->second) = (get<1>(*it->second) * get<0>(*it->second) - c.num_grade() * c.credits) / (get<0>(*it->second) - c.credits);
						get<0>(*it->second) -= c.credits;
						return;

					}
				}

			}
		}
		if (find_course == false or find_semester == false) return;
	}
	


void print_student_semester_courses(map<int, pair < pair<int, float>*, list<pair<int, tuple<int, float, list<course*  >*  >* >*>*>>& DB, int semester, int id) {
	//Your code
	cout << "Student ID: " << id << endl;
	cout << "Semester: " << semester << endl;
	for (auto it : *DB[id].second) {
		if (it->first == semester) {
			cout << *it->second <<endl ;
		}		
	}	
	cout << "\n"<< endl;
	return;
}
void print_student_all_courses(map<int, pair < pair<int, float>*, list<pair<int, tuple<int, float, list<course*  >*  >* >*>*>>& DB, int id) {
	//Your code
	cout << "Student ID: " << id << endl;
	cout << DB[id] << "\n"<< endl;

	return;


}


ostream& operator<<(ostream& str, const course *c) {
	str <<"(" << c->name << " " << c->section << " " << c->credits << " " << c->grade << ") ";
	return str;
}
ostream& operator<<(ostream& str, const tuple<int, float, list<course*  >*  > &T) {
		auto it = T;
	
		str << "GPA: " << get<1>(it) << endl;
		str << "Credits: " << get<0>(it) << endl;
		for (auto it1 : *(get<2>(it))) {
			str << it1;
		}
		// cout << "\n";
		return str;
}
ostream& operator<<(ostream& str, const pair < pair<int, float>*, list<pair<int, tuple<int, float, list<course*  >*  >* >*>*>& pair) {
	auto it = pair;
	str << "Overall GPA: " << setprecision(2) << fixed << it.first->second << endl << "Overall Credits:" << it.first->first << endl;
	for (auto it2 : *it.second) {
		str << "Semester: " << it2->first << endl;
		str << *it2->second << endl;
	}
	return str;
}

//Implement additional functions such that you can do
//cout << DB << endl;
ostream& operator<<(ostream& str, const map<int, pair < pair<int, float>*, list<pair<int, tuple<int, float, list<course*  >*  >* >*>*>>& DB) {
	for (auto i : DB) {
		str << "Student ID: " << i.first << "\n";
		str << "Overall GPA: " << setprecision(2) << fixed <<  i.second.first->second << "\n" << "Overall Credits: " << i.second.first->first << endl;
		for (auto it : *(i.second.second)) {
			str << "Semester: " << it->first << endl;
			//auto it1=it->second
			str << "GPA: " << get<1>(*it->second) << endl;
			str << "Credits: " << get<0>(*it->second) << endl;
			for (auto it1 : *(get<2>(*it->second))) {
				str << it1 << "";
			}
			cout << endl;

		}
		// cout << endl;

	}
	return str;
}

