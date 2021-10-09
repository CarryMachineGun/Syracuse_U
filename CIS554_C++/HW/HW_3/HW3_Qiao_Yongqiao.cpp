
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
    // ThreeD<T> ThreeTimes();
    ThreeD<T> ThreeTimes();
    ThreeD<T> operator *=(const int& num);
    // ThreeD<T> operator *(const int& num);

};

template<class T> ThreeD<T> ThreeD<T>::operator *=(const int& num) {

    this->wid = this->wid * num;
    this->dep = this->dep * num;
    this->ht = this->ht * num;

    return *this;
}

// template<class T> ThreeD<T> ThreeD<T>::operator *(const int& num) {
//     // ThreeD temp;
//     this->dep = this->dep * num;
//     this->wid = this->wid * num;
//     this->ht = this->ht * num;
//     return *this;
// }



template <class T> ostream& operator<<(ostream& str, const ThreeD<T>& t1) {
	str << "(" << t1.ht << ", " << t1.wid << ", " << t1.dep << ")";
	return str;
}

template<class T> ThreeD<T> ThreeD<T>::ThreeTimes() {
    this->dep *= 3;
    this->wid *= 3;
    this->ht *= 3;
    return *this;
}

/*implement for the following class LInkedList , constructor, copy constructor, initializer_list, copy assighment,
destructor, move constructor, move assignment, ThreeTimes.  in addition, you need to overload operator<< for tree class.
For all of them, print a statement such as "copy Assignment LL"*/

template <class T> class node {
public:
	T value;
	node* next;
	node(T i) : value(i), next(nullptr) {}
	node() : next(nullptr) {}
    // node<T> ThreeTimes();
    node<T> operator *=(const int& num);
    
};

template<class T> node<T> node<T>::operator *=(const int& num) {

    this->value = this->value * num;

    return *this;
}


template <class T> ostream& operator<<(ostream& str, const node<T>& n1) {
	str << n1.value << " ";
	return str;
}



// template<class T> node<T> node<T>::ThreeTimes() {
//     node<T> n1 { *this };
//     n1.value = n1.value * 3;
//     return n1;
// }


template <class T> class Node {
public:
	T value;
	Node<T>* l_child, * r_child;
	Node(T i) : value{ i }, l_child{ nullptr }, r_child{ nullptr }{};
	Node() {  }
    Node<T> ThreeTimes();
    Node<T> operator *=(const int& num);
};

template<class T> Node<T> Node<T>::operator *=(const int& num) {

    this->value = this->value * num;

    return *this;
}



template<class T> Node<T> Node<T>::ThreeTimes() {
    Node<T> n2 { *this };
    n2.value = n2.value * 3;
    return n2;
}

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
    LinkedList<T> operator *=(const int& num);
    // void operator *=(const int& num);

};

template<class T> LinkedList<T> LinkedList<T>::operator *=(const int& num) {

    LinkedList<T>* temp{ this };
	node<T>* p{ temp->head };
	while (p) {
		p->value *= num;
		p = p->next;
	}
	return *temp;
}

// 树的threetimes()方法
template<class T> LinkedList<T> LinkedList<T>::ThreeTimes() {
    LinkedList<T>* temp{ this };
    node<T>* p{ temp->head };
    while(p) {
        p->value *= 3;
        p = p->next;
    }
    return *temp;
}

// template <class T> LinkedList<T> LinkedList<T>::ThreeTimes() {
// 	LinkedList<T> temp{ *this };
// 	node<T>* p{ temp.head };
// 	while (p) {
// 		p->value *= 3;
// 		p = p->next;
// 	}

// 	cout << "ThreeTimes" << endl;
// 	return temp;//visual studio compiler will change it to return move(temp); 
// }


/*implement for the following class tree, constructor, copy constructor, initializer_list, copy assignment,
destructor, move constructor, move assignment, ThreeTimes, print_inO, print_preO, print_postO.  in addition, you need to overload operator<< for tree class.
For all of them, print a statement such as "copy Assignment tree" .   You might need to overload additional things for handling ThreeTimes..
*/
template <class T> class tree {
public:
	Node<T>* root;
	// tree(int k) { root = help_c(k); }//constructor; k is level
    // tree(int k);
    // Node<T>* help_c(int k);

	tree() : root{ nullptr } {}
	//function help_c for constructor

	// tree(const initializer_list<T>& I) : tree(int(log2(I.size() + 1))) { tree2(root,0,I); cout << "Initializer List" << endl; };
    // tree(const initializer_list<T>& I) : tree(int(log2(I.size() + 1))) { help_il(); cout << "Initializer List" << endl; };

    // void help_il();
    tree(const initializer_list<T>& I);
    //initializer_list
	void help_il(Node<T>* &root, int index, const initializer_list<T>& I);
    //help_il


    //copy constructor
    tree(const tree<T>& T1);
	//help_cc
    void help_cc(const Node<T>* root1, Node<T>*& root2);


	tree<T> operator=(const tree<T>& T1);
	// help_ca
    void help_ca(const Node<T>* root1, Node<T>* & root);


    // Destructor
	~tree();
	void help_d(Node<T>*& root);

    
	// tree ThreeTimes();
    tree<T> ThreeTimes();
	//help_tt
    void help_tt(Node<T>* node);


	


    // void print_inO(Node<T>* p);
    // void print_preO(Node<T>* p);
    // void print_postO(Node<T>* p);


    // *= 重写
    void operator*=(const int& num);
    void help_ome(Node<T>*& N1, const int& num);

	//Move Constructor
	tree(tree<T>&& T1);
	//Move Assignment
	tree<T> operator=(tree<T>&& T1);
};


template<class T> tree<T> tree<T>::operator=(tree<T>&& T1) {
	help_d(root);
	root = T1.root;
	T1.root = nullptr;
	
	cout << "Move Assignment tree" << endl;
	return *this;
}


template<class T> tree<T>::tree(tree<T>&& T1) {

	root = T1.root;
	T1.root = nullptr;

	cout << "Move Constructor tree" << endl;
}



// ThreeTimes
template<class T> tree<T> tree<T>::ThreeTimes() {
	tree<T> temp{*this};

	help_tt(temp.root);

	cout << "ThreeTimes tree" << endl;
    return move(temp);
}

template<class T> void tree<T>::help_tt(Node<T>* node) {
	if(node == nullptr){
		return;
	}
 	
    node->value *= 3;

    help_tt(node->l_child);
    help_tt(node->r_child);
    
	return;
}


//  *= 重写

template<class T> void tree<T>::operator *=(const int& num) {
    help_ome(root, num);

}

template<class T> void tree<T>::help_ome(Node<T>*& N1, const int& num) {
    if(N1 == nullptr)
        return;
    N1->value *= num;
    help_ome(N1->l_child, num);
    help_ome(N1->r_child, num);
    return;
}


// copy assignment
template<class T> tree<T> tree<T>::operator=(const tree<T>& T1) {
    help_d(root);
    
    tree<T> temp(T1);
    root = T1.root;
    temp.root = nullptr;

    cout << "Copy Assignment tree" << endl;
    return *this;
}

template<class T> void tree<T>::help_ca(const Node<T>* root1, Node<T>* & root) {
    
    if(root1 == nullptr)
        return; 
    else {
        root = new Node<T> (root1->value) ;
        help_ca(root1->l_child, root->l_child);
        help_ca(root1->r_child, root->r_child);
    }
}


//destructor
template<class T> tree<T>::~tree() {
    help_d(root);
    cout << "Destructor tree" << endl;
}

template<class T> void tree<T>::help_d(Node<T>*& root) {
    // if(!root->l_child && !root->r_child)
    //     delete root;
    if(root == nullptr)
        delete root;
    else{
        // Node<T>* l_c = root->l_child;
        // Node<T>* r_c = root->r_child;
        help_d(root->l_child);
        help_d(root->r_child);
    }
}
 

// copy constructor

template<class T> tree<T>::tree(const tree<T>& T1):tree() {
    // Node<T> *root2 = nullptr;
    help_cc(T1.root, root);
    cout << "Copy Constructor tree" << endl;
}

template<class T> void tree<T>::help_cc(const Node<T>* root1, Node<T>* & root) {
    
    if(root1 == nullptr)
        return; 
    else {
        root = new Node<T> (root1->value) ;
        help_cc(root1->l_child, root->l_child);
        help_cc(root1->r_child, root->r_child);
    }
}


// initializer_list

template<class T> void tree<T>::help_il(Node<T>* &root, int index, const initializer_list<T>& I) {
    // int mul = 1;
    if(index >= I.size())
        return;
    root = new Node<T>( *next(I.begin(), index));
    // cout << "root value: " << root->value << endl;
    help_il(root->l_child, index*2+1, I);
    help_il(root->r_child, (index+1)*2, I);
    return;
}

template<class T> tree<T>::tree(const initializer_list<T>& I) {
    help_il(root,0,I);
    cout << "Initializer List tree" << endl;
}


//前序遍历树
template<class T> void print_preO(Node<T>* p) {
    if (p) {
        cout << p->value << " ";
		print_preO(p->l_child);
		print_preO(p->r_child);
	}
}

//后序遍历树
template<class T> void print_postO(Node<T>* p) {
    if (p) {
		print_postO(p->l_child);
		print_postO(p->r_child);
        cout << p->value << " ";
	}
}

//中序遍历树
template<class T> void print_inO(ostream& str, Node<T>* p) {
    if (p) {
		print_inO(str, p->l_child);
		str << p->value << " ";
		print_inO(str, p->r_child);
	}
}

// //重写打印树
template<class T> ostream& operator<<(ostream& str, const tree<T>&  t) {
	// str << "{ ";
    Node<T>* root = t.root;
	print_inO(str,root);
	// str << "}";
	return str;
}

// ========================== LinkedList 代码 =================================

template <class T> LinkedList<T> LinkedList<T>::operator=(LinkedList<T>&& L) {
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

template <class T> LinkedList<T>::LinkedList(LinkedList<T>&& L) {//Will be invoked in the same three condition, when Rvalue is used.
	head = L.head;
	L.head = nullptr;

	cout << "Move Constructor LL" << endl;

}

template <class T> LinkedList<T>::~LinkedList() {//Destructor
	while (head) {
		node<T>* p{ head->next };
		delete head;
		head = p;
	}
	cout << "Destructor LL" << endl;
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


//930的录播13:40 可以直接套用课程代码模版