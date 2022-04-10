
#include <iostream>
#include <thread>//optional with mutex in VS2022
#include <mutex>
#include <vector>
#include <chrono>
#include <fstream>
#include <sstream>

using namespace std;
using namespace chrono;
using namespace literals::chrono_literals;

class Timer {
public:
	system_clock::time_point Begin, End;
	//system_clock::duration Runtime;
	Timer() { Begin = system_clock::now(); }
	~Timer() { 
		End = system_clock::now();
		cout << "Runtime = " << duration_cast<milliseconds>(End - Begin).count() << " ms" << endl;
	}


};

class myClass {
private:
	recursive_mutex rm1;
public:
	void f1(int id) {
		lock_guard<recursive_mutex> LG(rm1);
		this_thread::sleep_for(50ms);
		cout << "thread[" << id << "] compltes f1" << endl;
	}
	void f2(int id) {
		lock_guard<recursive_mutex> LG(rm1);
		this_thread::sleep_for(30ms);
		for (int i=0; i<5; ++i) f1(id);
		this_thread::sleep_for(30ms);
		cout << "thread[" << id << "] compltes f2" << endl;

	}
	//void f3(int id) {
	//	this_thread::sleep_for(40ms);
	//	lock_guard<recursive_mutex> LG(rm1);
	//	f1(id);
	//	this_thread::sleep_for(30ms);

	//}
};

int main() {
	myClass mc1;
	thread T1{ &myClass::f2, &mc1, 1 };
	thread T2{ &myClass::f2, &mc1, 2 };
	T1.join();
	T2.join();

	return 0;
}