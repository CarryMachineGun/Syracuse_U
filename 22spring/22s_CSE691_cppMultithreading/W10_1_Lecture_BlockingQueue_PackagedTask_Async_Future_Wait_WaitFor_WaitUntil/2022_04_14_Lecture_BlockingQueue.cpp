
//Blocking shared Resource
#include <iostream>
#include <mutex>
#include <thread>
#include <condition_variable>
#include <vector>
#include <queue>

using namespace std;
mutex m2;

class Q {
	mutex m1;
	queue<int> Queue;
	condition_variable cv1, cv2;

public:
	void Push(int i) {
		unique_lock<mutex> UG(m1);
		while (Queue.size() == 5) cv1.wait(UG);
		Queue.push(i);
		cv2.notify_one();
	}

	int Pop() {

		unique_lock<mutex> UG(m1);
		while (Queue.empty()) cv2.wait(UG);
		int i1{ Queue.front() };
		Queue.pop();
		cv1.notify_one();
		return i1;
	}

};

void PUSH(Q& q, int id, int i) {
	q.Push(i);
	lock_guard<mutex> LG(m2);
	cout << "ID " << id << " Push " << i << endl;
}

void POP(Q& q, int id) {
	int i1{ q.Pop() };
	lock_guard<mutex> LG(m2);
	cout << "ID " << id << " Pop " << i1 << endl;

}

int main() {
	Q q;
	vector<thread> V1;
	vector<thread> V2;
	for (int i = 0; i < 10; ++i) V1.emplace_back(PUSH, ref(q), i + 1, i * i);
	for (int i = 0; i < 10; ++i) V2.emplace_back(POP, ref(q), i + 1);
	for (auto& i : V1) i.join();
	for (auto& i : V2) i.join();
	return 0;
}