#include <iostream>//cout , cin
using namespace std;


//Making class---------------------------------
class ThreeD {
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



// LinkedList-------------------------------------
class node {
public:
	int value;
	node* next;
	node(int i) { value = i; next = nullptr; }//NULL is out of date
	node() { next = nullptr;}
};

class LinkedList {
public:
	node* head;
	LinkedList() { head = nullptr; }

	LinkedList(int A[], int size) {
		for (int i = size - 1; i >= 0; --i) {
			node* p1{ new node {A[i]} };
			p1->next = head;
			head = p1;
		}
	}


	void makeList(int n, int m) {//create an n-node LinkedList with random value in 0 ...m-1
		for (int i = 0; i < n; ++i) {
			node* p1{ new node {rand() % m} };//rand() return a random integer
			p1->next = head;
			head = p1;
		}
	}


	void print() {
		node* p1{ head };
		
		while (p1) {
			cout << p1->value << " ";
			p1 = p1->next;
		}
		cout << endl;

	}

};


// 
void f1(int j) { j++; }//call/pass by value
//A new copy of the object is created and used inside the function.
//Any change on this new object will not affect the original object  outside this function.


void f2(int &j) { j++; }//call/pass by reference(
//The same object outside the funciton is directly used inside the funcion.
//Any change on the object inside the function will acutally change the original object.

void f3(int A[], int size){
	//compiler will change the aboe into void f3(int * A, int size){
	for (int i = 0; i < size; i++) { A[i]++; }
}
void f4(int* p) {//p is pass by value.
	*p = 55;
	cout << p << " " << *p << endl;
	p++;//will not affect the original pointer outside the function

}



// Dynamic memory allocation
int main() {
	int k;//static allocaiton
	//cout << k << endl; Error!

	//Dynamic memory management

	int* p1{ new int {5} };//the operator new requests the system for a storage space and
	//returns the address of the storage sapce

	cout << p1 << " " << *p1 << endl;
	delete p1;//return object (and its space) pointed by p1 to system
	//delete p1; error!
	//cout << *p1 << endl;  Error!
	//k = 100;
	//p1 = &k;

	//delete p1;  only can delete dynamic object; k is a static object.

	p1 = new int[5]{ 1,2,3,4,5 };
	//Creates a dynamic array and retruns the address of the first element.
	for (int i = 0; i < 5; ++i) { cout << p1[i] << " "; }
	cout << endl;
	delete[] p1;//delete the dynamic array pointed by p1

	int A[6]{ 1,2,3,4,5,6 };
	for (int i : A) { cout << i << " "; }//p1 will not work for now.
	cout << endl;
	k = 10;
	//int AA[k];  array size has to be a constant
	
	p1 = new int[k];//no error.
	delete[] p1;

	//call/pass by value and call/pass by reference

	int i{ 1 };
	f1(i);
	cout << i << endl;//1
	f2(i);
	cout << i << endl; //2

	int B[4]{ 1,2,3,4 };
	f3(B, 4);
	for (int i : B) { cout << i << " "; }//2 3 4 5
	cout << endl;
	int* p2{ new int {50} };
	cout << p2 << " " << *p2 << endl;
	f4(p2);
	cout << p2 << " " << *p2 << endl;


	//user defined data type

	ThreeD t1;
	t1.ht = 10;
	t1.wid = 20; 
	t1.dep = 30;

	ThreeD t2{ 10,20,30 };//aggregate initialization
	ThreeD1 t3{ 1,2,3 };//will call constructor ht = 2, wid = 6, dep = 12

	ThreeD* p4{ new ThreeD{1,2,3} };
	cout << (*p4).ht << " " << (*p4).wid << " " << (*p4).dep << endl;//1 2 3
	cout << p4->ht << " " << p4->wid << " " << p4->dep << endl;//1 2 3  -> my pronounciation "select"

	LinkedList L1;
	L1.makeList(10, 20);
	L1.print();

	int C[7]{ 1,2,3,4,5,6,7 };
	LinkedList L2{ C, 7 };
	L2.print();




	return 0;
}