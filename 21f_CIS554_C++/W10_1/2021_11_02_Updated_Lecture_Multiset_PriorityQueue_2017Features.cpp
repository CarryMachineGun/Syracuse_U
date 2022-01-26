//multiset, multimap, priority_queue, etc.
//Need constructor for ThreeD and myCompare functor <= leads to errors (need to change it to <)
#include <iostream>
#include <queue>  //for both queue and priority_queue
#include <set> //for both set and multiset
#include <map>  //for both map and multimap
#include <string>
#include <vector>
#include <list>
#include <array>
#include <algorithm>//for_each
#include <memory>

using namespace std;
class ThreeD {
public:
	int ht;
	int wid;
	int dep;
	ThreeD(int i, int j, int k): ht(i),wid(j), dep(k){}
	int vol() const { return ht * wid * dep; }
	bool operator<(const ThreeD& t) const { return vol() < t.vol(); }
	//bool operator<(const ThreeD& t) const { return vol() <= t.vol(); } //all 6 will be different
	//a<b ? F  && b<a ? F  we have a == b
};

class myCompare {
public:
	bool operator()(const ThreeD& t1, const ThreeD& t2) const { return t1.vol() < t2.vol(); }
	bool operator()(int i, int j) const { return i % 2 < j % 2; }

};

ostream& operator<<(ostream& str, const ThreeD& t) {
	str << "(" << t.ht << ", " << t.wid << ", " << t.dep << ")";
	return str;
}


int main() {

	ThreeD t1{ 4,1,32 }, t2{ 9,2,3 }, t3{ 2, 3, 4 }, t4{ 4,5,6 }, t5{ 2,12, 5 }, t6{ 4,1,30 };
	set<ThreeD> S1{ t1, t2, t3, t4, t5, t6 };
	for (auto& i : S1) { cout << i << " "; }
	cout << endl;


	set<ThreeD, myCompare> S2{ t1, t2, t3, t4, t5, t6 };
	for (auto& i : S2) { cout << i << " "; }
	cout << endl;

	//vector v1{ 1,2,3,4,5 };
	//list l1{ 1,2,3,4,5 };
	map<int, int> m1{ {5, 5}, {5,5} };
	//array a1{ 1,2,3,4 };

	multiset<ThreeD> S3{ t1, t2, t3, t4, t5, t6 };
	for (auto& i : S3) { cout << i << " "; }
	cout << endl;

	auto ret = S3.equal_range({ 20, 1, 6 });//equal_range applies to multimap as well
	//ret will be a pair of iterators  [ ...)

	cout << *(ret.first) << endl;

	for_each(ret.first, ret.second, [](auto i) {cout << i << " "; });
	cout << endl;
	auto ret1 = S3.equal_range({ 21, 1, 6 });
	cout << *(ret1.second) << endl;

	priority_queue<int> PQ1;//max heap  using default less<int>
	for (auto& i : { 11,2,33,4,5 }) { PQ1.push(i); }
	while (!PQ1.empty()) {
		cout << PQ1.top() << " ";
		PQ1.pop();
	}
	cout << endl;
	priority_queue<int, vector<int>, greater<int>> PQ2;//min heap 
	for (auto& i : { 11,2,33,4,5 }) { PQ2.push(i); }
	while (!PQ2.empty()) {
		cout << PQ2.top() << " ";
		PQ2.pop();
	}

	cout << endl;
	priority_queue<int, vector<int>, myCompare> PQ3;//min heap 
	for (auto& i : { 11,2,33,4,5 }) { PQ3.push(i); }
	while (!PQ3.empty()) {
		cout << PQ3.top() << " ";
		PQ3.pop();
	}


	shared_ptr<ThreeD> sp1{ make_shared<ThreeD>(1,2,3) };

	pair<int, string> P{ 5, "Apple" };

	vector<int> V6{ 1,2,3,4,5 };

	map<int, string> M5{ {5, "Apple"}, {4, "Grape"} };
	for (auto& i : M5) { cout << i.first << " " << i.second << " "; }
	cout << endl;
	map<int, string> M6{ {5, "Apple"}, {4, "Grape"} };
	//for (auto [i, j] : M6) { cout << i << " " << j << " "; }//2017
	cout << endl;












	return 0;
}