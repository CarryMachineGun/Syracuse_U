#include <iostream>
#include <list>
#include <vector>
#include <deque>

using namespace std;
// a binary predicate implemented as a function:
bool same_integral_part(double first, double second)
{
	return (int(first) == int(second));
}

// a binary predicate implemented as a class:
struct is_near {
	bool operator() (double first, double second)
	{
		return (abs(first - second) < 5.0);//fabs 
	}
};

// a predicate implemented as a function:
bool single_digit(const int& value) { return (value < 10); }

// a predicate implemented as a class:
struct is_odd {
	bool operator() (const int& value) { return (value % 2) == 1; }
};


int main() {

	list<int> L1(4, 10);//10 10 10 10
	for (auto& i : L1) { cout << i << " "; }
	cout << endl;
	L1.insert(++L1.begin(), 20);//10 20 10 10 10
	for (auto& i : L1) { cout << i << " "; }
	cout << endl;
	list<int> L2(3, 100);//100 100 100
	L1.insert(L1.begin(), ++L2.begin(), L2.end());//100 100 10 20 10 10 10
	for (auto& i : L1) { cout << i << " "; }
	cout << endl;
	vector<int> V1{ 1,2,3,4 };
	L1.insert(L1.begin(), V1.begin() + 1, V1.end() - 1);//2 3 100 100 10 20 10 10 10
	for (auto& i : L1) { cout << i << " "; }
	cout << endl;
	int A[]{ 11,22,33,44 };
	L1.insert(L1.begin(), A + 1, A + 3);//22 33 2 3 100 100 10 20 10 10 10
	for (auto& i : L1) { cout << i << " "; }
	cout << endl;
	//insert for list is the same as that for vector
	
	list<int> L3{ 14, 7, 25 };
	L1.sort();
	L3.sort();
	L1.merge(L3);//only merge already sorted lists
	//L3 will becomes empty.
	cout << L1.size() << " " << L3.size() << endl;
	for (auto& i : L1) { cout << i << " "; }
	cout << endl;

	L1.remove(10);//Remove all occurances of 10
	for (auto& i : L1) { cout << i << " "; }
	cout << endl;

	int myints[] = { 15,36,7,17,20,39,4,1 };
	std::list<int> mylist3(myints, myints + 8);   // 15 36 7 17 20 39 4 1

	mylist3.remove_if(single_digit);           // 15 36 17 20 39

	mylist3.remove_if(is_odd());   //is_odd() calls constructor to create an anonymous object
								 //  of struct is_odd// 36 20
	//lambda expression is also OK

	std::cout << "mylist3 contains:";
	for (std::list<int>::iterator it = mylist3.begin(); it != mylist3.end(); ++it)
		std::cout << ' ' << *it;
	std::cout << '\n';

	list<int*> L6 { new int{5}, new int {8} };


	L3.assign(7, 3000);//3000 3000 3000 3000 3000 3000 3000
	L3.assign(L1.begin(), L1.end());//L3 have the same values as L1

	//The following unique and splice examples are from cplusplus.com
	double mydoubles[] = { 12.15,  2.72, 73.0,  12.77,  3.14,
					  12.77, 73.35, 72.25, 15.3,  72.25 };
	list<double> mylist(mydoubles, mydoubles + 10);

	mylist.sort();             //  2.72,  3.14, 12.15, 12.77, 12.77,
							   // 15.3,  72.25, 72.25, 73.0,  73.35

	mylist.unique();           //  2.72,  3.14, 12.15, 12.77
							   // 15.3,  72.25, 73.0,  73.35  duplicates wiil be removed

	mylist.unique(same_integral_part);  //  2.72,  3.14, 12.15
										 // 15.3,  72.25, 73.0

	mylist.unique(is_near());           //  2.72, 12.15, 72.25

	cout << "mylist contains:";
	for (list<double>::iterator it = mylist.begin(); it != mylist.end(); ++it)
		cout << ' ' << *it;
	cout << '\n';





	list<int> mylist1, mylist2;
	list<int>::iterator it;

	// set some initial values:
	for (int i = 1; i <= 4; ++i)
		mylist1.push_back(i);      // mylist1: 1 2 3 4

	for (int i = 1; i <= 3; ++i)
		mylist2.push_back(i * 10);   // mylist2: 10 20 30

	it = mylist1.begin();//it = begin(mylist1); is also OK
	++it;                         // points to 2

	mylist1.splice(it, mylist2); // mylist1: 1 10 20 30 2 3 4
								  // mylist2 (empty)
								  // "it" still points to 2 (the 5th element)

	mylist2.splice(mylist2.begin(), mylist1, it);
	// mylist1: 1 10 20 30 3 4
	// mylist2: 2
	// "it" is now invalid.
	it = mylist1.begin();// it = it+3; Error.
	advance(it, 3);           // "it" points now to 30

	mylist1.splice(mylist1.begin(), mylist1, it, mylist1.end());
	// mylist1: 30 3 4 1 10 20

	cout << "mylist1 contains:";
	for (it = mylist1.begin(); it != mylist1.end(); ++it)
		cout << ' ' << *it;
	cout << '\n';

	cout << "mylist2 contains:";
	for (it = mylist2.begin(); it != mylist2.end(); ++it)
		cout << ' ' << *it;
	cout << '\n';

	//deque:  Double-Ended QUEue; list with subscript [] function

	deque<int> D{ 1,2,3,4,5 };
	D.pop_front();
	D.pop_back();
	D.push_back(10);
	D.push_front(10);

	D[2] = 10;//vector is the other contain that supports this

	auto it10{ D.begin() };
	//it10 = it10 + 1; Error
	it10++;
	++it10;
	it10--;
	--it10;

	/*
Deques provide a functionality similar to vectors, but with efficient insertion and deletion of elements
also at the beginning of the sequence, and not only at its end. But, unlike vectors,
deques are not guaranteed to store all its elements in contiguous storage locations:
accessing elements in a deque by offsetting a pointer to another element causes undefined behavior.

Both vectors and deques provide a very similar interface and can be used for similar purposes,
but internally both work in quite different ways: While vectors use a single array that needs
to be occasionally reallocated for growth, the elements of a deque can be scattered
in different chunks of storage, with the container keeping the necessary information internally
to provide direct access to any of its elements in constant time and with a uniform
sequential interface (through iterators). 
Therefore, deques are a little more complex internally than vectors, but this allows them 
to grow more efficiently under certain circumstances, especially with very long sequences,
where reallocations become more expensive.
	
	*/
	

	return 0;
}