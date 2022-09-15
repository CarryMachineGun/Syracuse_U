
#include <iostream>
#include <thread>
#include <mutex>
#include <vector>
#include <atomic>

using namespace std;
using namespace literals::chrono_literals;

mutex m1; // mutex is a primitive lock mutually exclusive

void f1(int id)
{
	// m1.lock(); //
	for (int i = 0; i < 5000; ++i)
	{
		this_thread::sleep_for(100us);
		m1.lock();//
		cout << "ID = " << id << "  12111111111111"
			 << "  "
			 << " This is a very  very long text" << endl;
		m1.unlock();
	}
	// m1.unlock();
}

void f2(int n, atomic<int> &s)
{

	for (int i = 0; i < n; ++i)
	{
		this_thread::sleep_for(10us); // sleep_for(microseconds(100)
		// m1.lock();
		s = s + 1;

		//++s;
		// m1.unlock();
	}
}

int main()
{
	vector<thread> T;
	for (int i = 0; i < 5; ++i)
	{
		// T.push_back(thread(f1, i));
		T.emplace_back(f1, i);
	}

	for (auto &i : T)
		i.join();

	// int k{ 0 };
	//  atomic<int> k {0};

	// thread T1{ f2, 500, ref(k) };

	// thread T2{ f2, 500, ref(k) };

	// T1.join();
	// T2.join();

	// cout << " k = " << k << endl;

	return 0;
}