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

	LinkedList operator=(const LinkedList& L);//operator=
	LinkedList ThreeTimes();
	~LinkedList();//destructor
};
	
// ostream& operator<<(ostream& str, const LinkedList& L);

LinkedList::~LinkedList() {//Destructor
	cout << "Destructor and address is" << this << endl;
	while (head) {
		node* p{ head };
		head = head->next;
		delete p;
	}
}


//@Yuchen_Qst: Why temp is static allocated but can also be returned to outside of the function?  even after destructing?
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


LinkedList LinkedList::operator=(const LinkedList& L) {//operator=; copy assignment
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
	return L;
}

//Deep copy
LinkedList::LinkedList(const LinkedList& L) {//copy constructor
	head=nullptr;
	// cout << "In CC " << (head == nullptr) << endl;

	node* p1{ L.head };
	//@Yuchen: make the current LinkedList as same length as L
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



	cout << "Copy Constructor, and address is " << this << endl;
}


//@Yuchen_Qst: Why the constructor below dones't need to set head(at the end of the function will be the tail) to nullptr?
LinkedList::LinkedList(const initializer_list<int>& I) {//initializer_list
	// cout << "In IC " << (head == nullptr) << endl;
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
	// L3.operator=(L1);
	// // L3 = L1;

	// cout << L3 << " " << &L1 << endl;
	// cout << L1 << endl;
	// cout << L2 << endl;
	// cout << L3 << endl;
	// cout << L1.head << "  " << L2.head << "   " << L3.head << endl;

	cout << " --------------------------------- " << endl;
	L3 = L1.ThreeTimes();
	cout << L1 << endl;
	cout << L3 << endl;


	return 0;
}

// ostream& operator<<(ostream str, const LinkedList& list){

// }