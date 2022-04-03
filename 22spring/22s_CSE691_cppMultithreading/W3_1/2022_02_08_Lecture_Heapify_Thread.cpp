
// Heapify
#include <iostream>
#include <vector>
#include <thread>

using namespace std;
using namespace chrono;

class Timer
{
public:
	system_clock::time_point Begin, End;
	Timer() { Begin = system_clock::now(); }
	~Timer()
	{
		End = system_clock::now();
		system_clock::duration Runtime{End - Begin};
		cout << "Runtime = " << duration_cast<milliseconds>(Runtime).count() << " ms"
			 << "\n";
	}
};

void Heapify(vector<int> &T, int i);

int main()
{

	int n{99999};
	vector<int> T(n);
	for (auto &i : T)
		i = rand() % 9999;

	Timer tm1;
	// Heapify(T, 0);
	thread T1{Heapify, ref(T), 1};
	Heapify(T, 2);
	T1.join();
	int k{0}, j;
	while (2 * k + 1 < T.size())
	{
		if (2 * k + 2 >= T.size())
		{
			j = 2 * k + 1;
		}
		else
		{
			j = (T[2 * k + 1] <= T[2 * k + 2]) ? 2 * k + 1 : 2 * k + 2;
		}
		if (T[k] > T[j])
		{
			swap(T[k], T[j]);
			k = j;
		}
		else
			break;
	}

	// for (auto &i : T)
	// {
	// 	cout << i << " ";
	// }
	// cout << endl;

	return 0;
}
void Heapify(vector<int> &T, int i)
{
	if (i < 0 || i >= T.size() || 2 * i + 1 >= T.size())
		return;
	Heapify(T, 2 * i + 1);
	Heapify(T, 2 * i + 2);
	int k{i}, j;
	while (2 * k + 1 < T.size())
	{
		if (2 * k + 2 >= T.size())
		{
			j = 2 * k + 1;
		}
		else
		{
			j = (T[2 * k + 1] <= T[2 * k + 2]) ? 2 * k + 1 : 2 * k + 2;
		}
		if (T[k] > T[j])
		{
			swap(T[k], T[j]);
			k = j;
		}
		else
			break;
	}
}