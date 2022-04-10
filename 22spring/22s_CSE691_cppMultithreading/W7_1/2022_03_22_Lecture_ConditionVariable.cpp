
#include <iostream>
#include <thread>
#include <vector>
#include <mutex>
#include <fstream>
#include <condition_variable>

using namespace std;

mutex m1, m2;
condition_variable cv1;
bool Flag{ false };

void Race(int id) {
	unique_lock<mutex> UL1(m1);
	while (!Flag) cv1.wait(UL1);//wait_for, wait_until
	// while (!Flag) cv1.wait();//wait_for, wait_until
	cout << "Thread " << id << endl;
	// cv1.notify_one();

}

void Start() {
	this_thread::sleep_for(chrono::microseconds(100));
	unique_lock<mutex> UL1(m1);
	Flag = true;
	cv1.notify_one();//notify_one
	//some additional work
}


int main() {
	vector<thread> V;
	for (int i = 0; i < 10; ++i) {
		V.emplace_back(Race, (i + 1));
	}
	Start();
	for (auto& i:V) i.join();


	unique_lock<mutex> UL2(m2);
	unique_lock<mutex> UL3 = move(UL2);
	UL2 = move(UL3);
	return 0;
}