
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

int Count{ 0 };//
mutex m1, m2;

void f1(int id) {
	ostringstream Out;
	for (int i = 0; i < 10; ++i) {
		if (m1.try_lock()) {
			Count++;
			Out << "Success!" << " Count = " << Count << "  ";
			this_thread::sleep_for(100ms);
			m1.unlock();

		}
		else {
			//Count--;
			//m2.lock();
			Out << " Failure!" << "  ";
			this_thread::sleep_for(50ms);
			//m2.unlock();
		}
	}
	lock_guard<mutex> LG{ m2 };//move assignment
	cout << "Thread[" << id << "]:" << endl;
	cout << Out.str() << endl;
	//m2.unlock(); Will cause error in VS.
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