
//Monte Carlo Simulation
#include <iostream>
#include <vector>
#include <thread>

using namespace std;

class Timer {
public:

		chrono::system_clock::time_point Begin, End;
		chrono::system_clock::duration Runtime;
		Timer() {
			Begin = chrono::system_clock::now();
		}
		~Timer() {
			End = chrono::system_clock::now();
			Runtime = End - Begin;
			cout << "Runtime = " << chrono::duration_cast<chrono::milliseconds>(Runtime).count() << " ms" << endl;
		}
};


void walk(int w1, int w2, int n, vector<float>& V) {
	for (int i = w1; i <= w2; ++i) {
		int sum{ 0 };
		for (int j = 0; j < n; ++j) {
			int x{ 0 }, y{ 0 };
			for (int k = 0; k < i; ++k) {
				int p{ rand() % 4 };
				switch (p) {
				case 0: ++x; break;
				case 1: ++y; break;
				case 2: --x; break;
				case 3: --y; break;
				}
			}
			sum += (abs(x) + abs(y));
		}
		V[i] = float(sum) / n;
	}


}

int main() {
	vector<float> V(30);

	int n{ 100000};

	{
		Timer tm1;
		//walk(10, 29, n, V);
		thread T1{ walk, 10, 14, n, ref(V) };
		thread T2{ walk, 15, 19, n, ref(V) };
		thread T3{ walk, 20, 24, n, ref(V) };
		walk(24, 29, n, V);
		T1.join();
		T2.join();
		T3.join();
	}

	//for (int i = 10; i < 30; ++i) {

	//	cout << "Walking " << i << " blocks will give it average distance of " << V[i] 
	//		<< " blocks from the starting point." << endl;
	//}

	return 0;
}
