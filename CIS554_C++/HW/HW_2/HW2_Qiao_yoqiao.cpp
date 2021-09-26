//HW2 by Yong Qiao
//SU Net ID: yoqiao  SUID: 278632551

//HW2
//Due: 11:59PM, Sept. 25 (Saturday)

#include <iostream>
#include <list>
#include <map>
#include <string>
#include <tuple>
#include <vector>
#include <iomanip>
using namespace std;

class course {
public:
	string name;
	int section;
	int credits;
	string grade;
	course() {}
	course(string n, int s, int c, string g) { name = n; section = s; credits = c; grade = g; }

    float num_grade() const {
        map<string, float> gpa{{"A", 4.0}, {"A-", 3.6666}, {"B+", 3.3333}, {"B", 3.0}, 
		{"B-", 2.6666}, {"C+", 2.3333}, {"C", 2.0}, {"C-", 1.6666}, {"D", 1.0}, {"D-", 0.666},
		{"F", 0.0} };

        return gpa[grade];
    }
	//You might need to implement some overloaded operators here.
    // compare if two courses are equal
	bool operator == (const course & c) const {
        return name == c.name;
    }

    // overload < operator
	bool operator<(const course& c) const {
        if(num_grade() != c.num_grade()) {
            return num_grade() < c.num_grade(); 
        }else{
            return name < c.name;
        }
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

void add_student(map<int, pair < pair<int, float>*, list<pair<int, tuple<int, float, list<course*  >*  >* >*>*>>& DB, int id);
void remove_student(map<int, pair < pair<int, float>*, list<pair<int, tuple<int, float, list<course*  >*  >* >*>*>>& DB, int id);
void add_course(map<int, pair < pair<int, float>*, list<pair<int, tuple<int, float, list<course*  >*  >* >*>*>>& DB, int semester, int id, course c); //20171 Spring semester of 2017; 20172: Fall semester of 2017
																//All courses in the list should be sorted according to grade (increasing order)
void drop_course(map<int, pair < pair<int, float>*, list<pair<int, tuple<int, float, list<course*  >*  >* >*>*>>& DB, int semester, int id, course c);
void print_student_semester_courses(map<int, pair < pair<int, float>*, list<pair<int, tuple<int, float, list<course*  >*  >* >*>*>>& DB, int semester, int id);
void print_student_all_courses(map<int, pair < pair<int, float>*, list<pair<int, tuple<int, float, list<course*  >*  >* >*>*>>& DB, int id);

//Implement additional functions such that you can do
//cout << DB << endl;
ostream &operator<<(ostream &str, const course &c);
ostream &operator<<(ostream &str, const map<int, pair < pair<int, float>*, list<pair<int, tuple<int, float, list<course*  >*  >* >*>*>>& DB);

//You might need to implement some overloaded operators in the course class.

//overload << operator to print course information
ostream &operator<<(ostream &str, const course &c)
{
	str << "(" << c.name << " " << c.section << " " << c.credits << " " << c.grade << ") ";
	return str;
}

//overload << operator to print DB information
ostream &operator<<(ostream &str, const map<int, pair < pair<int, float>*, list<pair<int, tuple<int, float, list<course*  >*  >* >*>*>>& DB) {
    for(auto it = DB.begin(); it != DB.end(); it++) {
        auto& overall_credit_gpa = it->second.first;
        auto& semesters_list = it->second.second;

        str << "Student ID: " << it->first << endl;
		str << "Overall GPA: " << setprecision(2) << fixed << overall_credit_gpa->second << endl;
		str << "Overall Credits: " << overall_credit_gpa->first << endl;

        for(auto s : *semesters_list) {
            auto& semester_course = get<2>(*(s->second));
            str << "Semester: " << s->first << endl;
			str << "GPA: " << setprecision(2) << fixed << get<1>(*(s->second)) << endl;
			str << "Credits: " << get<0>(*(s->second)) << endl;
            for(course *c : *semester_course) {
                str << (*c);
            }
            str << endl;
        }
    }
    str << endl;
    return str;
}

int main() {

	
	map<int, pair < pair<int, float>*, list<pair<int, tuple<int, float, list<course *  > *  > * >*>*>>    DB;

	add_student(DB, 11111);
	course C1("CIS554", 1, 3, "A-"), C2("CSE674", 1, 3, "B+"), C3("MAT296", 8, 4, "A"), C4("WRT205", 5, 3, "A");

	add_course(DB, 20171, 11111, C1);
	add_course(DB, 20171, 11111, C4);
	add_course(DB, 20171, 11111, C3);
	add_course(DB, 20171, 11111, C2);
	print_student_semester_courses(DB, 20171, 11111);

	drop_course(DB, 20171, 11111, C1);
	print_student_semester_courses(DB, 20171, 11111); //sorted according to grade (from low to high)

	course C5("CIS351", 2, 3, "A-"), C6("PSY205", 5, 3, "B+"), C7("MAT331", 2, 3, "A"), C8("ECN203", 4, 3, "A");
	add_course(DB, 20172, 11111, C5);
	add_course(DB, 20172, 11111, C6);
	add_course(DB, 20172, 11111, C7);
	add_course(DB, 20172, 11111, C8);
	add_course(DB, 20172, 11111, C3);
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
	if(DB.find(id) != DB.end()) return;
	DB[id] = {};
	DB[id].first = new pair<int, float>{ 0, 0.0 };
	DB[id].second = new list<pair<int, tuple<int, float, list<course*  >*  >* >*>;
}

void remove_student(map<int, pair < pair<int, float>*, list<pair<int, tuple<int, float, list<course*  >*  >* >*>*>>& DB, int id) {
	//Your code
    if(DB.find(id) == DB.end()) return;
	for(auto it = DB.begin(); it != DB.end(); it++) {
		// delete the credit and gpa pointer 
		//delete pair<int, float>*, which contains overall credit and grade information.
		if(it->first == id) {
			delete ((it->second).first);
			auto& r2 =  *((it->second).second); //list: semesters information
			for(auto it1 = r2.begin(); it1 != r2.end(); it1++) {	// pair<int, tuple<int, float, list<course* >* >* >* : one semester information
				auto& sem = (*it1)->second;
				auto& c_list = get<2>(*sem);
				for(auto it2 = c_list->begin(); it2 != c_list->end(); it2++) { //delete course*
					delete *it2;
				}		
				delete c_list; //delete list<>*
				delete sem; //delete tuple<>*
				delete *it1;//delete pair*
			}
			delete (it->second).second;
		}
	}
	DB.erase(id);
}


void add_course(map<int, pair < pair<int, float>*, list<pair<int, tuple<int, float, list<course*  >*  >* >*>*>>& DB, int semester, int id, course c) {

	//Your code

    //check if the id exists in DB
	if(DB.find(id) == DB.end()) return;	
	
    // check if the course already exists in DB
    auto& list_out = (*(DB[id].second));
    for (pair<int, tuple<int, float, list<course *> *> *> *sem : list_out) {
		for (course *c1 : *(get<2>(*(sem->second)))) {
			if (*c1 == c) return;
		}
	}

    int& overall_credit = (*(DB[id].first)).first;
    float& overall_gpa = (*(DB[id].first)).second;

    //insert the course information
	for(auto it = DB.begin(); it != DB.end(); it++) {

        //check whether the semester exists or not
		bool flag_semester = false;	
		if(it->first == id){
			
			auto& r2 =  *((it->second).second); //list
			course* c_t = new course(c);

			//check whether the semester exists
			for(auto it1 = r2.begin(); it1 != r2.end(); it1++) {
				auto& sem = (*it1)->first;
				if(sem == semester){
					flag_semester = true;	
				}
				//semester already exists
				if(flag_semester == true) {

                    bool course_insert = false;

					auto& sem_tuple = (*((*it1)->second));
					// update the gpa and overall credit of this semester
					float overall_score = get<0>(*((*it1)->second)) * get<1>(*((*it1)->second)) + c.num_grade() * c.credits;
					int overall_credit_sem = get<0>(*((*it1)->second)) + c.credits;
					float sem_gpa = overall_score / overall_credit_sem;
					
					//the inner course list
                    auto& list_2 = (get<2>(*((*it1)->second)));
					//insert according to the grade, keep the course list in order.
					for(auto it2 = list_2->begin(); it2 != list_2->end(); it2++ ) {
						if( *c_t < (**it2)) {
							list_2->insert(it2, c_t);
                            course_insert = true;
                            break;
						}
					}
                    if(course_insert == false) {
                        list_2->push_back(c_t);
                    }
					
					sem_tuple = {overall_credit_sem, sem_gpa, list_2 };
					break;
				}
			}
            //semester does not exist, we need to create this semester
			if(flag_semester == false) {

				list<course*> * list_2  = new list<course*>;
				list_2->push_back(c_t);
				
				tuple<int, float, list<course* >* >* tuple_1 = new tuple<int, float, list<course* >* >{c.credits, c.num_grade(), list_2};
				pair<int, tuple<int, float, list<course* >* >* >* pair_1 = new pair<int, tuple<int, float, list<course* >* >* >(make_pair( semester, tuple_1 ));
				
                // keep the semester in order
                bool semester_insert_flag = false;
                for(auto it = (DB[id].second)->begin(); it != (DB[id].second)->end(); it++) {
                    if(semester < (*it)->first) {
                        semester_insert_flag = true;
                        (*(DB[id].second)).insert(it, pair_1);
                        break;
                    }
                }
                
                //insert the semester pair directly to the end of the semester list
                if(semester_insert_flag == false) {
                    (*(DB[id].second)).push_back(pair_1);
                }
			}
		}
	}

    overall_gpa = ( (overall_gpa * overall_credit) + (c.num_grade() * c.credits) ) / (overall_credit + c.credits);
    overall_credit += c.credits;	
    return;
}

void drop_course(map<int, pair < pair<int, float>*, list<pair<int, tuple<int, float, list<course*  >*  >* >*>*>>& DB, int semester, int id, course c) {
	//Your code
    if(DB.find(id) == DB.end()) return;

    auto& overall_credit_gpa = DB[id].first;
    auto& semesters_list = DB[id].second;
    pair<int, tuple<int, float, list<course *> *> *>* semester_info = nullptr;
    //check 1. whether semester item exists in DB
    //      2. course item exists in DB
    bool semester_legal = false;

    for(auto s : *semesters_list) {
        if(s->first == semester) {
            semester_legal = true; 
            semester_info = s;
        }
    }

    if(semester_legal == false) return;

    //drop the course
    bool course_deleted = false;

    int& semester_credit = get<0>(*(semester_info->second));
    float& semester_gpa = get<1>(*(semester_info->second));

    auto& course_list = get<2>(*(semester_info->second));
    int& overall_credit = overall_credit_gpa->first;
    float& overall_gpa = overall_credit_gpa->second;
    
	for (auto it = course_list->begin(); it != course_list->end(); it++) {
        auto& c_p = *it;
		if (*(c_p) == c) {
            delete c_p;
			course_list->erase(it);
			course_deleted = true;
            break;
		}
	}
    // update semester and overall gpa/credit information
	if (course_deleted) {
		semester_gpa = ((semester_gpa * semester_credit) - (c.num_grade() * c.credits)) / (semester_credit - c.credits);
		overall_gpa = ((overall_gpa * overall_credit) - (c.num_grade() * c.credits)) / (overall_credit - c.credits);
		semester_credit -= c.credits;
		overall_credit -= c.credits;
	}
	return;
}

void print_student_semester_courses(map<int, pair < pair<int, float>*, list<pair<int, tuple<int, float, list<course*  >*  >* >*>*>>& DB, int semester, int id) {
	//Your code
    if(DB.find(id) == DB.end()) return;
	cout << "Student ID: " << id << endl;
	cout << "Semester: " << semester << endl;

	auto& r =  *(DB[id].second); //list
	for(auto it : r) {
		if((*it).first == semester) {
			auto& tup = *((*it).second);
			int credit_sem = get<0>(tup);
			float gpa_sem = get<1>(tup);
			cout << "GPA : " << setprecision(2) << fixed << gpa_sem << endl;
			cout << "Credits : " << credit_sem << endl;
			//print the information of the course
			list<course*> course_list = *(get<2>(tup));
			for(course* c : course_list) {
				cout << (*c);
			}
		}
	}
	cout << endl << endl;
	return;
}
void print_student_all_courses(map<int, pair < pair<int, float>*, list<pair<int, tuple<int, float, list<course*  >*  >* >*>*>>& DB, int id) {
	//Your code

    if(DB.find(id) == DB.end()) return;

    auto& overall_credit_gpa = DB[id].first;
    auto& semester_info = DB[id].second;

    cout << "Student ID: " << id << endl;
	cout << "Overall GPA: " << setprecision(2) << fixed << overall_credit_gpa->second << endl;
	cout << "Overall Credits: " << overall_credit_gpa->first << endl;

    // traverse the semester information list
    for (auto s : *semester_info) {
        // get the inner course list
		auto& inner_list = get<2>(*(s->second));

		cout << "Semester: " << s->first << endl;
		cout << "GPA: " << setprecision(2) << fixed << get<1>(*(s->second)) << endl;
		cout << "Credits: " << get<0>(*(s->second)) << endl;
		for (course *c : *inner_list) {
			cout << *c;
		}
		cout << endl;
    }
	cout << endl << endl;
	return;
}


