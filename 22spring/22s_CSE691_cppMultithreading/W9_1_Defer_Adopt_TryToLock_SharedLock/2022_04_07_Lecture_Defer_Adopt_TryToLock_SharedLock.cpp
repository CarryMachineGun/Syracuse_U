
#include <iostream>
#include <thread>
#include <mutex>
#include <vector>
#include <shared_mutex>
#include <memory>

using namespace std;
mutex m1, m2, m3;


class myClass {
	mutable shared_mutex Lock;
	mutable int A;
	mutable mutex m1;
public:
	myClass(int i) { A = i; }
	myClass() { A = 0; }
	void read_A() const {
		shared_lock<shared_mutex> SG(Lock);
		this_thread::sleep_for(chrono::milliseconds(20));
		lock_guard<mutex> LG(m1);
		cout << A << endl;
	}
	void inc_A() const {
		unique_lock<shared_mutex> UG(Lock);
		this_thread::sleep_for(chrono::milliseconds(10));
		++A;	
		cout << A << endl;

	}
	void dec_A() const {
		unique_lock<shared_mutex> UG(Lock);
		this_thread::sleep_for(chrono::milliseconds(7));
		--A;
		cout << A << endl;
	}
};


int main() {
	//std::lock
	/*
	lock(m1, m2, m3); //there is no corresponding std::unlock
	m1.unlock();
	m2.unlock();
	m3.unlock();
	*/
	{
		scoped_lock(m1, m2, m3);//RAII; need at least 2017 C++
		//unlock(m1, m2, m3);
	}

	//defer_lock, adopt_lock, try_to_lock for unique_lock and lock_guard (only adopt_lock)
	{
		m1.lock();
		lock_guard<mutex> LG(m1, adopt_lock);//m1 is already locked;  
		//adopt_lock will prevent running m1.lock() again.  LG is now associated with m1, or is managing m1.
		//m1.unlock() is no longer needed

		//The concept is similar to the following smart pointer example.
	}
	int* p1{ new int {34} };

	shared_ptr<int> sp1{ p1 };

	sp1.reset();//object 34 will be deleted automatically

	m1.lock();
	unique_lock<mutex> UG1(m1, adopt_lock);

	unique_lock<mutex>  UG2(m2, defer_lock);//UG2 is associated with m2; it does not run m2.lock()

	UG2.lock();

	/*
	When running with adopt_lock, the thread  already owns the mutex.  the purpose is to avoid running lock() twice.
	When running with defer_lock, the thread does not own the mutex.  
	
	*/

	m3.lock();
	unique_lock<mutex> UG3(m3, try_to_lock);//If UG3 does not own m3, then it cannot unlock() m3.unlock() will be needed
	//if (UG3.owns_lock()) cout << "UG3 owns m3" << endl;
//	if (!UG3) cout << "UG3 does not own m3" << endl;

	//m3.unlock();

	//m4.try_lock()

	mutex m5;
	unique_lock<mutex> UG5(m5);
	unique_lock<mutex> UG6 = move(UG5);//UG5 is no longer associated with m5
	//Thraed1 = move(Thread2);

	mutex m8;
	m8.lock();
	unique_lock<mutex> UG10(m8, try_to_lock);

	unique_lock<mutex> UG11{ move(UG10) };
	if (!UG11) cout << "UG11 does not own m8" << endl;
	m3.unlock();
	m8.unlock();


	vector<thread> V1;
	vector<thread> V2;
	vector<thread> V3;
	myClass M1;
	for (int i = 0; i < 10; ++i) V1.emplace_back(&myClass::read_A, &M1);
	for (int i = 0; i < 3; ++i) V2.emplace_back(&myClass::inc_A, &M1);
	for (int i = 0; i < 3; ++i) V3.emplace_back(&myClass::dec_A, &M1);
	for (auto& i : V1) i.join();
	for (auto& i : V2) i.join();
	for (auto& i : V3) i.join();

	return 0;
}