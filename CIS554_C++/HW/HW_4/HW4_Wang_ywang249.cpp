//HW4 by Yuchen Wang
//SU Net ID: ywang249  SUID: 905508464

//HW4 Due: 11:59pm, Friday October 29
#include <iostream>
#include <memory>
#include <list>

using namespace std;

class node
{
public:
	shared_ptr<list<shared_ptr<int>>> Value;
	shared_ptr<node> South;
	weak_ptr<node> East;
	node()
	{
		Value = make_shared<list<shared_ptr<int>>>();
	}
};

class TwoD
{ //rectangle
public:
	int Rows; //Number of Rows
	int Cols; //Number of Columns
	shared_ptr<node> head;
	//TwoD(int i, int j);
	TwoD() : Rows{0}, Cols{0} {}

	//*********************
	//Implement all the following member functions.
	TwoD(int r, int c); //constructor
	TwoD(const initializer_list<initializer_list<initializer_list<int>>> &I);
	TwoD(const TwoD &T);		   //copy constructor
	TwoD operator=(const TwoD &T); //copy assignment
	~TwoD();					   //destructor
	TwoD(TwoD &&T);				   //move constructor
	TwoD operator=(TwoD &&T);	   //move assignment
	TwoD Times(int k) const;	   //Return a TwoD object with all values being k times of those in *this .
	void DeleteR(int r);		   //Delete row r
	void DeleteC(int c);		   //Delete column c
};
ostream &operator<<(ostream &str, const list<shared_ptr<int>> &L)
{
	//Your code
	str << "( ";
	for (shared_ptr<int> k : L)
	{
		str << *k << " ";
	}
	str << ")";

	return str;
}

ostream &operator<<(ostream &str, const TwoD &&T)
{ //Print in olumn-major order
	//Your code
	shared_ptr<node> curr = T.head;

	for (int i = 0; i < T.Cols; i++)
	{
		for (int i = 0; i < T.Rows; i++)
		{
			shared_ptr<list<shared_ptr<int>>> value_list = curr->Value;
			str << *value_list;
			curr = curr->South;
		}
		str << "\n";
	}

	return str;
}

ostream &operator<<(ostream &str, const TwoD &T)
{ //Print in row-major order
	//Your code
	shared_ptr<node> row_head = T.head;
	weak_ptr<node> curr;
	for (int i = 0; i < T.Rows; i++)
	{
		curr = row_head;
		for (int j = 0; j < T.Cols; j++)
		{
			shared_ptr<list<shared_ptr<int>>> value_list = curr.lock()->Value;
			str << *value_list;
			curr = curr.lock()->East;
		}
		row_head = row_head->South;
		str << "\n";
	}

	str << endl;

	return str;
}

TwoD::~TwoD()
{
	// cout << "Destructor " << this << endl;
	cout << "Destructor " << endl;

	Cols = 0;
	Rows = 0;

	if (!head)
	{
		return;
	}

	head->South.reset();
	head.reset();

	return;
}

TwoD::TwoD(const TwoD &T) : TwoD(T.Rows, T.Cols)
{
	cout << "Copy Constructor " << endl;
	// cout << "Copy Constructor " << &T << endl;
	shared_ptr<node> o_curr = T.head, curr = head;
	shared_ptr<list<shared_ptr<int>>> curr_list;

	while (o_curr->South != T.head)
	{
		curr_list = curr->Value;
		for (shared_ptr<int> i : *(o_curr->Value))
		{
			curr_list->push_back(make_shared<int>(*i));
		}
		curr = curr->South;
		o_curr = o_curr->South;
	}

	curr_list = curr->Value;
	for (shared_ptr<int> i : *(o_curr->Value))
	{
		curr_list->push_back(make_shared<int>(*i));
	}

	return;
}

TwoD::TwoD(TwoD &&T)
{
	cout << "Move Constructor " << endl;
	// cout << "Move Constructor " << this << endl;

	Cols = T.Cols;
	Rows = T.Rows;

	head = T.head;
	T.head.reset();

	return;
}

TwoD TwoD::operator=(const TwoD &T)
{
	cout << "Copy Assignment " << endl;
	// cout << "Copy Assignment " << &T << endl;
	if (head)
	{
		head->South.reset();
		head.reset();
	}

	TwoD temp(T);
	
	Cols = temp.Cols;
	Rows = temp.Rows;

	head = temp.head;
	temp.head.reset();

	return *this;
}

TwoD TwoD::operator=(TwoD &&T)
{
	cout << "Move Assignment " << endl;
	// cout << "Move Assignment " << &T << " " << this << endl;
	if (head)
	{
		head->South.reset();
		head.reset();
	}

	Cols = T.Cols;
	Rows = T.Rows;

	head = T.head;
	T.head.reset();

	return *this;
}

TwoD TwoD::Times(int k) const
{

	TwoD temp(*this);

	shared_ptr<node> curr = temp.head;
	shared_ptr<list<shared_ptr<int>>> curr_list;

	while (curr->South != temp.head)
	{
		curr_list = curr->Value;
		for (shared_ptr<int> i : *(curr_list))
		{
			*i = k * (*i);
		}
		curr = curr->South;
	}

	curr_list = curr->Value;
	for (shared_ptr<int> i : *(curr->Value))
	{
		*i = k * (*i);
	}
	cout << "Times " << endl;
	// cout << "Times " << &temp << endl;

	return move(temp);
}

void TwoD::DeleteR(int r)
{
	if(r > (Rows - 1) || r < 0){
		return;
	}

	// there could be the special case of 1 or 2 rows
	shared_ptr<node> pre = head; 
	for (int i = 1; i < (r + Rows); i++)
	{
		pre = pre->South;
	}

	for (int i = 0; i < Cols; i++)
	{
		if(pre->South == head){
			head = pre->South->South;
		}
		pre->South = pre->South->South;
		pre = (pre->East).lock();
	}

	Rows--;

	return;
}

void TwoD::DeleteC(int c)
{
	if(c > (Cols - 1) || c < 0){
		return;
	}

	shared_ptr<node> pre_column_head = head, pre_column_curr, next_column_head, pre_column_tail;

	// initilize values
	for(int i = 1; i < (c + Cols); i++){
		pre_column_head = pre_column_head->East.lock();
	}

	pre_column_tail = pre_column_head;
	for(int i = 1; i < Rows; i++){
		pre_column_tail = pre_column_tail->South;
	}

	pre_column_curr = pre_column_head;
	next_column_head = pre_column_head->East.lock()->East.lock();

	// reset east
	for(int i = 0; i < Rows; i++){
		pre_column_curr->East = pre_column_curr->East.lock()->East;
		pre_column_curr = pre_column_curr->South;
	}

	//reset head
	if(c == 0){
		head = head->East.lock();
	}

	// remove the column
	pre_column_tail->South = next_column_head;

	Cols--;

	return;
}

TwoD::TwoD(int r, int c)
{
	if (r == 0 || c == 0)
	{
		return;
	}
	Rows = r;
	Cols = c;

	//create nodes and connect south
	head = make_shared<node>();
	shared_ptr<node> curr = head;
	for (int i = 1; i < (Rows * Cols); i++)
	{
		curr->South = make_shared<node>();
		curr = curr->South;
	}

	curr->South = head;

	//connect east
	shared_ptr<node> row_head = head, pre;
	for (int i = 0; i < Rows; i++)
	{
		curr = row_head;
		for (int j = 1; j < Cols; j++)
		{
			pre = curr;
			for (int k = 0; k < Rows; k++)
			{
				curr = curr->South;
			}
			pre->East = curr;
		}
		curr->East = row_head;
		row_head = row_head->South;
	}

	return;
}

// TwoD T1{ { {1,1,1}, {2,2}, {3,3,3}}, {{4,4}, {5,5, 5,5}, {6,6}},
// 	{{7, 7, 7},{8,8}, {9}}, {{10,10,10,10}, {11,11}, {12,12,12,12,12}} };//4 rows, 3 columns
TwoD::TwoD(const initializer_list<initializer_list<initializer_list<int>>> &I) : TwoD(I.size(), (I.begin())->size())
{
	shared_ptr<node> row_head = head, curr;

	for (auto i = I.begin(); i != I.end(); i++)
	{
		curr = row_head;
		for (auto j = i->begin(); j != i->end(); j++)
		{
			shared_ptr<list<shared_ptr<int>>> value_list = curr->Value;
			for (int k : *j)
			{
				value_list->push_back(make_shared<int>(k));
			}
			curr = (curr->East).lock();
		}
		row_head = row_head->South;
	}

	cout << "Initializer List" << endl;

	return;
}

int main()
{
	TwoD T1{{{1, 1, 1}, {2, 2}, {3, 3, 3}}, {{4, 4}, {5, 5, 5, 5}, {6, 6}}, {{7, 7, 7}, {8, 8}, {9}}, {{10, 10, 10, 10}, {11, 11}, {12, 12, 12, 12, 12}}}; //4 rows, 3 columns
	cout << T1 << endl;
	TwoD T2(T1);
	cout << T2 << endl;
	T2 = T1.Times(4);
	cout << T2 << endl;
	T1.DeleteR(3);
	// T1.DeleteR(0);
	cout << T1 << endl;
	cout << move(T1) << endl;
	T2.DeleteC(2);
	// T2.DeleteC(0);
	cout << T2 << endl;
	cout << move(T2) << endl;
	return 0;
}