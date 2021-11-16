
#include <iostream>
#include <map>
#include <set>
#include <vector>
#include <list>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>


using namespace std;

class myHashClass {

public:

	size_t operator()(const vector<int>& v) const;
	size_t operator()(const unordered_set<int>& s) const;
	size_t operator()(const unordered_set<unordered_set<int>>& s) const;
};
class myEqualClass {
public:
	bool operator()(const vector<int>& v1, const vector<int>& v2) const;
	bool operator()(const unordered_set<int>& s1, const unordered_set<int>& s2) const;
	bool operator()(const unordered_set<unordered_set<int>>& s1, const unordered_set<unordered_set<int>>& s2) const;
};

size_t myHashClass::operator()(const vector<int>& v) const {
	int sum{ 0 };
	for (auto& i : v) sum += i;
	return hash<int>()(sum);
}

bool myEqualClass::operator()(const vector<int>& v1, const vector<int>& v2) const {

	int sum1{ 0 };
	for (auto& i : v1) sum1 += i;
	int sum2{ 0 };
	for (auto& i : v2) sum2 += i;
	return sum1 == sum2;
}


size_t myHashClass::operator()(const unordered_set<int>& s) const {
	int sum{ 0 };
	for (auto& i : s) sum += i;
	return hash<int>()(sum);
}


bool myEqualClass::operator()(const unordered_set<int>& s1, const unordered_set<int>& s2) const {
	int sum1{ 0 };
	for (auto& i : s1) sum1 += i;
	int sum2{ 0 };
	for (auto& i : s2) sum2 += i;
	return sum1 == sum2;
}

size_t myHashClass::operator()(const unordered_set<unordered_set<int>>& s) const {
	int sum{ 0 };
	for (auto& i : s) {
		for (auto& j : i) {
			sum += j;
		}
	}
	return hash<int>()(sum);
}

bool myEqualClass::operator()(const unordered_set<unordered_set<int>>& s1, const unordered_set<unordered_set<int>>& s2) const {
	int sum1{ 0 };
	for (auto& i : s1) {
		for (auto& j : i) {
			sum1 += j;
		}
	}
	int sum2{ 0 };
	for (auto& i : s2) {
		for (auto& j : i) {
			sum2 += j;
		}
	}
	return sum1 == sum2;
}
int main() {
	unordered_set<vector<int>, myHashClass, myEqualClass> S1;
	//unordered_set < unordered_set<vector<int>, myHashClass, myEqualClass> > S2;

	unordered_set<int> S3;
	unordered_set<unordered_set<int>, myHashClass, myEqualClass> S4{ {11,2},{3,4} };
	for (auto& i : S4) {
		for (auto& j : i)  cout << j << " ";
	}
	cout << endl;
	unordered_set<unordered_set<int>, myHashClass, myEqualClass> S5{ {13,2},{23,4} };

	//unordered_set< unordered_set<unordered_set<int, hash<int>, equal_to<int>>, myHashClass, myEqualClass>, myHashClass, myEqualClass> S6{ S4, S5 };
	//the above statement does not compili in VS2019


	list<unordered_set<unordered_set<int, hash<int>, equal_to<int>>, myHashClass, myEqualClass>> L1{ S4, S5 };
	cout << endl;
	for (auto& i : L1) {
		for (auto& j : i) {
			for (auto& k : j) {
				cout << k << " ";
			}
		}
		cout << "  ";
	}
	return 0;
}