
//initializer_list
#include <iostream>
#include <vector>
#include <list>
#include <string>

using namespace std;

class ThreeD {
public:
	int ht;
	int wid;
	int dep;
	ThreeD(int i, int j, int k): ht(2*i), wid(2*j), dep(2*k){}
	ThreeD(){}
	ThreeD(const initializer_list<int>& I);
};
ThreeD::ThreeD(const initializer_list<int>& I) {
	auto it{ I.begin() };
	ht = *it * 3;
	++it;
	wid = *it * 3;
	++it;
	dep = *it * 3;
}

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
	LinkedList(const initializer_list<int>& I);

};

LinkedList::LinkedList(const initializer_list<int>& I) {
	auto it{ I.end() - 1 };
	while (it != I.begin() - 1) {
		node* p{ new node(*it) };
		p->next = head;
		head = p;
		--it;
	}
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


ostream& operator<<(ostream& str, const ThreeD& t) {
	str << "(" << t.ht << ", " << t.wid << ", " << t.dep << ")";
	return str;
}





int main() {
	ThreeD t1 { 1,2,3 };//agregate initialization
	cout << t1 << endl;
	//initializer_list > constructor > agregate
	ThreeD t2(10, 20, 30);//will invoke constrctor
	cout << t2 << endl;

	LinkedList L1{ 1,2,3,4,5 };
	cout << L1 << endl;



	return 0;
}