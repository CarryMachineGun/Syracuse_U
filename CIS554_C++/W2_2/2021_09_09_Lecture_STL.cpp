
//Standard Template Library (STL): containers such as vector, list, map, set, etc.
#include <iostream>
#include <vector>
#include <list>
#include <map>
#include <stack>
#include <queue>
#include <set>
#include <string>

using namespace std;

int main() {

	//all STL containers elements come with default initialized values
	vector<int> Va1(10);//10 elements, all initialized to 0
	vector<int> Va2(10, 5); //10 elements, all initialized to 5
	vector<int> Va3{ 1,2,3,4,5 };//5 elements:  1 2 3 4 5

	for (size_t i = 0; i < Va3.size(); ++i) {//size() will return a non-negative int, size_t, of 5

		cout << Va3[i] << " ";

	}

	//cout << Va3[10];  Error! Vector will check for out-of-bound errors
	cout << endl;
	//"For each" for loop
	for (int i : Va3) { cout << i << " "; i++; }//1 2 3 4 5  call by value
	cout << endl;

	for (int i : Va3) { cout << i << " ";  } //1 2 3 4 5
	cout << endl;
	for (int &i : Va3) { cout << i << " "; i++; } // 1 2 3 4 5  call by reference
	for (auto i : Va3) { cout << i << " "; } //2 3 4 5 6

	Va3.push_back(20);//add 20 to the end of vector
	Va3.pop_back();
	if (Va3.empty()) cout << "It is empty " << endl;
	Va2.clear();// Reset the size of vector to 0
	Va3.resize(4); //2 3 4 5
	Va3.resize(8);//2 3 4 5 0 0 0 0
	Va3.resize(10, 9); //2 3 4 5 0 0 0 0 9 9
	cout << Va3.front() << " LOLOLOLOL " << Va3.back() << endl;//1 9   first and last element

	list<int> L1{ 1,2, 3,4,5 };//Other ways for vector also apply
	L1.push_back(6);
	L1.pop_back();
	//two new functions
	L1.push_front(100);
	L1.pop_front();

	//cout << L1[3] ; Error!;  List does not support subscript

	//empty(), clear(), size(), clear(), front(), back(), also available for list

	map<int, string> M1{ {4, "Dave"}, {3, "John"}, {5, "Akara"}, {3, "Chen"} };// {key, value}
	for (pair<int, string> i : M1) { cout << i.first << " " << i.second << "   "; };
	//3 John   4 Dave   5 Akara
	//All map elements will be automatically sorted based on key (first value)
	
	M1[20] = "Mary";//{20, "Mary"} has been added to map
	//{3, "Chen"} is ignored beacause map does not allow duplicated key
	
	M1[3] = "Chen";//override {3, "John"} with {3, "Chen"}
	cout << endl;
	for (auto i : M1) { cout << i.first << " " << i.second << "   "; };
	M1.insert({ 15,"Bob" });
	M1.insert({ 3, "Nancy"});

	cout << endl;
	for (auto i : M1) { cout << i.first << " " << i.second << "   "; };
	//3 Chen   4 Dave   5 Akara   15 Bob   20 Mary
	//insert will ignore duplicate key

	stack<int> S1;//no simple way to initialize stack values; first in last out
	S1.push(2);
	S1.push(3);
	for (int i : {4, 5, 6, 7, 8, 9}) { S1.push(i); }
	cout << endl;
	while (!S1.empty()) {//while S1 is not empty
		cout << S1.top() << " ";
		S1.pop();
	}


	queue<int> Q1;//no simple way to initialize stack values; first in first out
	Q1.push(2);
	Q1.push(3);
	for (int i : {4, 5, 6, 7, 8, 9}) { Q1.push(i); }
	cout << endl;
	while (!Q1.empty()) {//while S1 is not empty
		cout << Q1.front() << " ";
		Q1.pop();
	}

	vector<list<int>> V2{ {1, 2, 3},{4,5},{6,7,8,9} };
	cout << endl;
	cout << "[ ";
	for (auto i : V2) {
		cout << "< ";
		for (auto j : i) {
			cout << j << " ";
		}
		cout << ">  ";

	}
	cout << "]" << endl;

	list<int*>* pL1{ new list<int*> { new int{3}, new int{5}, new int{11} } };
	//* -> .  new

	//map<int, map<int, vector<int> *>>







	


	return 0;
}