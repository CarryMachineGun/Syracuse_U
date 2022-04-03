
#include <iostream>
#include<thread>
#include <mutex>
#include <chrono>
#include <vector>

using namespace std;
using namespace literals::chrono_literals;
using namespace chrono;

class myClass {
private:
	mutex m1;
	int count;
public:
	myClass() { count = 1; }
	void f1(int id) {
		lock_guard<mutex> LG{ m1 };
		this_thread::sleep_for(50ms);
		for (int i = 0; i < 1000; ++i) {
			++count;
		}
	}
};


int main() {
	myClass mc1;
	vector<thread> T;
	for (int i = 0; i < 5; ++i) {
		T.emplace_back(&myClass::f1, &mc1, (i + 1));
	}
	for (auto& i : T) i.join();


	return 0;
}