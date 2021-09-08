#include <iostream>//cout , cin
using namespace std;


//Making class---------------------------------
// struct
class ThreeD {
//@Yuchen: Class' members are private by default. Struct's members are public by default.`  
public:
	int ht; 
	int wid;
	int dep;

	int vol() { return ht * wid * dep; }

};
class ThreeD1 {
public:
	int ht;
	int wid;
	int dep;


	ThreeD1(int i, int j, int k) { ht = 2*i; wid = 3*j; dep = 4*k; }	//constructor

	int vol() { return ht * wid * dep; }

};

int main() {
	//user defined data type

	ThreeD t1;
	t1.ht = 10;
	t1.wid = 20; 
	t1.dep = 30;

	ThreeD t2{10,20,30};//aggregate initialization`
	ThreeD1 t3 {1,2,3};//will call constructor ht = 2, wid = 6, dep = 12

    cout<< t3.vol() << endl;

    //@Yuchen: we use 'new' here because p4 is a pointer, so we need to apply it a pointer
	ThreeD* p4 = new ThreeD{1,2,3} ;

    // ThreeD j{1,2,3};
    // ThreeD* p4 = &j;


	cout << (*p4).ht << " " << (*p4).wid << " " << (*p4).dep << endl;//1 2 3
	cout << p4->ht << " " << p4->wid << " " << p4->dep << endl;//1 2 3  -> my pronounciation "select"

    delete p4;
    // delete p4;

	return 0;
}