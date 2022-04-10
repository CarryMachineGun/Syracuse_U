
#include <iostream>
#include <thread>
#include <mutex>
//#include <chrono>

using namespace std;
using namespace chrono;
using namespace literals::chrono_literals;

mutex m1;
int success_count{ 0 };
int failure_count{ 0 };

void task_a() {
	this_thread::sleep_for(100ms);
	while (true) {
		if (m1.try_lock()) {
			cout << "Success_count = " << success_count << endl;
			m1.unlock();
			return;
		}
		else {
			++failure_count;
			cout << "failure_count = " << failure_count << endl;

		}

		this_thread::sleep_for(100ms);

	}
}
void task_b() {
	m1.lock();
	++success_count;

	this_thread::sleep_for(545ms);//545 is the cutoff time
	m1.unlock();
}

int main() {

	thread  T1{ task_a };
	thread T2{ task_b };
	T1.join();
	T2.join();

	return 0;
}