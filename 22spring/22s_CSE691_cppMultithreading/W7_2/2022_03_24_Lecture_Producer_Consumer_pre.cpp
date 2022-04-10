//Producer-Consumer
#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <vector>
#include <chrono>
#include <atomic>


using namespace std;
mutex m1, m2;
condition_variable cv1, cv2;
vector<int> V;
atomic<int> c_wait {0}, p_wait {0};


void Consumer(int id);
void Producer(int id);


int main() {
	vector<thread> C;
	vector<thread> P;
	
	for (int i = 0; i < 2; ++i) C.emplace_back(Consumer, i + 1);
	for (int i = 0; i < 12; ++i) P.emplace_back(Producer, i + 1);

	for (auto& i : C) i.join();
	for (auto& i : P) i.join();

	return 0;
}
void Consumer(int id) {
	unique_lock<mutex> UG1(m1);//for accessing V
	while (V.size() < 6) cv1.wait(UG1);//a producer needs all 6 elements to process.
	//do something
	this_thread::sleep_for(chrono::milliseconds(5));
	V.clear();
	{
		lock_guard<mutex> LG1(m2);
		cout << "Consumer " << id << " V.size() = " << V.size() << " c_wait = " << c_wait << " p_wait = " << p_wait << endl;
	}
	cv2.notify_all();//OK
}
void Producer(int id) {
	unique_lock<mutex> UG1(m1);
	while (V.size() == 6) cv2.wait(UG1);//the maximum capacity of V is 6
	//do something
	this_thread::sleep_for(chrono::milliseconds(5));
	V.push_back(id);
	{
		lock_guard<mutex> LG1(m2);
		cout << "Producer " << id << " V.size() = "<< V.size() << " c_wait = " << c_wait << " p_wait = " << p_wait<<endl;
	}
	cv1.notify_one();
}