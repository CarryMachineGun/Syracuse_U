//both funciton and lambda are callables
//functor is another callable
#include <cmath>
#include <iostream>
#include <algorithm>
#include <list>
#include <typeinfo> //for typeid
#include <functional>//for function
using namespace std;

bool f1(int a, int b) { return a % 5 < b % 5; }

int min(int a, int b, function<bool(int, int)> func) {//function pointer only allows the passing of function or lambda with capturing
	return func(a, b) ? a : b;
}



int main() {
	/*
A lambda (or lambda expression) consists of three parts:
[capture clause](argument list){function body}
Capture list allows you to specify which objects (variables) in
the scope of calling function can be accessed in the lambda.
Two types of access: Access (or Capture) by value or
Access (capture) by reference.  See examples below.
Argument list is the same as argument list of regular function.

Lambda is primarily used for in-place function definition and/or
invocation.  Although it can have a "name" and be re-used, it is
primarily used as an un-named function definition.
	*/
	list<int> L1{ 7,4,3,9,5 };
	L1.sort([](int a, int b) {return a % 5 < b % 5; });
	//Equivalent to L1.sort(f1);
	//in-place function definition
	//define a function at a plece it is needed
	//The lambda here does not capture any local objects.
	//[](){cout << 500 <<endl;}
	//[]{cout <<500 <<endl;

	for (int i : L1) { cout << i << " "; };
	cout << endl;
	int j{ 10 }, s{ 100 };
	list<int> L2{ 1,2,3,4 };
	for_each(L2.begin(), L2.end(), [j, &s](int i) {s += i + j; });
	//capture by value does not allow change of the value
	//it is different from call by value for function
	/*
		The lambda here captures two local objects j and s.
		j is captured by value and is thus read-only.  Any attempt
		to modify the value of j will lead to compilation error.
		s is capture by reference.  It permits both read and write.
		Similar to call by reference in a function, there will be a single
		object s.  Thus, any modification on s in lambda will actually
		modify the s in the scope of calling function.

	More on capture clause:
		[&] : access all variables with both read and write (i.e., access by reference)
		[=] : access all variables with read only (i.e., access by value)
		[&, i]: i read only and all others both read and write
		[=, &i, &j] :  i and j both read and write, all others read only
		[=, i] : error
	*/
	cout << s << endl;
	for (int i : L2) { [j, &s](int i) {s += i + j; }(i); }
	cout << s << endl;

	auto p = [](int a, int b) {return sqrt(abs(a * a - b * b)); };

	cout << p(3, 9) << endl;
	cout << p(7, 15) << endl;



	cout << typeid(p).name() << endl;
	//every lambda has its only unique type.


	list<int*> L3{ new int{4}, new int{7}, new int {9}, new int{3}, new int{1} };

	auto it = find_if(L3.begin(), L3.end(), [](int* i) {return *i == 9; });

	if (it != L3.end()) L3.erase(it);
	for (int* i : L3) { cout << *i << " "; }
	cout << endl;
	cout << min(2, 8, f1) << endl;
	cout << min(2, 8, [](int a, int b) {return a % 5 < b % 5; });

	return 0;
}
