#include <iostream>//cout , cin
using namespace std;

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


	ThreeD1(int i, int j, int k) { ht = 2 * i; wid = 3 * j; dep = 4 * k; }	//constructor

	int vol() { return ht * wid * dep; }

};

class node {
public:
	int value;
	node* next;
	node(int i) { value = i; next = nullptr; }//NULL is out of date
	node() { next = nullptr; }
};

class LinkedList {
public:
	node* head;
	LinkedList() { head = nullptr; }

	LinkedList(int A[], int size);

	void makeList(int n, int m);

	void print();

	void reverse();//funciton prototype

	void removeOne(int k); //remove the first node with value k

	void sort();//selection sort

};

void LinkedList::sort() {
	if (!head || !head->next) return;//0 or 1 node
	node* p1{ head };
	while (p1) {
		node* p2{ p1->next };
		int min{ p1->value };
		node* p_min{ p1 };
		while (p2) {
			if (p2->value < min) { min = p2->value; p_min = p2; }
			p2 = p2->next;
		}
		p_min->value = p1->value;
		p1->value = min;
		p1 = p1->next;
	}
}

void LinkedList::removeOne(int k) {
	if (!head) return; //empty linked list
	if (head->value == k) { node* p1{ head->next }; delete head; head = p1; return; }
	node* p1{ head }, * p2{ head->next };
	while (p2) {
		if (p2->value == k) {
			p1->next = p2->next;
			delete p2;
			return;
		}
		p1 = p2;
		p2 = p2->next;
	}
}


void LinkedList::reverse() {
	if (!head || !head->next) return;//0 or 1 node
	node* p1{ head }, * p2{ head->next };
	while (p2) {//while (p2 != nullptr)
		node* p3{ p2->next };
		p2->next = p1;
		if (p1 == head) { p1->next = nullptr; }
		p1 = p2;
		p2 = p3;
	}
	head = p1;
}



void LinkedList::print() {
	node* p1{ head };

	while (p1) {
		cout << p1->value << " ";
		p1 = p1->next;
	}
	cout << endl;

}

LinkedList::LinkedList(int A[], int size) {
	for (int i = size - 1; i >= 0; --i) {
		node* p1{ new node {A[i]} };
		p1->next = head;
		head = p1;
	}
}

void LinkedList::makeList(int n, int m) {//create an n-node LinkedList with random value in 0 ...m-1
	for (int i = 0; i < n; ++i) {
		node* p1{ new node {rand() % m} };//rand() return a random integer
		p1->next = head;
		head = p1;
	}
}

void f1(int j) { j++; }//call/pass by value
//A new copy of the object is created and used inside the function.
//Any change on this new object will not affect the original object  outside this function.


void f2(int& j) { j++; }//call/pass by reference(
//The same object outside the funciton is directly used inside the funcion.
//Any change on the object inside the function will acutally change the original object.

void f3(int A[], int size) {
	//compiler will change the aboe into void f3(int * A, int size){
	for (int i = 0; i < size; i++) { A[i]++; }
}
void f4(int* p) {//p is pass by value.
	*p = 55;
	cout << p << " " << *p << endl;
	p++;//will not affect the original pointer outside the function

}


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
	int C[7]{ 1,2,3,4,5,6,7 };
	LinkedList L2{ C, 7 };
	L2.print();


	LinkedList L1;
	L1.makeList(10, 20);
	L1.print();
	L1.reverse();
	L1.print();
	L1.removeOne(14);
	L1.print();
	L1.sort();
	L1.print();


	return 0;
}