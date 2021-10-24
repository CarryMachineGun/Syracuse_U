#include <iostream>//cout , cin
#include <memory>
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
	//node* next;
	shared_ptr<node> next;
	node(int i) { value = i; }//NULL is out of date
	node() {  }

};

class LinkedList {
public:
	//node* head;
	shared_ptr<node> head;
	LinkedList() {}

	LinkedList(int A[], int size);

	void makeList(int n, int m);

	void print();

	void reverse();//funciton prototype

	void removeOne(int k); //remove the first node with value k

	void sort();//selection sort

};

void LinkedList::sort() {
	if (!head || !head->next) return;//0 or 1 node
	//node* p1{ head };
	shared_ptr<node> p1{ head };
	while (p1) {
		//node* p2{ p1->next };
		shared_ptr<node> p2{ p1->next };
		int min{ p1->value };
		//node* p_min{ p1 };
		shared_ptr<node> p_min{p1};
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
	if (head->value == k) { head = head->next; return; }
	//node* p1{ head }, * p2{ head->next };
	shared_ptr<node> p1{ head }, p2{ head->next };
	while (p2) {
		if (p2->value == k) {
			p1->next = p2->next;
			//delete p2;
			return;
		}
		p1 = p2;
		p2 = p2->next;
	}
}


void LinkedList::reverse() {
	if (!head || !head->next) return;//0 or 1 node
	//node* p1{ head }, * p2{ head->next };
	shared_ptr<node> p1{ head }, p2{ head->next }, p3;
	while (p2) {//while (p2 != nullptr)
		//node* p3{ p2->next };
		p3 = p2->next;
		p2->next = p1;
		if (p1 == head) { p1->next = nullptr; }
		p1 = p2;
		p2 = p3;
	}
	head = p1;
}



void LinkedList::print() {
	//node* p1{ head };
	shared_ptr<node> p1{ head };

	while (p1) {
		cout << p1->value << " ";
		p1 = p1->next;
	}
	cout << endl;

}

LinkedList::LinkedList(int A[], int size) {
	for (int i = size - 1; i >= 0; --i) {
		//node* p1{ new node {A[i]} };
		// shared_ptr<node> p1{ new node(A[i]) };
		shared_ptr<node> p1{ make_shared<node>(A[i])};
		p1->next = head;
		head = p1;
	}
}

void LinkedList::makeList(int n, int m) {//create an n-node LinkedList with random value in 0 ...m-1
	for (int i = 0; i < n; ++i) {
		//node* p1{ new node {rand() % m} };//rand() return a random integer
		shared_ptr<node> p1{ new node{ rand() % m } };
		p1->next = head;
		head = p1;
	}
}

int main() {
	

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