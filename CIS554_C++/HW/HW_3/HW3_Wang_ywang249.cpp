//HW3 by Yuchen Wang
//SU Net ID: ywang249  SUID: 905508464

//HW3 Due: 11:59, Friday, Oct. 8
//Note that I removed the member functions print_inO, print_preO, and print_postO for tree class.
//You need to overload operator<< to allow cout for a tree, in which you will implement in-order traversal.
//In additon you need to overload *= for tree and linkedList (see the included main function).


#include <iostream>
using namespace std;

template <class T> class ThreeD {
public:
	T ht;
	T wid;
	T dep;
	ThreeD(T i, T j, T k) :ht(2 * i), wid(2 * j), dep(2 * k) {};
	ThreeD() { ht = wid = dep = 0; }
	void operator*=(int num);
};

template <class T> ostream& operator<<(ostream& str, const ThreeD<T>& t1) {
	str << "(" << t1.ht << ", " << t1.wid << ", " << t1.dep << ")";
	return str;
}

template <class T> void ThreeD<T>::operator*=(int num){
	ht *= num;
	wid *= num;
	dep *= num;

	return;
}


/*implement for the following class LInkedList , constructor, copy constructor, initializer_list, copy assighment,
destructor, move constructor, move assignment, ThreeTimes.  in addition, you need to overload operator<< for tree class.
For all of them, print a statement such as "copy Assignment LL" */

template <class T> class node {
public:
	T value;
	node* next;
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
    void operator*=(int num);

};

// Constructor--------------------------------
template <class T> LinkedList<T>::LinkedList(LinkedList<T>&& L) {//Will be invoked in the same three condition, when Rvalue is used.
	head = L.head;
	L.head = nullptr;

	cout << "Move Constructor LL" << endl;

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
	cout << "Copy Constructor LL" << endl;
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
	cout << "Initializer List LL" << endl;
}

// Destructor--------------------------------

template <class T> LinkedList<T>::~LinkedList() {//Destructor
	while (head) {
		node<T>* p{ head->next };
		delete head;
		head = p;
	}
	cout << "Destructor LL" << endl;
}

// threeTimne--------------------------------
template <class T> LinkedList<T> LinkedList<T>::ThreeTimes() {
	LinkedList<T> temp{ *this };
	node<T>* p{ temp.head };
	while (p) {
		p->value *= 3;
		p = p->next;
	}

	cout << "ThreeTimes LL" << endl;
	return temp;//visual studio compiler will change it to return move(temp); 
}


// Assignment--------------------------------

template <class T> LinkedList<T> LinkedList<T>::operator=(LinkedList<T>&& L) { //move assignment
	while (head) {
		node<T>* p1{ head->next };
		delete head;
		head = p1;
	}
	head = L.head;
	L.head = nullptr;
	cout << "Move Assignment LL" << endl;
	return *this;
}

template <class T> LinkedList<T> LinkedList<T>::operator=(const LinkedList<T>& L) {//operator=; copy assignment
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

	cout << "Copy Assignment LL" << endl;
	return *this;
}


// overload << --------------------------------

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

template <class T> void LinkedList<T>::operator*=(int num){
	node<T>* p{ head };
	
	while (head) {
		head->value *= num;
		head = head->next;
	}

	head = p;

	return;
}

/*implement for the following class tree, constructor, copy constructor, initializer_list, copy assignment,
destructor, move constructor, move assignment, ThreeTimes, print_inO, print_preO, print_postO.  in addition, you need to overload operator<< for tree class.
For all of them, print a statement such as "copy Assignment tree" .   You might need to overload additional things for handling ThreeTimes..
*/

template <class T> class Node {
public:
	T value;
	Node<T>* l_child, * r_child;
	Node(T i) : value{ i }, l_child{ nullptr }, r_child{ nullptr }{};
	Node() {
		l_child=nullptr;
		r_child=nullptr;
		return;
	}
};

template <class T> class tree {
public:
	Node<T>* root;
	tree(int k);//constructor; k is level
	tree() : root{ nullptr } {}
	//function help_c for constructor


	void help_il(const initializer_list<T>& list, int index, Node<T>* &node);
	void help_cc(const Node<T>* nodeO, Node<T>* &nodeN);
	void help_d(Node<T>* node);
	void help_tt(Node<T>* node);
	void help_mul(Node<T>* node, int num);

	tree(const initializer_list<T>& I);//initializer_list
	//help_il

	tree(const tree<T>& T1);//copy constructor
	//help_cc


	tree operator=(const tree<T>& T1);
	//help_ca

	~tree();
	//help_d

	tree ThreeTimes();
	//help_tt

	tree(tree<T>&& T1);//Move Constructor
	tree operator=(tree<T>&& T1);//Move Assignment

	void operator*=(int num);

};
// helper----------------------------------
// template <class T> void tree<T>::help_il(const initializer_list<T>& list, initializer_list<T>::iterator& it , Node<T>* node){
	
// }
template <class T> void tree<T>::help_il(const initializer_list<T>& list, int index, Node<T>* &node){
	if(index >= list.size()){
		return;
	}

	// node = new Node<T>(*next(list.begin(), index));
	node = new Node<T>();
	node->value = *next(list.begin(), index);

	help_il(list, (index * 2 + 1), node->l_child);
	help_il(list, (index * 2 + 2), node->r_child);

	return;
}


// template <class T> tree<T>::tree(int k):tree<T>::tree(){
template <class T> void tree<T>::help_cc(const Node<T>* nodeO, Node<T>* &nodeN){
	if(nodeO == nullptr){
		return;
	}

	// nodeN = new Node<T>(nodeO->value);
	nodeN = new Node<T>();
	nodeN->value = nodeO->value;

	help_cc(nodeO->l_child, nodeN->l_child);
	help_cc(nodeO->r_child, nodeN->r_child);

	return;
}

// }

// Constructors ---------------------------
template <class T> tree<T>::tree(tree<T>&& T1){//Move Constructor
	root = T1.root;
	T1.root = nullptr;
	
	cout << "Move Constructor tree" << endl;
	
	return;
}



template <class T> tree<T>::tree(const initializer_list<T>& I){
	help_il(I, 0, root);

	cout << "Initializer List tree" <<endl;

	return;
}

template <class T> tree<T>::tree(const tree<T>& T1){
	help_cc(T1.root, root);

	cout << "Copy Constructor tree" <<endl;

	return;
}

//Assigbnment ------------------------------------------------

template <class T> tree<T> tree<T>::operator=(const tree<T>& T1){//copy assignment of Tree
	// help_cc(T1.root, root);
	help_d(root);

	tree<T> temp(T1);
	root = temp.root;
	temp.root = nullptr;

	cout << "Copy Assignment tree" <<endl;

	return *this;
}

template <class T> tree<T> tree<T>::operator=(tree<T>&& T1){//Move Assignment
	help_d(root);

	root = T1.root;
	T1.root = nullptr;
	
	cout << "Move Assignment tree" << endl;

	return *this;
}


// Deconsturctor-----------------------------------------
template <class T> tree<T>::~tree(){
	help_d(root);

	cout << "Destructor tree" <<endl;

	return;
}

template <class T> void tree<T>::help_d(Node<T>* node){
	if(node == nullptr){
		return;
	}

	help_d(node->l_child);
	help_d(node->r_child);

	delete node;

	return;
}

//ThreeTimes -------------------------------------------------------

template <class T> void tree<T>::help_tt(Node<T>* node){
	if(node == nullptr){
		return;
	}

	node->value *= 3;

	help_tt(node->l_child);
	help_tt(node->r_child);

	return;
}
	
template <class T> tree<T> tree<T>::ThreeTimes(){
	tree<T> temp(*this);

	help_tt(temp.root);

	cout<< "ThreeTimes tree" <<endl;

	return move(temp);
}


//Overload : Inorder treversal --------------------------------------

template <class T> void help_p(ostream& str, int index, const Node<T>* node){
	if(node == nullptr){
		return;
	}

	help_p(str, (index * 2 + 1), node->l_child);

	str << node->value << " ";

	help_p(str, (index * 2 + 2), node->r_child);

	return;
}
template <class T> ostream& operator<<(ostream& str, const tree<T>& L){
	help_p(str, 0, L.root);

	return str;
}


template <class T> void tree<T>::help_mul(Node<T>* node, int num){
	if(node == nullptr){
		return;
	}

	node->value *= num;
	help_mul(node->l_child, num);
	help_mul(node->r_child, num);

	return;
}

template <class T> void tree<T>::operator*=(int num){
	help_mul(root, num);

	return;
}

int main() {

	tree<int> T1{ 0, 11, 2, 3, 4, 5, 6 };
	cout << T1 << endl;
	
	tree<int> T2{ T1 };
	cout << T2 << endl;

	tree<int> T3;
	T3 = T1;
	cout << T3<< endl;

	T3 = T1.ThreeTimes();
	cout << T3 << endl;


	tree<ThreeD<int>> T4{ {1,2,3}, {4,5,6}, {2,2,2}, {3,3,3}, {4,4,4}, {5,5,5}, {1,1,1} };
	cout << T4 << endl;

	tree<ThreeD<int>> T5{ {4,4,4}, {5,5,5}, {6,6,6} };
	cout << T5 << endl;

	tree<LinkedList<int>> T6{ {1} , { 4, 5, 6 }, { 7,8 } };
	cout << T6 << endl;

	tree < LinkedList<ThreeD<int>>> T7{ {{1,2,3}, {4,5,6}, {7,8,9}}, {{1,1,1}, {2,2,2}}, {{3,3,3},{4,4,4}, {5,5,5}} };
	cout << T7 << endl;

	T7 *= 4;
	cout << T7 << endl;
	tree < LinkedList<ThreeD<int>>> T8;
	T8 = T7.ThreeTimes();
	cout << T8 << endl;

	auto p3{ new tree < LinkedList<ThreeD<int>>> { {{1,2,3}, {4,5,6}, {7,8,9}}, {{1,1,1}, {2,2,2}}, {{3,3,3},{4,4,4}, {5,5,5}} } };
	delete p3;
	return 0;
}
