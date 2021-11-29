
#include <iostream>
#include <vector>
using namespace std;

class my_class {
public:
	static int num_objects;//static members are associated with class, rather than objects of the class
	my_class() { num_objects++; }

	static void get_num_objects() { cout << num_objects << endl; }
	int operator()(){
		return 100;
	}
};
int my_class::num_objects = 0; //static data member has to be initialized outside the class.


void fun1() {
	static int num_fun1_calls = 1; //Static variable will only be initialized when the function
					// is invoked for the first time.
					//The value of static variable will continue into next time when
					//the function is invoked.
	//Such object is sometimes called persistent.
	cout << "num_fun1_calls = " << num_fun1_calls <<endl;
	num_fun1_calls++;
}

int main() {//main is an independent funciton or free function --- not a member function of a class
	my_class m1, m2, m3;

	//Both the following two statements are valid to access num_objects
	cout << my_class::num_objects << endl;
	cout << m1.num_objects << endl;
	m1.get_num_objects();

	fun1();//1 -> 2
	fun1();//2 ->3
	fun1();//3->4
	fun1();//4->5

	cout << "===================" << endl;

	cout << my_class()() << endl;

	auto lam = [](int a, int b){return a+b;};

	cout << lam(1,2) << endl;

	vector<int> arr{1,2,3,4,5,6,7};

	arr.resize(3);

	for(int i : arr) cout << i << ", ";	
	cout << endl;

	return 0;
}