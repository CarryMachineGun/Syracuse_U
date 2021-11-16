
#include <iostream>
#include <unordered_set>
#include <set>
#include <vector>
#include <list>

using namespace std;



int main() {
	unordered_set<int> S1{ 1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,
		31,32,33,34,35,36,37,38,39,40 };
	for (auto& i : S1) cout << i << " ";
	cout << endl;
	cout << "bucket size : " << S1.bucket_count() << endl;
	for (unsigned i = 0; i < S1.bucket_count(); ++i) {
		cout << "bucket number " << i << " size = " << S1.bucket_size(i) << " :  ";
		auto it = S1.begin(i);
		while (it != S1.end(i)) { cout << *it << " "; it++; }
		cout << endl;
	}

	cout << *S1.find(15) << endl;//S1.find(15); returns a iterator pointing to the locaiton for key 15, which is not bucket address

	return 0;
}