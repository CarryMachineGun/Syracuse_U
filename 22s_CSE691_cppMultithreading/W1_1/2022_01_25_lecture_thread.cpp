//Thread I  -- Creating Threads from callables (regular functions, functors, and lambda) and member function

#include <iostream>
#include <thread>

using namespace std;

void f1(int k, int& s) {
	for (int i = 0; i < k; ++i) s += i * i;
}


class myFunctorClass {
public:

	void operator()(int k, int& s) {
		for (int i = 0; i < k; ++i) s += i * i;
	}
};

class myFunctionClass {
public:
	int value;
	myFunctionClass(int i) { value = i; };
	myFunctionClass(){}

	void f1(int k, int& s) {
		for (int i = 0; i < k; ++i) s += i * i;
		value = 100;
	}
};



int main() {


	cout << thread::hardware_concurrency() << endl;

	int s1{ 0 }, s2{ 0 };
	thread T1{ f1, 200, ref(s1) };//start running
	/*
	Alternatively we can write it as:
	thread T1(f1, 200, ref(s1) );//{} is more up to date.
	*/
	thread T2{ f1, 100, ref(s2) };//start running
	cout << s1 << endl;//

	//using operator=   move assignment

	int s[10]{ 0,0 };
	thread T[10];
	for (int i = 0; i < 10; ++i) {

		T[i] = thread{f1, (i + 1) * 100, ref(s[i])};//start running
	}

	for (int i = 0; i < 10; ++i) T[i].join();

	for (auto i : s) cout << i << " ";


	T1.join();//main thread will pause until T1 completes and then resume.
	//Without join(), most compilers will report errors.

	T2.join();
	cout << s1 << endl;

	s1 = 0;
	myFunctorClass m1;
	thread T3{ m1, 100, ref(s1) };
	T3.join();
	cout << s1 << endl;

	s1 = 0;
	thread T4{ [](int k, int& s) {for (int i = 0; i < k; ++i) s += i * i; }, 100, ref(s1)};

	T4.join();
	cout << s1 << endl;
	s1 = 0;

	thread T5{ [&s1](int k) {for (int i = 0; i < k; ++i) s1 += i * i; }, 100 };
	T5.join();
	cout << s1 << endl;

	s1 = 0;
	s2 = 0;
	myFunctionClass mf1{ 200 };
	thread    T6{ &myFunctionClass::f1,mf1, 200, ref(s1) };//mf1: call by value

	myFunctionClass mf2{ 200 };
	thread    T7{ &myFunctionClass::f1,  ref(mf2), 200, ref(s2) }; //mf2: call by reference
	/*
	thread    T7{ &myFunctionClass::f1,  &mf2, 200, ref(s2) }; will also work
	
	*/
	T6.join();
	T7.join();

	cout << s1 << " " << s2 << " " << mf1.value << " " << mf2.value << endl;

	return 0;
}
