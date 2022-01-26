
//Hash Table
#include <iostream>
#include <map>//multimap
#include <unordered_map>//unordered_multimap
#include <set> //multiset
#include <unordered_set>//unordered_multiset
#include <string>
#include <algorithm>
#include <vector>

using namespace std;

template <class T>  class ThreeD {
public:
	T ht;
	T wid;
	T dep;
	ThreeD(T i, T j, T k) : ht(i), wid(j), dep(k){}
	ThreeD(){}
	T vol() const { return ht * wid * dep; }
	T area() const { return 2 * (ht * wid + wid * dep + dep * ht); }
};

template <class T> class myCompare {
public:
	bool operator()(const ThreeD<T>& t1, const ThreeD<T>& t2) const {
		return t1.vol() < t2.vol();
	}
	/*size_t operator()(const ThreeD<T>& t) const {
		hash<int> h1;
		return h1(t.vol() * t.area() + 101);
	}*/
	
};

template <class T> class my_equal_to {
public:

	bool operator()(const ThreeD<T>& t1, const ThreeD<T>& t2) const {
		return t1.vol() == t2.vol();
	}

};
template <class T> class my_hash {
public:
	size_t operator()(const ThreeD<T>& t)  const{
		hash<int> h1;
		return h1(t.vol() * t.area() + 101);
	}


};

template <class T> ostream& operator<<(ostream& str, const ThreeD<T>& t) {
	str << "(" << t.ht << ", " << t.wid << ", " << t.dep << ")";
	return str;
}




int main() {
	hash<int> h1;
	//cout << h1(5) << " " << h1(5) << endl;
	cout << h1(100) << " " << h1(101) << " " << h1(102) << endl;
	char c1[]{ "This is good!" };
	char c2[]{ "This is good!" };
	cout << "*********" << endl;
	cout << *c1 << " " << c1 << endl;

	hash<char*> h2;
	cout << h2(c1) << " " << h2(c2) << endl;
	const char * p1{ "This is good!" };
	const char* p2{ "This is good!" };
	cout << p1 << " " << p2 << endl;
	hash<const char*> h3;
	cout << h3(p1) << " " << h3(p2) << endl;
	string s1{ "This is good!" };
	string s2{ "This is good!" };
	hash<string> h4;
	cout << h4(s1) << " " << h4(s2) << endl;

	int i{ 5 }, j{ 5 };
	cout << h1(i) << " " << h1(j) << endl;

	int* p3{ new int{5} };
	int* p4{ new int {5} };
	hash<int*> h5;
	cout << h5(p3) << " " << h5(p4) << endl;
	

	vector<int> V1{ 1,2,3,4,5 };
	//hash<vector<int>> h6;

	ThreeD<int> t1{ 1,1,1 }, t2{ 2,2,2 }, t3{ 3,3,3 }, t4{ 4,4,4 }, t5{ 4,5,6 }, t6{ 2,5,12 }, t7{ 6,5,4 }, t8{ 30,1,4 }, t9{ 7,8,9 };
	set<ThreeD<int>, myCompare<int>> S1{ t1, t2, t3, t4, t5, t6, t7, t8, t9 };
	unordered_set<int, hash<int>, equal_to<int>> S2{ 1,2,3,4,5,6,7,8,9,10 };
	unordered_set<ThreeD<int>, my_hash<int>, my_equal_to<int>> S5{ t1, t2, t3, t4,t5, t6, t7, t8, t9 };
	for (auto& i : S5) { cout << i << " "; }
	cout << endl;



}



