
//Callables:  functions, lambda, functors
#include <iostream>
#include <functional> //to use function
#include <list>
#include <vector>
#include <set>
#include <map>
#include <string>

using namespace std;




class myCompare {

public:
	int s{ 20 };//s has a default value 20
	bool operator()(const int &i, const int &j) const { return i % 2 < j % 2; }
	bool operator()(int i) { return i < s; }

}  f3;
myCompare f4;//gloval variabel f3;



bool f1(int i, int j) { return i < j; }
bool f11(int i, int j) { return i > j; }

int Max(int i, int j, bool (*F)(int p, int q)) {

	return F(i, j) ? j : i;//if (i, j) return true then statement return j else retrun i;

}//Allow passing a function or a lambda without capturing anything

int Max1(int i, int j, function<bool(int m, int n)>  F) {//Allows all callables
	return F(i, j) ? j : i;
}

template <class T> int Max2(int i, int j, T F) {//Allows all callables
	return F(i, j) ? j : i;
}


int main() {
	//pointer to function
	int s1{ 20 };
	bool (*pF) (int i, int j);
	bool (*pF1) (int i, int j) { f1 };
	//pointer pF to a function which returns bool and takes two int arguments i and j
	pF = f1;//function name is the address of the function in memory
	cout << f1(5, 3) << " " << pF(5, 3) << endl;

	cout << Max(3, 5, f1) <<" "<<Max(5,3, f1) << endl;
	cout << Max(3, 5, [](int i, int j) {return i%5 < j%5; }) <<endl;
	//cout << Max(3, 5, [s1](int i, int j) {return i%5 < j%5; }) <<endl; will not compiler
	/*
	pF = *f1; also works
	pF = *****f1; also works
	pF = &f1; also works
	but not pF= &&f1;  won't work
	*/

	myCompare f2;
	cout << f2(3, 4) << " " << f2(25) <<endl;//f2 is a functor
	//cout << Max(3,6, f2) << endl;  Error! //can't pass functor to function pointer

	int s2{ 30 };
	cout << Max1(3, 6, f1) << "  " << Max1(3, 6, [s2](int i, int j) {return i < j; }) << " " <<
		Max1(3, 6, f2) << endl;

	cout << Max2(3, 6, f1) << "  " << Max2(3, 6, [s2](int i, int j) {return i < j; }) << " " <<
		Max2(3, 6, f2) << endl;

	list<int> L1{ 6,5,2,9,4,1,8,7 };
	L1.sort();
	for (auto& i : L1) { cout << i << " "; }
	cout << endl;
	list<int> L2{ 6,5,2,9,4,1,8,7 };
	L2.sort(f11);
	for (auto& i : L2) { cout << i << " "; }
	cout << endl;
	list<int> L3{ 6,5,2,9,4,1,8,7 };
	L3.sort(f2);
	for (auto& i : L3) { cout << i << " "; }
	cout << endl;
	list<int> L4{ 6,5,2,9,4,1,8,7 };
	L4.sort([s2](int i, int j) {return i % 3 < j % 3;   });
	for (auto& i : L4) { cout << i << " "; }
	cout << endl;


	set<int> S1{  6,5,2,9,4,1,8,7 };
	for (auto& i : S1) { cout << i << " "; }
	cout << endl;
	set<int, myCompare > S2{ 6,5,2,9,4,1,8,7 };
	for (auto& i : S2) { cout << i << " "; }
	cout << endl;


	return 0;
}