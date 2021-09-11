#include <iostream>

using namespace std;

class test{
public:
	int val;

	test(){
		val = 0;
	}

	test(int i){
		val = i;
	}
};

class node {
public:
	int value;

    //@Yuchen_Qst: why next can not be setted as 'node next'? A: Because it will created a self-nested attribute 
	//casuing a infinite loop. Becasue next can not be initilized 
	node* next;

	//@Yuchen: This is allowed because no initlized looped is created
	test foo;
	
    node(int i){ 
        value = i; next = nullptr; 
        }//NULL is out of date
	
    node() {
        next = nullptr;
		// foo = {1};
		foo = test(1);
        }
};

class LinkedList {
public:

	//@Yuchen_Qst: Can head here be a object not a pointer?
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
		    //@Yuchen_Qst: Does using the line below to create the nodes fails because 'newNode' will be delete when function complete?
			// node newNode(rand() % m);
			// node* p1 = &newNode;

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

	//@Yuchen: 
	
	// node head;

	// LinkedList() { head = node(); }

	// LinkedList(int A[], int size) {
	// 	for (int i = size - 1; i >= 0; --i) {
	// 		node p1 = node(A[i]) ;
	// 		p1.next = &head;
	// 		head = p1;
	// 	}
	// }


	// void makeList(int n, int m) {//create an n-node LinkedList with random value in 0 ...m-1
	// 	for (int i = 0; i < n; ++i) {
	// 		node p1 = node(rand() % m);//rand() return a random integer
	// 		p1.next = &head;
	// 		head = p1;
	// 	}
	// }


	// void print() {
	// 	node p1 = head ;
		
	// 	while (&p1) {
	// 		cout << p1.next << " ";
	// 		p1 = *(p1.next);
	// 	}
	// 	cout << endl;

	// }

};


int main() {

	LinkedList L1;
	L1.makeList(10, 20);
	L1.print();

	// int C[7] = { 1,2,3,4,5,6,7 };
	// LinkedList L2 = LinkedList( C, 7 );
	// L2.print();

	return 0;
}