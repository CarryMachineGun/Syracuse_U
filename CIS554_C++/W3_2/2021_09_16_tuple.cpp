//tuple
#include <iostream>
#include <tuple>
#include <string>

using namespace std;


int main() {
	tuple<int, string, int> t1{ 5, "Apple", 24 };
	cout << get<0>(t1) << " " << get<1>(t1) << " " << get<2>(t1) << endl;
	pair<int, string> P1{ 8, "Orange" };
	cout << P1.first << " " << P1.second << endl;

	return 0;
}