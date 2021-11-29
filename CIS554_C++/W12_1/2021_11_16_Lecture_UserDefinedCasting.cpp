#include <iostream>
#include <string>
using namespace std;

class ThreeD {
public:
	int ht;
	int wid;
	int dep;
	ThreeD() { ht = wid = dep = 0; }
	ThreeD(int i, int j, int k) { ht = i; wid = j; dep = k; }
	
	operator int() { return ht + wid + dep; } //Casting from ThreeD to int
	//implicit and explicit castings are both allowed

	explicit operator string() { return "ThreeD: ht, wid, dep"; }
	//Casting from ThreeD to string
	//With the keyword explicit, only explicit casting is allowed.
	//Implicit casting will cause errors.

};

int main() {

	ThreeD t1{ 3,4,5 };
	int m = t1; //implicit type casting is allowed
	cout << m << endl; //Will print 12
	cout << static_cast<int>(t1) << endl; //Explicit casting is allowed. Will print 12
	//string s1 = t1; Error. Implicit casting is not allowed
	cout << static_cast<string>(t1) << endl; //explicit casting is allowed
	//Will print ThreeD: ht, wid, dep
	return 0;
}