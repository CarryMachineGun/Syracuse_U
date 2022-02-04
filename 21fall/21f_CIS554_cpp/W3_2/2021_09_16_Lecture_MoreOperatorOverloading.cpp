
//Operator overloading
#include <iostream>
#include <map>
#include <set>
#include <string>
using namespace std;

class ThreeD {
public:
	int ht;
	int wid;
	int dep;
	ThreeD(int i, int j, int k) { ht = 2 * i; wid = 2 * j; dep = 2 * k; }
	//ThreeD(int i, int j, int k): ht(2*i), wid(2*j), dep(2*k){};  the same
	ThreeD() { ht = wid = dep = 0; }//default constructor
	ThreeD operator+(const ThreeD& t) const;
	int & operator[](int k);//return by reference; return the object rather than the value of the object
	ThreeD operator++();//prefix
	ThreeD operator++(int NeverUsed);//postfix
	int vol() const { return ht * wid * dep; }
	bool operator<(const ThreeD& t) const;
};
bool ThreeD::operator<(const ThreeD& t) const{
	return vol() < t.vol();
}
ThreeD ThreeD::operator++(int NeverUsed) {//;//postfix
	ThreeD temp = *this;
	ht++;
	wid++;
	dep++;
	return temp;
}
ThreeD ThreeD::operator++() {
	++ht;
	++wid;
	++dep;
	return *this;//this is a pointer pointing to the current object.
}
int & ThreeD::operator[](int k) {
	switch (k) {
	case 0: return ht;
	case 1: return wid;
	case 2: return dep;
	}

}
ThreeD ThreeD::operator+(const ThreeD& t) const {
	ThreeD temp;
	temp.ht = ht + t.ht;
	temp.wid = wid + t.wid;
	temp.dep = dep + t.dep;
	return temp;
}


ostream& operator<<(ostream& str, const ThreeD& t);
istream& operator>>(istream& str, ThreeD& t);




int main() {

	ThreeD t1{ 2,3,4 }, t3{ 4,5,6 };

	ThreeD t2;//default constructor

	t2 = t1 + t3;
	//compiler will change the above into t2 = t1.operator+(t3);
	cout << t2.ht << " " << t2.wid << "  " << t2.dep << endl;

	cout << t2 << endl;

	cout << t2[1] << endl;//overload operator[]  subscript  will print t2.wid
	t2[1] = 100;//t2.wid = 100;

cout << "************"<< endl;
	cin >> t2;
	cout << t2 << endl;

	

	t3 = ++t2;
	cout << t2 << " " << t3 << endl;

	t3 = t2++;
	cout << t2 << " " << t3 << endl;

	set<int> S1{ 5, 3, 1, 4 };
	for (auto it = S1.begin(); it != S1.end(); ++it) { cout << *it << " "; }
	cout << endl;

	set<ThreeD> S2{ t1, t2, t3 };
	cout << t1 << endl;

	//map<ThreeD, int> M1{ {t1, 2}, {t2, 3} };
	//auto it5{ M1.begin() };
	//cout << it5->first << endl;
	//cout << *(S2.begin()) << endl;
	for (auto &i : S2) { cout << i << " "; }
	cout << endl;
	return 0;
}

istream& operator>>(istream& str, ThreeD& t) {

	str >> t.ht >> t.wid >> t.dep;
	return str;
}

ostream& operator<<(ostream& str, const ThreeD& t) {//read only call by reference for t
	str << "[" << t.ht << ", " << t.wid << ", " << t.dep << "]";
	return str;
}