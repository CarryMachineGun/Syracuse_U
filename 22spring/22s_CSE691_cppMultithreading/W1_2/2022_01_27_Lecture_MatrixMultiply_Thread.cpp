
#include <iostream>
#include <thread>
#include <vector>
#include <chrono> //optional for VS

using namespace std;
using namespace chrono;

class Timer {
public:
	chrono::system_clock::time_point Begin, End;
	system_clock::duration Runtime;
	Timer() {//constructor
		Begin = system_clock::now();
	}
	~Timer() {
		End = system_clock::now();
		Runtime = End - Begin;
		cout << "Runtime = " << chrono::duration_cast<chrono::milliseconds>(Runtime).count() << endl;
	}
};


void MatMultiply(vector<vector<int>>& M1, vector<vector<int>>& M2, vector<vector<int>>& M3,
	int r1, int r2, int c1, int c2);




int main() {
	int n1{ 200}, n2{ 220 }, n3{ 360 };
	vector<vector<int>> A(n1, vector<int>(n2, 1));//n1 x n2 matrix, with values 1
	vector<vector<int>> B(n2, vector<int>(n3, 1));//n2 x n3 matrix, with values 1
	vector<vector<int>> C(n1, vector<int>(n3));//n1 x n3 matrix, with values 0

	/*for (auto& i : A) {
		for (auto& j : i) cout << j << " ";
		cout << endl;
	}*/
	{
		Timer tm1;
		//MatMultiply(A, B, C, 0, n1 - 1, 0, n3 - 1);

		//thread T1{ MatMultiply,ref(A), ref(B), ref(C), 0, n1 / 2 - 1,  0, n3 / 2 - 1 };
		//thread T2{ MatMultiply,ref(A), ref(B), ref(C), 0, n1 / 2 - 1,  n3 / 2 , n3 - 1 };
		//thread T3{ MatMultiply,ref(A), ref(B), ref(C), n1 / 2 , n1 - 1,  0, n3 / 2 - 1 };
		//MatMultiply(A, B, C, n1 / 2, n1 - 1, n3 / 2, n3 - 1);

		// thread T1{ MatMultiply,ref(A), ref(B), ref(C), 0, n1 / 4 - 1,  0, n3 - 1 };
		// thread T2{ MatMultiply,ref(A), ref(B), ref(C), n1 / 4 , n1/2-1, 0 , n3 - 1 };
		// thread T3{ MatMultiply,ref(A), ref(B), ref(C), n1 / 2 , n1/4*3 - 1,  0, n3 - 1 };
		// MatMultiply(A, B, C, n1 / 4*3, n1 - 1, 0, n3 - 1);

		thread T1{ MatMultiply,ref(A), ref(B), ref(C), 0, n1 / 2 - 1,  0, n3 / 2 - 1 };
		thread T2{ MatMultiply,ref(A), ref(B), ref(C), n1 / 2 , n1 - 1, 0 , n3 / 2 - 1 };
		thread T3{ MatMultiply,ref(A), ref(B), ref(C), 0 , n1 / 2 - 1,  n3 / 2, n3 - 1 };
		MatMultiply(A, B, C, n1 / 2, n1 - 1, n3 / 2, n3 - 1);

		T1.join();
		T2.join();
		T3.join();
	}
	/*cout << endl;

	for (auto& i : C) {
		for (auto& j : i) cout << j << " ";
		cout << endl;
	}*/
	return 0;
}

void MatMultiply(vector<vector<int>>& M1, vector<vector<int>>& M2, vector<vector<int>>& M3,
	int r1, int r2, int c1, int c2) {

	for (int i = r1; i <= r2; ++i) {
		for (int j = c1; j <= c2; ++j) {
			for (size_t k = 0; k < M2.size(); ++k) {
				M3[i][j] += M1[i][k] * M2[k][j];
			}

		}
	}
}