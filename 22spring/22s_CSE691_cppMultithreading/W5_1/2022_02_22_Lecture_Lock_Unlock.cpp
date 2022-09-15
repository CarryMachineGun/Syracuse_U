
#include <iostream>
#include <thread>//optional with mutex in VS2022
#include <mutex>
#include <vector>
#include <chrono>
#include <fstream>

using namespace std;
using namespace chrono;
using namespace literals::chrono_literals;

int Count{ 0 };//
mutex m1;

void f1(int id) {

	for (int i = 0; i < 50; ++i) {
		// m1.lock();
		Count++;
		cout << "Thread " << id << " increase Count " << " Count = " << Count << endl;
		// this_thread::sleep_for(100ms);
		// m1.unlock();
	}
}

int main() {
	//vector<int> V{ 1,2,3,4,5 };
	//ofstream Out("output_data.txt");//automatically Out.open();
	//for (auto& i : V) Out << i << endl;
	//Out.close();
	vector<thread> T;
	for (int i = 0; i < 5; ++i) {
		T.emplace_back(f1, (i + 1));
	}
	for (auto& i : T) i.join();
	return 0;
}