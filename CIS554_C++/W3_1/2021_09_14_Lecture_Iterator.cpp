//Iterator: a special pointer used inside STL containers
#include <iostream>
#include <vector>
#include <list>
#include <map>
#include <set>
#include <string>

using namespace std;

int main() { 

	vector<int> V1{ 1, 2, 3, 4, 5 };
	vector<int>::iterator it1{ V1.begin() };//begin() return the address of the first elemnt of V1
	auto it2{ V1.begin() + 1 };//points to 2
	cout << *it1 << endl;// 1
	cout << *(it1 + 2) << endl;//3
	it1 = V1.end();//end() will return the address immediately after the last element
	cout << *(V1.end() - 1) <<endl;//5
	for (auto it = V1.begin(); it != V1.end(); ++it) { cout << *it << "  "; }
	cout << endl;
	it2 = find(V1.begin(), V1.end(), 3);// range [  )  left side closed, right side open
	if (it2 != V1.end()) V1.erase(it2);//find will return end() if not found
	for (auto it = V1.begin(); it != V1.end(); ++it) { cout << *it << "  "; }
	cout << endl;

	// list<int> L1{ 11,22,33,44,55 };
	// for (auto it = L1.begin(); it != L1.end(); ++it) { cout << *it << "  "; }
	// cout << endl;
	// //cout << *(L1.begin() + 1) << endl; iterator of list only allow ++it, it++, --it, it++
	// auto it4{ L1.begin() };
	// cout  << *(++it4) << endl;
	// it4 = find(L1.begin(), L1.end(), 33);
	// if (it4 != L1.end()) L1.erase(it4);
	// L1.remove(44);//only list has remove
	// for (auto it = L1.begin(); it != L1.end(); ++it) { cout << *it << "  "; }
	// cout << endl;
	//iterator does not have nullptr

	// map<int, string> M1{ {6, "apple"}, {2, "Banana"}, {4, "strawberry"},{5, "orange"} };
	// auto it5{ M1.begin() };
	// for (auto it = M1.begin(); it != M1.end(); ++it) {

	// 	cout << it->first << " " << it->second << "   ";
	// }
	// cout << endl;
	// it5 = M1.find(4);
	// if (it5 != M1.end()) M1.erase(it5);//erase based on iterator
	// M1.erase(2);//erase based on key ; will do nothing if not found
	// for (auto it = M1.begin(); it != M1.end(); ++it) {

	// 	cout << it->first << " " << it->second << "   ";
	// }
	// cout << endl;


	// return 0;
}