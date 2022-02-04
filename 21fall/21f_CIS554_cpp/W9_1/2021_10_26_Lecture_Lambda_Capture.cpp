
#include <iostream>
#include <map>
using namespace std;

int main() {
	int int_value = 1;
	for (int i = 0; i < 5; i++) {
		cout << [int_value]() {return int_value; }() << " ";
		//int_value is read-only.  Any attemp to modify it inside the lambda will cause error.
		int_value++;
	}
	//The above loop will print 1 2 3 4 5

	cout << endl;
	int_value = 1;
	auto my_lambda = [int_value]() {return int_value; };
	for (int i = 0; i < 5; i++) {
		cout << my_lambda() << " ";
		int_value++;
	}
	//The above loop will print 1 1 1 1 1

	cout << endl;
	int_value = 1;
	//auto my_lambda_ = [int_value]() mutable {int_value++;  return int_value; };
	for (int i = 0; i < 5; i++) {
		cout << [int_value]() mutable {int_value++;  return int_value; }() << " ";
		//int_value++;
	}
	//The above loop will print 2 2 2 2 2

	cout << endl;
	int_value = 1;
	auto my_lambda_ = [int_value]() mutable {int_value++;  return int_value; };
	for (int i = 0; i < 5; i++) {
		cout << my_lambda_() << " ";
	}
	//The above loop will print 2 3 4 5 6

	cout << endl;
	int_value = 1;
	for (int i = 0; i < 5; i++) {
		cout << [&int_value]()  {int_value++;  return int_value; }() << " ";
		int_value++;
	}
	//The above loop will print 2 4 6 8 10


	cout << endl;
	int_value = 1;
	auto my_lambda_1 = [&int_value]()  {int_value++;  return int_value; };
	for (int i = 0; i < 5; i++) {
		cout << my_lambda_1() << " ";
	}
	//The above loop will print 2 3 4 5 6

	cin.get();


	return 0;
}