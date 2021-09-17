
//Operator overloading
#include <iostream>
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
	ThreeD operator+(ThreeD& t);
	int & operator[](int k);//return by reference; return the object rather than the value of the object

};
int & ThreeD::operator[](int k) {
	switch (k) {
	case 0: return ht;
	case 1: return wid;
	case 2: return dep;
	}

}
ThreeD ThreeD::operator+(ThreeD& t) {
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

	cin >> t2;
	cout << t2 << endl;

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