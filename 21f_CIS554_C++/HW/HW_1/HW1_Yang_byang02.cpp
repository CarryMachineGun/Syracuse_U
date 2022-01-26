//Due:  11:59pm, Tuesday, Sept. 14
#include <iostream>
using namespace std;

class Node {
public:
	int value;
	Node* next;
	Node* previous;
	Node(int i) { value = i; next = previous = nullptr; }
	Node() { next = previous = nullptr; }//default constructor
};

class DoublyLinkedList {
public:
	Node* head;
	Node* tail;
	DoublyLinkedList() { head = tail = nullptr; }
	void makeList(int n, int m);//create an n-node linked list with random values in 0 ... m-1
	void print_F();
	void print_B();
	void bubbleSort();
	//2 3 1 6 8 5 9 6 2 5 7 7 4 2 becomes
	//1 2 2 2 3 4 5 5 6 6 7 7 8 9 

	//In case multiple nodes have the same min value, the
	//first of them will be swapped with the node pointed by head.
	//In case multiple nodes have the same max value, the
	//last of them will be swapped with the node pointed by tail.
	//For example,    6 5 3 7 3 7 5 4 will become 3 5 6 7 3 4 5 7





	//You only can modify next and previous of nodes, but not value of nodes.
	//You are required to directly work on the linked list.

	//You are not allowed to use any external structures such as arrays
	// to perform operations and copy the results back to the linked list.

	//You are not allowed to create additional functions.
	//You can use while loop, but not for loop.



	void minMax();//swap the node of min value with the first node; 
	//swap the node of max value with the last node

	// 14 5 6 2 17 9 8
	// 2 5 6 14 8 9 17

	//In case multiple nodes have the same min value, the
	//first of them will be swapped with the node pointed by head.
	//In case multiple nodes have the same max value, the
	//last of them will be swapped with the node pointed by tail.
	//For example,    6 5 3 7 3 7 5 4 will become 3 5 6 7 3 4 5 7

	//Similar constraints apply as repeatedly stated below.
	//You only can modify next and previous of nodes, but not value of nodes.
	//You are required to directly work on the linked list.

	//You are not allowed to use any external structures such as arrays
	// to perform operations and copy the results back to the linked list.

	//You are not allowed to create additional functions.
	//You can use while loop, but not for loop.


};

void DoublyLinkedList::minMax() {

	//Your code
	Node* p1{ head };
	Node* p2{ head->next };
	Node* pmin{ p1 };
	Node* pmax{ p1 };
	Node* p3{ tail};

	while (p2) {
		if (p2->value < pmin->value) {
			pmin = p2;
		}
		if (p2->value >= pmax->value) {
			pmax = p2;
		}
		p2 = p2->next;
	}
	if (pmin == tail) {
		p1->next->previous = pmin;
		pmin->previous->next = p1;
		head = pmin;
		tail = p1;
		pmin->next = p1->next;
		p1->next = NULL;
		p1->previous = pmin->previous;
		pmin->previous = NULL;
	}
	else if (pmin == head) {
		return;
	}
	else
	{
		p1->next->previous = pmin;
		pmin->next->previous = p1;
		pmin->previous->next = p1;
		head = pmin;
		Node* q{ pmin->next };
		pmin->next = p1->next;
		p1->next = q;
		Node* q3{ pmin->previous };
		pmin->previous = p1->previous;
		p1->previous = q3;
	}

	if (pmax == head) {
		pmax->next->previous = p3;
		p3->previous->next = pmax;
		head = p3;
		tail = pmax;
		p3->next = pmax->next;
		pmax->next = NULL;
		pmax->previous = p3->previous;
		p3->previous = NULL;
	}
	else if (pmax == tail) {
		return;
	}

	else {
		p3 = tail;
		pmax->next->previous = p3;
		tail = pmax;
		pmax->previous->next = p3;
		p3->previous->next = pmax;
		Node* q1{ pmax->next };
		pmax->next = p3->next;
		p3->next = q1;
		Node* q2{ pmax->previous };
		pmax->previous = p3->previous;
		p3->previous = q2;
	}
	

	/*pmin->value = p1->value;
	p1->value = min;
	pmax->value = p3->value;
	p3->value = max;*/


}

void DoublyLinkedList::bubbleSort() {

	//Your code
	Node* p{ head };
	Node* q{ head };
	Node* end{ nullptr };
	Node* pre{ p };
	while (head != end) {
		while (p != end and p->next != NULL) {
			if (p->value > p->next->value) {
				if (p == head) {
					p = p->next;
					head = p;
					q->next = p->next;
					head->next = q;
					p->next = q;
					p->previous = q->previous;
					q->previous = p;
					q->next->previous = q;
				}
				else {
					q->next = p->next;
					q = q->next;
					p->next = q->next;
					q->next = p;
					q->previous = p->previous;
					p->previous = q;
					if (p->next != nullptr) {
						p->next->previous = p;
					}
					p = q;
				}
			}
			q = p;
			p = p->next;
		}
		end = q;
		p = q = head;

	}
	while (p->next != NULL) {
		p = p->next;
	}
	tail = p;
	p = head;

}


void DoublyLinkedList::makeList(int n, int m) {
	for (int i = 0; i < n; ++i) {
		Node* p1{ new Node{rand() % m} };
		if (!head) { head = tail = p1; }//currently empty linked list
		else {
			tail->next = p1;
			p1->previous = tail;
			tail = p1;
		}
	}
}
void DoublyLinkedList::print_F() {
	Node* p1{ head };
	while (p1) {
		cout << p1->value << " ";
		p1 = p1->next;
	}
	cout << endl;
}
void DoublyLinkedList::print_B() {
	Node* p1{ tail };
	while (p1) {
		cout << p1->value << " ";
		p1 = p1->previous;
	}
	cout << endl;
}

int main() {
	DoublyLinkedList L1;
	L1.makeList(19, 15);
	L1.print_F();
	L1.print_B();
	L1.minMax();
	L1.print_F();
	L1.print_B();

	DoublyLinkedList L2;
	L2.makeList(25, 30);
	L2.bubbleSort();
	L2.print_F();
	L2.print_B();
	return 0;
}