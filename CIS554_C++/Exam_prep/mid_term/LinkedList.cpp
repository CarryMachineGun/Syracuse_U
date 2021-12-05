
#include <iostream> //cout , cin
using namespace std;

class node
{
public:
	int value;
	node *next;
	node(int i)
	{
		value = i;
		next = nullptr;
	} // NULL is out of date
	node() { next = nullptr; }
};

class LinkedList
{
public:
	node *head;
	LinkedList() { head = nullptr; }

	LinkedList(int A[], int size);

	void makeList(int n, int m);

	void print();

	void reverse(); // funciton prototype

	void remove(int k); // remove the first node with value k

	void add(int i, int value);

	~LinkedList();
};

void LinkedList::reverse()
{
	node *p1 = head, *p2 = head->next;

	while (p2)
	{
		node *p3 = p2->next;

		p2->next = p1;
		if (p1 == head)
		{
			p1->next = nullptr;
		}

		p1 = p2;
		p2 = p3;
	}

	head = p1;

	return;
}
// void LinkedList::reverse()
// {
// 	if(!head){
// 		return;
// 	}

// 	node* p1 = head, *p2 = head->next;

// 	while(p2){
// 		node* temp = p2->next;
// 		p2->next = p1;
// 		if(p1 == head){
// 			p1->next = nullptr;
// 		}

// 		p1 = p2;
// 		p2 = temp;
// 	}

// 	head = p1;

// 	return;
// }

void LinkedList::add(int i, int value)
{
	node *p = head;

	if (i == 0)
	{
		head = new node{value};
		head->next = p;
	}
	else
	{
		while (i > 0)
		{
			p = p->next;

			if (p == nullptr)
			{
				return;
			}

			i--;
		}
	}

	node *o_next = p->next;
	p->next = new node{value};
	p->next->next = o_next;
	return;
}

void LinkedList::remove(int i)
{
	node* p = head;

	while(i > 0){
		p = p->next;

		if(p->next == nullptr){
			return;
		}
		i--;
	}

	node* de_node = p->next;
	p->next = p->next->next;
	delete de_node;

	return;

}

LinkedList::~LinkedList(){
	node* curr = head, *next = head->next;

	while(next){
		delete curr;
		curr = next;
		next = next->next;
	}

	delete curr;

	return;
}

void LinkedList::print()
{
	node *p1{head};

	while (p1)
	{
		cout << p1->value << " ";
		p1 = p1->next;
	}
	cout << endl;
}

LinkedList::LinkedList(int A[], int size)
{
	for (int i = size - 1; i >= 0; --i)
	{
		node *p1{new node{A[i]}};
		p1->next = head;
		head = p1;
	}
}

void LinkedList::makeList(int n, int m)
{ // create an n-node LinkedList with random value in 0 ...m-1
	for (int i = 0; i < n; ++i)
	{
		node *p1{new node{rand() % m}}; // rand() return a random integer
		p1->next = head;
		head = p1;
	}
}

int main()
{
	LinkedList L1;
	L1.makeList(10, 20);
	L1.print();
	L1.reverse();
	L1.print();
	L1.add(0, 5);
	L1.print();
	L1.remove(4);
	L1.print();

	L1.~LinkedList();
	L1.print();

	return 0;
}
