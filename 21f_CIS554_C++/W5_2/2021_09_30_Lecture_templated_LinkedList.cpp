//copy construcotr, move constructor, copy assignment, move assignment, destructor
//initializer_list
#include <iostream>
#include <vector>
#include <list>
#include <string>

using namespace std;

template <class T> class ThreeD {
public:
	T ht;
	T wid;
	T dep;
	ThreeD(T i, T j, T k) : ht{ 2 * i }, wid{ 2 * j }, dep{ 2 * k }{}
	ThreeD() {}
};

template <class T> ostream& operator<<(ostream& str, const ThreeD<T>& t) {
	str << "(" << t.ht << ", " << t.wid << ", " << t.dep << ")";
	return str;
}



template <class T> class node {
public:
	T value;
	node<T>* next;
	node(T i) : value(i), next(nullptr) {}
	node() : next(nullptr) {}
};
template <typename T> class LinkedList {
public:
	node<T>* head;
	LinkedList() : head(nullptr) {}
	LinkedList(const initializer_list<T>& I);//initializer_list
	LinkedList(const LinkedList<T>& L);//copy constructor
	//Will be invoked by sysmtem in three cases:
	//1. When an object is declared and initialized in the same statement
	//2. call by value;  3. return by value

	LinkedList<T> operator=(const LinkedList<T>& L);//operator=; copy assignment
	LinkedList<T> ThreeTimes();
	~LinkedList();//destructor
	LinkedList(LinkedList<T>&& L);//move constructor; Notice that const is removed.
	LinkedList<T> operator=(LinkedList<T>&& L);//move assignment

};

template <class T> LinkedList<T> LinkedList<T>::operator=(LinkedList<T>&& L) {
	while (head) {
		node<T>* p1{ head->next };
		delete head;
		head = p1;
	}
	head = L.head;
	L.head = nullptr;
    cout << &L << endl;
	cout << "Move Assignment" << endl;
	return *this;
}

template <class T> LinkedList<T>::LinkedList(LinkedList<T>&& L) {//Will be invoked in the same three condition, when Rvalue is used.
	head = L.head;
	L.head = nullptr;

	cout << "Move Constructor" << endl;

}

template <class T> LinkedList<T>::~LinkedList() {//Destructor
	while (head) {
		node<T>* p{ head->next };
		delete head;
		head = p;
	}
	cout << "Destructor" << endl;
}

template <class T> LinkedList<T> LinkedList<T>::ThreeTimes() {
	LinkedList<T> temp{ *this };
	node<T>* p{ temp.head };
	while (p) {
		p->value *= 3;
		p = p->next;
	}

	cout << "ThreeTimes, and temp is :" << &temp <<endl;
	// return *this;//visual studio compiler will change it to return move(temp); 
	return temp;//visual studio compiler will change it to return move(temp); 
}


template <class T> LinkedList<T> LinkedList<T>::operator=(const LinkedList<T>& L) {//operator=; copy assignment
	cout << &L << endl;
	while (head) {
		node<T>* p1{ head->next };
		delete head;
		head = p1;
	}

	node<T>* p1{ L.head };
	while (p1) {
		node<T>* p2{ new node<T>{} };
		p2->next = head;
		head = p2;
		p1 = p1->next;
	}
	p1 = L.head;
	node<T>* p2 = head;
	while (p1) {
		p2->value = p1->value;
		p1 = p1->next;
		p2 = p2->next;
	}

	cout << "Copy Assignment" << endl;
	return *this;
}


template <class T>LinkedList<T>::LinkedList(const LinkedList<T>& L) :LinkedList() {//copy constructor
	node<T>* p1{ L.head };
	while (p1) {
		node<T>* p2{ new node<T>() };
		p2->next = head;
		head = p2;
		p1 = p1->next;
	}
	p1 = L.head;
	node<T>* p2 = head;
	while (p1) {
		p2->value = p1->value;
		p1 = p1->next;
		p2 = p2->next;
	}
	cout << "Copy Constructor" << endl;
}



template <class T> LinkedList<T>::LinkedList(const initializer_list<T>& I) {//initializer_list
	head = nullptr;
	auto it{ I.end() - 1 };
	while (it != I.begin() - 1) {
		node<T>* p{ new node<T>(*it) };
		p->next = head;
		head = p;
		--it;
	}
	cout << "Initializer List" << endl;
}


template <class T> ostream& operator<<(ostream& str, const LinkedList<T>& L) {
	str << "{ ";
	node<T>* p{ L.head };
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
	LinkedList<int> L1{ 1,2,3, 4, 5 };//initialilizer_list

	LinkedList<int> L2{ L1 }; //will use default copy constructor if copy constructor is not defined
	//LinkedList L2 = L1;

	LinkedList<int> L3;//deault operator assignment if no operator= defined
	cout << &L1 << endl;
	L3 = L1;
	cout << L1 << endl;
	cout << L2 << endl;
	cout << L3 << endl;
	cout << L1.head << "  " << L2.head << "   " << L3.head << endl;

	//为什么在我将treeTime返回的值设为L1而不是temp后，用的不是copy assignment，而是在hidden copy之后用的move assugnment
	L3 = L1.ThreeTimes();//L3.operator=(L1.ThreeTimes());//L1.ThrreTimes() is Rvalue
	cout << L3 << endl;



	L1 = L2 = L3;//L1.operator=(L2.operator=(L3));

	LinkedList<ThreeD<int>> L5{ {1,2,3}, {1,1,1}, {2,2,2} };
	cout << L5 << endl;




	//int i{ 25 };
	//f1(i);//i Lvalue
	//cout << i << endl;
	//f1(25);//25 Rvalue
	//f1(i - 1);//i-1 Rvalue
	//f1(move(i)); //change i to Rvalue



	//int& i{ f2() };//Used to be error, but now the C++ does not complain anymore.
	//cout << i << endl;



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