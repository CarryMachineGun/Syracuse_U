
#include <iostream>

using namespace std;

class node {
public:
	int value;
	node* l_child;
	node* r_child;
	node(int i) : value(i), l_child{ nullptr }, r_child{ nullptr }{}
	node(): l_child{nullptr}, r_child{nullptr}{}
};

class tree {
public:
	node* root;
	tree(int i, int m); //copy constructor; Construct a level i tree with random values in 0 ... m
	tree(): root {nullptr}{}
	node* help_c(int i, int m);
	void mirror(node * p1);
	node * mirrorCopy(node* p1);


};
node * tree::mirrorCopy(node* p1) {
	if(p1 == nullptr){
		return nullptr;
	}

	node* p2 = new node{p1->value};

	p2->l_child = mirrorCopy(p1->r_child);
	p2->r_child = mirrorCopy(p1->l_child);

	return p2;
}

void tree::mirror(node * p1) {
	if(p1 == nullptr){
		return;
	}

	swap(p1->l_child, p1->r_child);

	mirror(p1->r_child);
	mirror(p1->l_child);

	return;
}

tree::tree(int i, int m) {
	root = help_c(i, m);
}
node* tree::help_c(int i, int m) {
	if (i == 0) return nullptr;
	node* p1{ new node{rand()%m} };
	p1->l_child = help_c(i - 1, m);
	p1->r_child = help_c(i - 1, m);
	return p1;
}




void help_cout(ostream& str, node* p1);
void help_cout1(ostream& str, node* p1);


ostream& operator<<(ostream& str, const tree&& T);
ostream& operator<<(ostream& str, const tree& T);

int main() {
	tree T1{ 3, 10};
	cout << T1 << endl;
	cout << move(T1) << endl;
	T1.mirror(T1.root);
	cout << T1 << endl;
	cout << move(T1) << endl;

	tree T2;
	T2.root = T1.mirrorCopy(T1.root);
	cout << T2 << endl;
	cout << move(T2) << endl;

	return 0;
}



void help_cout(ostream& str, node* p1) {//in-order traversal
	if (!p1) return;
	help_cout(str, p1->l_child);
	str << p1->value << " ";
	help_cout(str, p1->r_child);
}
void help_cout1(ostream& str, node* p1) {//post-order traversal
	if (!p1) return;
	help_cout1(str, p1->l_child);
	help_cout1(str, p1->r_child);
	str << p1->value << " ";
}


ostream& operator<<(ostream& str, const tree&& T) {
	help_cout1(str, T.root);
	return str;
}
ostream& operator<<(ostream& str, const tree& T) {
	help_cout(str, T.root);
	return str;
}