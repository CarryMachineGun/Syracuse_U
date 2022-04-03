
#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>
#include <vector>
#include <sstream>

using namespace std;
using namespace literals::chrono_literals;
using namespace chrono;


timed_mutex tm1;
mutex m1;
//int count{ 0 };

void f1(int id) {
	ostringstream Out;
	for (int i = 0; i < 5; ++i) {
		auto tp1{ system_clock::now() };
		if (tm1.try_lock_until(tp1 + 100ms)) {
		//if (tm1.try_lock_for(100ms)) {
			Out << "Success!  ";
			this_thread::sleep_for(100ms);
			tm1.unlock();
		}
		else {
			Out << "Failure!  ";
		}
		this_thread::sleep_for(100ms);
	}
	lock_guard<mutex> LG{ m1 };
	cout << "[" << id << "]:" << endl;
	cout << Out.str() << endl;
}

int main() {
	vector<thread> T;
	for (int i = 0; i < 5; ++i) {
		T.emplace_back(f1, (i + 1));
	}

	for (auto& i : T) i.join();

	return 0;
}