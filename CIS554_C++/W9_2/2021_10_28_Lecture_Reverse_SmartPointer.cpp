//Due:  11:59pm, Tuesday, Sept. 14
#include <iostream>
#include <memory>
using namespace std;

class Node {
public:
	int value;
	//Node* next;
	shared_ptr<Node> next;
	//Node* previous;
	weak_ptr<Node> previous;
	Node(int i) { value = i;  }
	Node() { }//default constructor
};

class DoublyLinkedList {
public:
	//Node* head;
	shared_ptr<Node> head;
	//Node* tail;
	shared_ptr<Node> tail;
	DoublyLinkedList() {  }
	void makeList(int n, int m);//create an n-node linked list with random values in 0 ... m-1
	void print_F();
	void print_B();
	void reverse();

};

void DoublyLinkedList::reverse() {
	if (!head || !head->next) return;
	//Node* p1{ head }, * p2;
	shared_ptr<Node> p1{ head }, p2, p3;
	while (p1) {
		p2 = p1->next;
		p1->next = p1->previous.lock();
		p1->previous = p2;
		p3 = p1;
		p1 = p2;
	}
	swap(head, tail);
}


void DoublyLinkedList::makeList(int n, int m) {
	for (int i = 0; i < n; ++i) {
		//Node* p1{ new Node{rand() % m} };
		shared_ptr<Node> p1{ make_shared<Node>(rand() % m) };
		if (!head) { head = tail = p1; }//currently empty linked list
		else {
			tail->next = p1;
			p1->previous = tail;
			tail = p1;
		}
	}
}
void DoublyLinkedList::print_F() {
	//Node* p1{ head };
	shared_ptr<Node> p1{ head };
	while (p1) {
		cout << p1->value << " ";
		p1 = p1->next;
	}
	cout << endl;
}
void DoublyLinkedList::print_B() {
	//Node* p1{ tail };
	shared_ptr<Node> p1{ tail };
	while (p1) {
		cout << p1->value << " ";
		p1 = p1->previous.lock();
	}
	cout << endl;
}

int main() {
	DoublyLinkedList L1;
	L1.makeList(19, 15);
	L1.print_F();
	L1.print_B();
	L1.reverse();
	L1.print_F();
	L1.print_B();
	return 0;
}