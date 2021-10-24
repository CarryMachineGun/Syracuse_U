//HW4 by Yuchen Wang
//SU Net ID: ywang249  SUID: 905508464

//HW4 Due: 11:59pm, Friday October 29
#include <iostream>
#include <memory>
#include <list>

using namespace std;

class node {
public:
	shared_ptr < list<shared_ptr<int>> > Value;
	shared_ptr<node> South;
	weak_ptr<node> East;
	node() {
		Value = make_shared<list<shared_ptr<int>>>();
	}
};


class TwoD {//rectangle
public:
	int Rows;//Number of Rows
	int Cols;//Number of Columns
	shared_ptr<node> head;
	//TwoD(int i, int j);
	TwoD() : Rows{ 0 }, Cols{ 0 } {}
	

	//*********************
	//Implement all the following member functions.
	TwoD(int r, int c);//constructor
	TwoD(const initializer_list<initializer_list<initializer_list<int>>>& I);
	TwoD(const TwoD& T);//copy constructor
	TwoD operator=(const TwoD& T); //copy assignment
	~TwoD();//destructor
	TwoD(TwoD&& T);//move constructor
	TwoD operator=(TwoD&& T);//move assignment
	TwoD Times(int k) const;//Return a TwoD object with all values being k times of those in *this .
	void DeleteR(int r); //Delete row r
	void DeleteC(int c); //Delete column c
};



ostream& operator<<(ostream& str, const list<shared_ptr<int>>& L) {
	//Your code
}


ostream& operator<<(ostream& str, const TwoD&& T) {//Print in olumn-major order
	//Your code
}


ostream& operator<<(ostream& str, const TwoD& T) {//Print in row-major order
//Your code
}



int main() {
	TwoD T1{ { {1,1,1}, {2,2}, {3,3,3}}, {{4,4}, {5,5, 5,5}, {6,6}},
		{{7, 7, 7},{8,8}, {9}}, {{10,10,10,10}, {11,11}, {12,12,12,12,12}} };//4 rows, 3 columns
	cout << T1 << endl;
	TwoD T2(T1);
	cout << T2 << endl;
	T2 = T1.Times(4);
	cout << T2 << endl;
	T1.DeleteR(3);
	cout << T1 << endl;
	cout << move(T1) << endl;
	T2.DeleteC(2);
	cout<< T2<<endl;
	cout << move(T2) << endl;
	return 0;
}