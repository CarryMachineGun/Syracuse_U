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
	
	LinkedList operator=(const LinkedList& L);//operator=; copy assignment
	LinkedList ThreeTimes();
	~LinkedList();//destructor
	LinkedList(LinkedList&& L);//move constructor; Notice that const is removed.
	LinkedList operator=(LinkedList&& L);//move assignment

};

LinkedList LinkedList::operator=(LinkedList&& L) {
	while (head) {
		node* p1{ head->next };
		delete head;
		head = p1;
	}
	head = L.head;
	L.head = nullptr;
	cout << "Move Assignment Tree" << endl;
	return *this;
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
	return *this;
}
LinkedList::LinkedList(LinkedList&& L) {//Will be invoked in the same three condition, when Rvalue is used.
	head = L.head;
	L.head = nullptr;

	cout << "Move Constructor" << endl;

}

LinkedList::~LinkedList() {//Destructor
	while (head) {
		node* p{ head->next };
		delete head;
		head = p;
	}
	cout << "Destructor" << endl;
}

LinkedList LinkedList::ThreeTimes() {
	//QS: Why here is copy constructor?
	LinkedList temp{ *this };
	node* p{ temp.head };
	while (p) {
		p->value *= 3;
		p = p->next;
	}

	cout << "ThreeTimes" << endl;
	return move(temp);//visual studio compiler will change it to return move(temp); 
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

void f1(int& i) {
	cout << "Lvalue f1" << endl;
	++i;
}
void f1(int&& i) {
	cout << "Rvalue f1" << endl;
	++i;
}


int& f2() {
	int k{ 200 };
	return k;

}

int main() {
	LinkedList L1{ 1,2,3, 4, 5 };//initialilizer_list

	LinkedList L2{ L1 }; //will use default copy constructor if copy constructor is not defined
	// //LinkedList L2 = L1;

	LinkedList L3;//deault operator assignment if no operator= defined
	// L3 = L1;
	// cout << L1 << endl;
	// cout << L2 << endl;
	// cout << L3 << endl;
	// cout << L1.head << "  " << L2.head << "   " << L3.head << endl;

	cout << " --------------------------------- " << endl;

	L3 = L1.ThreeTimes();//L3.operator=(L1.ThreeTimes());//L1.ThrreTimes() is Rvalue
	cout << L3 << endl;



	// L1 = L2 = L3;//L1.operator=(L2.operator=(L3));


	//int i{ 25 };
	//f1(i);//i Lvalue
	//cout << i << endl;
	//f1(25);//25 Rvalue
	//f1(i - 1);//i-1 Rvalue
	//f1(move(i)); //change i to Rvalue



	// int& i{ f2() };//Used to be error, but now the C++ does not complain anymore.
	// cout << i << endl;
	return 0;
}

/*
Lvalue:  "Anything" that can be placed on the left hand side of an assignment is an Lvalue.
Rvalue: "Anything" that can only be placed on the right hand side of an assignment is an Rvalue.

i = 10;  //i is Lvalue; 10 is Rvalue
int k {25};
i = sqrt(k); //sqrt(k) is Rvalue
A[2] = k; //A[2] if Lvalue

//if your class contains any deep structure (thrught pointers), you need to do deep processing
class myClass{
public:

vector<list<ThreeD>>> V1;
int * p;//need deep processing
vector<int *> V2;//need deep processing

}


*/