//copy construcotr, move constructor, copy assignment, move assignment, destructor
//initializer_list
#include <iostream>
#include <vector>
#include <list>
#include <string>

using namespace std;




class node {
public:
	int value;
	node* next;
	node(int i): value(i), next (nullptr){}
	node(): next(nullptr){}
};
class LinkedList {
public:
	node* head;
	LinkedList(): head(nullptr){}
	LinkedList(const initializer_list<int>& I);//initializer_list
	LinkedList(const LinkedList& L);//copy constructor
	//Will be invoked by sysmtem in three cases:
	//1. When an object is declared and initialized in the same statement
	//2. call by value;  3. return by value

	void operator=(const LinkedList& L);//operator=
	LinkedList ThreeTimes();
	~LinkedList();//destructor

};

LinkedList::~LinkedList() {//Destructor
	while (head) {
		node* p{ head->next };
		delete head;
		head = p;
	}
	cout << "Destructor" << endl;
}

LinkedList LinkedList::ThreeTimes() {
	LinkedList temp{ *this };
	node* p{ temp.head };
	while (p) {
		p->value *= 3;
		p = p->next;
	}

	cout << "ThreeTimes" << endl;
	return temp;
}


void LinkedList::operator=(const LinkedList& L) {//operator=; copy assignment
	while (head) {
		node* p1{ head->next };
		delete head;
		head = p1;
	}

	node* p1{ L.head };
	while (p1) {
		node* p2{ new node() };
		p2->next = head;
		head = p2;
		p1 = p1->next;
	}
	p1 = L.head;
	node* p2 = head;
	while (p1) {
		p2->value = p1->value;
		p1 = p1->next;
		p2 = p2->next;
	}

	cout << "Copy Assignment" << endl;
}


LinkedList::LinkedList(const LinkedList& L):LinkedList() {//copy constructor
	node* p1{ L.head };
	while (p1) {
		node* p2{ new node() };
		p2->next = head;
		head = p2;
		p1 = p1->next;
	}
	p1 = L.head;
	node* p2 = head;
	while (p1) {
		p2->value = p1->value;
		p1 = p1->next;
		p2 = p2->next;
	}
	cout << "Copy Constructor" << endl;
}



LinkedList::LinkedList(const initializer_list<int>& I) {//initializer_list
	auto it{ I.end() - 1 };
	while (it != I.begin() - 1) {
		node* p{ new node(*it) };
		p->next = head;
		head = p;
		--it;
	}
	cout << "Initializer List" << endl;
}


ostream& operator<<(ostream& str, const LinkedList& L) {
	str << "{ ";
	node* p{ L.head };
	while (p) {
		str << p->value << " ";
		p = p->next;
	}
	str << "}";
	return str;
}





int main() {
	LinkedList L1{ 1,2,3, 4, 5 };//initialilizer_list

	LinkedList L2{ L1 }; //will use default copy constructor if copy constructor is not defined
	//LinkedList L2 = L1;

	LinkedList L3;//deault operator assignment if no operator= defined
	L3 = L1;
	cout << L1 << endl;
	cout << L2 << endl;
	cout << L3 << endl;
	cout << L1.head << "  " << L2.head << "   " << L3.head << endl;

	L3 = L1.ThreeTimes();
	cout << L3 << endl;


	return 0;
}