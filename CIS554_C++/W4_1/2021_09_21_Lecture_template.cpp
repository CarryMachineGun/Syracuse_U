//template
#include <iostream>
#include <vector>
#include <list>
#include <map>

using namespace std;

class ThreeD1 {
public:
	int ht;
	int wid;
	int dep;
};

class ThreeD2 {
public:
	float ht;
	float wid;
	float dep;
};


template <class T> class ThreeD {
	//template <typename T> ...
public:
	T ht;
	T wid;
	T dep;
	ThreeD(T i, T j, T k) :ht(2 * i), wid(2 * j), dep(2 * k) {}
	//ThreeD(T i, T j, T k){ht= 2*i; wid= 2*j; dep=2*k;}

	ThreeD() { ht = wid = dep = (T)0; }
};


template <class T> ostream& operator<<(ostream& str, const ThreeD<T>& t);

template <class T> ostream& operator<<(ostream& str, const vector<T>& V);
template <class T> ostream& operator<<(ostream& str, const list<T>& L);
template <class T> ostream& operator<<(ostream& str, const vector<T*>& V);
template <class T> ostream& operator<<(ostream& str, const list<T*>& L);
template <class T1, class T2> ostream& operator<<(ostream& str, const map<T1, T2>& M);
template <class T1, class T2> ostream& operator<<(ostream& str, const map<T1, T2 *>& M);

int main() {
	ThreeD<int> t1{ 2,3,4 };
	ThreeD<float> t2{ 5,6,7 };
	cout << t1 << " " << t2 << endl;

	vector<int> V1{ 1,2,3,4,5 };
	cout << V1 << endl;
	ThreeD<int> t3{ 8,9,10 };
	vector<ThreeD<int>> V2{ t1, t3 };
	cout << V2 << endl;

	vector<list<int>> V3{ {1, 2, 3 }, {5,6} };
	cout << V3 << endl;

	vector<int*> V4{ new int {6}, new int {4}, new int {11} };
	cout << V4 << endl;

	list<int*> L4{ new int {6}, new int {4}, new int {11} };
	cout << L4 << endl;

	map<int, ThreeD<int>> M1{ {6, ThreeD<int>{1,2,3}}, {4, ThreeD<int>{7,8,9}} };
	cout << M1 << endl;

	map<int, ThreeD<int> *> M2{ {6, new ThreeD<int> {1,2,3}}, {4, new ThreeD<int> {7,8,9}} };
	cout << M2 << endl;

	/*
	list<vector<int *>*> L6;

	cout << L6 << endl;
	*/

	int i1{ 12 }, i2{ 13 };
	int& r1{ i1 };//r1 and i1 are two names of the same object
	r1 = 100; //the same as i1 = 100;
	

	auto const & r2{ i2 };
	i2 = 2000;
	//r2 = 3000; error! read only

	//int& r3; error.
	
	//auto& r4{ 25 }; error

	vector<int> V9{ 3,4,5,6,7 };
	//auto& r5{ V9.begin() };

	int* p5{ new int {56} };
	int*& r6{ p5 };//one object
	int* p6{ p5 };//two objects
	p6 = new int{ 34 };




	return 0;
}


template <class T1, class T2> ostream& operator<<(ostream& str, const map<T1, T2*>& M) {
	str << "{ ";
	for (auto i : M) { str << i.first << " " << *(i.second) << "  "; }
	str << "}";
	return str;
}

template <class T1, class T2> ostream& operator<<(ostream& str, const map<T1, T2>& M) {
	str << "{ ";
	for (auto i : M) { str << i.first << " " << i.second << "  "; }
	str << "}";
	return str;
}


template <class T> ostream& operator<<(ostream& str, const list<T*>& L) {
	str << "< ";
	for (auto& i : L) { str << *i << " "; }
	str << ">";
	return str;
}

template <class T> ostream& operator<<(ostream& str, const list<T>& L) {
	str << "< ";
	for (auto& i : L) { str << i << " "; }
	str << "List overload operator is called";

	str << ">";
	return str;
}
template <class T> ostream& operator<<(ostream& str, const vector<T*>& V) {
	str << "[ ";
	for (auto& i : V) { str << *i << " "; }
	str << "]";
	return str;

}



template <class T> ostream& operator<<(ostream& str, const vector<T>& V) {
	str << "[ ";
	for (auto& i : V) { str << i << " "; }
	str << "]";
	return str;

}

template <class T> ostream& operator<<(ostream& str, const ThreeD<T>& t) {
	str << "[" << t.ht << ", " << t.wid << ", " << t.dep << "]";
	str << "ThreeD overload operator is called";
	return str;
}