
#include <iostream>
#include <thread>
#include <vector>
#include <mutex>
#include <fstream>
#include <condition_variable>

using namespace std;

class Record
{
	mutex m1, m2;
	ofstream Out;
	once_flag Flag;

public:
	Record()
	{

		// Out.open("output.txt");
	}

	void Print(int id, int value)
	{

		{

			unique_lock<mutex> UL1(m2, defer_lock);
			// unique_lock<mutex> UL1(m2);
			//....

			UL1.lock();
			// unique_lock<mutex> UL1(m2);
			if (!Out.is_open())
				Out.open("output.txt");
			//...
			//
			UL1.unlock();
			// some work that does not need locking

			UL1.lock();
			// starting here, need locking again
		}
		// call_once(Flag, [&]() {Out.open("output.txt"); });
		lock_guard<mutex> LG1(m1);
		Out << "Thread " << id << " prints value " << value << endl;
	}
	~Record()
	{
		if (Out.is_open())
			Out.close();
	}
};

void f1(int id, int value, Record &rec)
{
	rec.Print(id, value);
}

int main()
{
	vector<thread> V;
	Record rec;
	for (int i = 0; i < 10; ++i)
	{

		V.emplace_back(f1, (i + 1), (i + 1) * (i + 1), ref(rec));
	}
	for (auto &i : V)
		i.join();

	return 0;
}