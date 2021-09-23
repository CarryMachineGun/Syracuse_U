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
	ThreeD(T i, T j, T k):ht(2*i), wid(2*j), dep(2*k){}
	//ThreeD(T i, T j, T k){ht= 2*i; wid= 2*j; dep=2*k;}

	ThreeD() { ht = wid = dep = (T)0; }
};


template <class T> ostream& operator<<(ostream& str, const ThreeD<T>& t);

template <class T> ostream& operator<<(ostream& str, const vector<T>& V);
template <class T> ostream& operator<<(ostream& str, const list<T>& L);

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

	/*
	vector<list<vector<list<ThreeD<float>>>>>>  V6;
	cout << V6 <<endl;
	
	*/

	return 0;
}


template <class T> ostream& operator<<(ostream& str, const list<T>& L) {
	str << "< ";
	for (auto& i : L) { str << i << " "; }
	str << ">";
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
	return str;
}