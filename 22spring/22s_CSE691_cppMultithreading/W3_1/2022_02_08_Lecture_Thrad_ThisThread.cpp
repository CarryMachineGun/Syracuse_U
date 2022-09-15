
//thread and this thread  inside thread
#include <iostream>
#include <thread>
#include <chrono> //optional for vs2022
#include <atomic>

using namespace std;
using namespace chrono;

//thread::id ID;


atomic<bool> Flag{ false };

void f1(thread::id ID) {
	cout << this_thread::get_id() << endl;
	if (this_thread::get_id() == ID) cout << "this is the main thread" << endl;
	else cout << "this thread is not main thread" << endl;

	this_thread::sleep_for(chrono::seconds(1));//will pause for 1 second


	auto Time1{ chrono::system_clock::now() };//auto is   chorno::system_clock::time_point

	this_thread::sleep_until(Time1 + chrono::seconds(1)); //pause until a timepoint

	do {

		this_thread::yield();

	} while (chrono::system_clock::now() < Time1 + chrono::seconds(3));


	// while (!Flag) {//this will cause infinite loop.

	// 	this_thread::yield();
	// }

}



int main() {



	thread::id ID{ this_thread::get_id() };
	cout << ID << endl;
	cout << this_thread::get_id() << endl;
	cout << thread::hardware_concurrency() << endl;// static function in class thread

	thread T1{ f1, ID };
	thread T2{ f1, ID };
	T1.swap(T2);

	cout << T1.hardware_concurrency() << endl;

	cout << T1.get_id() << endl;

	thread T3;
	T3 = thread{ f1, ID };//move assignment

	thread T4;
	//T4 = T3;  Error.
	T1.join();
	cout << "A: " << T1.joinable() << endl;//0
	T2.detach();
	T3.join();
	f1(ID);
	return 0;
}