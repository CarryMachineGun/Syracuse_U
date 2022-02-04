
//Monte Carlo Simulation
#include <iostream>
#include <vector>
#include <thread>

using namespace std;


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
	walk(10, 29, n, V);
	for (int i = 10; i < 30; ++i) {

		cout << "Walking " << i << " blocks will give me average distance of " << V[i] 
			<< " blocks from the starting point." << endl;
	}



	return 0;
}
