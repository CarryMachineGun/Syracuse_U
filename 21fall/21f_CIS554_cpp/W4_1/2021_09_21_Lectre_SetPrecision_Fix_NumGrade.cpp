#include <iostream>
#include <map>
#include <list>
#include <vector>
#include <iomanip>

using namespace std;


class course {
public:
	string name;
	string grade;
	float num_grade() const{
	
		map<string, float> gpa{ {"A", 4.000 }, {"A-", 3.667}, {"B+", 3.334}, {"B", 3.000} };

		return gpa[grade];


		}

	bool operator==(const course& c) const {
		 return name == c.name;
	}

	bool operator<(const course& c) const {

		return num_grade() < c.num_grade();
	}

};


int main() {

	float f1{ 3.14759 };
	cout << f1 << endl;
	cout << setprecision(5) << f1 << endl;
	cout << setprecision(2) << fixed << f1 << endl;



	return 0;
}