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
	int vol() const { return ht * wid * dep; }
	bool operator<(const ThreeD<T>& t) const { return vol() < t.vol(); }
};

template <class T> ostream& operator<<(ostream& str, const ThreeD<T>& t) {
	str << "(" << t.ht << ", " << t.wid << ", " << t.dep << ")";
	return str;
}



template <class T> class node {
public:
	T value;
	//node<T>* next;
	shared_ptr<node<T>> next;
	node(T i) : value(i), next(nullptr) {}
	node() : next(nullptr) {}
};
template <typename T> class LinkedList {
public:
	//node<T>* head;
	shared_ptr<node<T>> head;
	//LinkedList() : head(nullptr) {}
	LinkedList() {}
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

	void sort();
	void removeOne(int k);
	void reverse();

};


template <class T> void LinkedList<T>::sort() {
	if (!head || !head->next) return;//0 or 1 node
	//node<T>* p1{ head };
	shared_ptr<node<T>> p1{ head };
	while (p1) {
		//node<T>* p2{ p1->next };
		shared_ptr<node<T>> p2 = p1->next;
		T min =  p1->value;
		//node<T>* p_min{ p1 };
		shared_ptr<node<T>> p_min{ p1 };
		while (p2) {
			if (p2->value < min) { 
				min = p2->value; 
				p_min = p2; 
			}
			p2 = p2->next;
		}
		p_min->value = p1->value;
		p1->value = min;
		p1 = p1->next;
	}
}

template <class T> void LinkedList<T>::removeOne(int k) {
	if (!head) return; //empty linked list
	//if (head->value == k) { node<T>* p1{ head->next }; delete head; head = p1; return; }
		if (head->value == k) {  head = head->next; return; }
	//node<T>* p1{ head }, * p2{ head->next };
		shared_ptr<node<T>> p1{ head }, p2{ head->next };
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


template <typename T> void LinkedList<T>::reverse() {
	if (!head || !head->next) return;//0 or 1 node
	shared_ptr<node<T>> p1{ head }, p2{ head->next };
	shared_ptr<node<T>> p3 = make_shared<node<T>>(); 
	while (p2) {//while (p2 != nullptr)
		// node* p3{ p2->next };
		// shared_ptr<node<T>> p3 = make_shared<node<T>>(p2->next); 
		p3 = p2->next;
		p2->next = p1;
		if (p1 == head) { p1->next = nullptr; }
		p1 = p2;
		p2 = p3;
	}
	head = p1;
}




template <class T> LinkedList<T> LinkedList<T>::operator=(LinkedList<T>&& L) {
	while (head) {
		head = head->next;
	}
	head = L.head;
	L.head = nullptr;
	cout << "Move Assignment" << endl;
	return *this;
}

template <class T> LinkedList<T>::LinkedList(LinkedList<T>&& L) {//Will be invoked in the same three condition, when Rvalue is used.
	head = L.head;
	L.head = nullptr;

	cout << "Move Constructor" << endl;

}

template <class T> LinkedList<T>::~LinkedList() {//Destructor
	head.reset();
	cout << "Destructor" << endl;
}

template <class T> LinkedList<T> LinkedList<T>::ThreeTimes() {
	LinkedList<T> temp{ *this };
	//node<T>* p{ temp.head };
	shared_ptr<node<T>> p{ temp.head };
	while (p) {
		p->value *= 3;
		p = p->next;
	}

	cout << "ThreeTimes" << endl;
	return temp;//visual studio compiler will change it to return move(temp); 
}


template <class T> LinkedList<T> LinkedList<T>::operator=(const LinkedList<T>& L) {//operator=; copy assignment
	head.reset();
	shared_ptr<node<T>> p1{ L.head };
	while (p1) {
		//node<T>* p2{ new node<T>{} };
		shared_ptr<node<T>> p2{ make_shared<node<T>>() };
		p2->next = head;
		head = p2;
		p1 = p1->next;
	}
	p1 = L.head;
	//node<T>* p2 = head;
	shared_ptr<node<T>> p2{ head };
	while (p1) {
		p2->value = p1->value;
		p1 = p1->next;
		p2 = p2->next;
	}

	cout << "Copy Assignment" << endl;
	return *this;
}


template <class T>LinkedList<T>::LinkedList(const LinkedList<T>& L) :LinkedList() {//copy constructor
	//node<T>* p1{ L.head };
	shared_ptr<node<T>> p1{ L.head };
	while (p1) {
		//node<T>* p2{ new node<T>() };
		shared_ptr<node<T>> p2{ make_shared<node<T>>() };
		p2->next = head;
		head = p2;
		p1 = p1->next;
	}
	p1 = L.head;
	//node<T>* p2 = head;
	shared_ptr<node<T>> p2{ head };
	while (p1) {
		p2->value = p1->value;
		p1 = p1->next;
		p2 = p2->next;
	}
	cout << "Copy Constructor" << endl;
}



template <class T> LinkedList<T>::LinkedList(const initializer_list<T>& I) {//initializer_list
	//head = nullptr;
	auto it{ I.end() - 1 };
	while (it != I.begin() - 1) {
		//node<T>* p{ new node<T>(*it) };
		shared_ptr<node<T>> p{ make_shared<node<T>>(*it) };
		p->next = head;
		head = p;
		--it;
	}
	cout << "Initializer List" << endl;
}


template <class T> ostream& operator<<(ostream& str, const LinkedList<T>& L) {
	str << "{ ";
	//node<T>* p{ L.head };
	shared_ptr<node<T>> p{ L.head };
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
	L3 = L1;
	cout << L1 << endl;
	cout << L2 << endl;
	cout << L3 << endl;
	cout << L1.head << "  " << L2.head << "   " << L3.head << endl;


	L3 = L1.ThreeTimes();//L3.operator=(L1.ThreeTimes());//L1.ThrreTimes() is Rvalue
	cout << L3 << endl;



	L1 = L2 = L3;//L1.operator=(L2.operator=(L3));

	LinkedList<ThreeD<int>> L5{ {1,2,3}, {1,1,1}, {2,2,2} };
	cout << L5 << endl;
	L5.sort();
	cout << L5 << endl;

	LinkedList<int> L6{ 6,5,4,3,2,1 };
	L6.removeOne(4);
	cout << L6 << endl;
	L6.reverse();
	cout << L6 << endl;






	return 0;
}