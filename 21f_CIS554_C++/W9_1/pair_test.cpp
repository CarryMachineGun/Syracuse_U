#include <map>
#include <iostream>

using namespace std;

int main(){

	map<int, int> hashmap{{1,2}, {5,6}};
	pair<int, int> p1{1,2};
	pair<int, int> p2{p1};
	pair<int, int> p3;

	cout << p1.first << endl;
	cout << p2.first << endl;
	cout << p3.first << endl;

    return 0;
}