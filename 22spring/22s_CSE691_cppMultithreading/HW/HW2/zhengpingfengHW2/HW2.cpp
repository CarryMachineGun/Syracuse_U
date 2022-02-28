#include <iostream>
#include <vector>
#include <thread>
#include <list>
#include <fstream>
#include <complex>
#include <math.h>
using namespace std;

#define PI (double)3.1415926536

const complex<double> J{ 0,1 };
//reverse bit
int reverseBit(int n, int b) {
	int rb = 0;
	int p = (int)(log(n + 1) / log(2));

	for (int k = 0; k < p; ++k) {
		rb = (rb << 1) + (b >> k & 1);
	}
	return rb;
}

//Twiddle factor
complex<double> W(int m, int n) {
	complex<double> res = exp(-J * (double)((2 * PI * n) / m));
	return res;
}

//divide by datablocks
void fft(vector<complex<double>>& F, int i1, int i2, int k) {
	for (int i = i1; i <= i2; i++) {
		for (int j = 0; j < (1 << (k - 1)); j++) {
			complex<double> a = F[i * (1 << k) + j];
			complex<double> b = F[i * (1 << k) + j + (1 << (k - 1))];
			complex<double> c = W(1 << k, j);
			F[i * (1 << k) + j] = a + (b * c);
			F[i * (1 << k) + j + (1 << (k - 1))] = a - (b * c);
		}
	}
}

//divide by points(W)
void fft2(vector<complex<double>>& F, int p, int j1, int j2, int k) {
	for (int j = j1; j <= j2; j++) {
		complex<double> a = F[p * (1 << k) + j];
		complex<double> b = F[p * (1 << k) + j + (1 << (k - 1))];
		complex<double> c = W(1 << k, j);
		F[p * (1 << k) + j] = a + (b * c);
		F[p * (1 << k) + j + (1 << (k - 1))] = a - (b * c);
	}
}

int main() {
	int N = -1;
	vector<complex<double>> indata, outdata;
	//read in the data
	ifstream In("data.txt");
	double a;

	while (!In.eof()) {
		In >> a;
		indata.push_back({ a,0 });
		N++;
	}
	In.close();
	vector<complex<double>> curdata(N + 1);

	//reverse the bit
	for (int i = 0; i < N; ++i) {
		curdata[i] = indata[reverseBit(N, i)];
	}

	/*int K = (int)(log(N + 1) / log(2));
	for (int k = 1; k <= K; ++k) {
		int p = (N / (1 << k));
		fft(curdata, 0, p - 1, k);
	}*/

	//do fft
	//K layers of rotation 
	int K = (int)(log(N + 1) / log(2));
	for (int k = 1; k <= K; ++k) {
		int p = (N / (1 << k));
		if (p > 2) {      // >= 4 data blocks
			//divide by data blocks
			thread T1(fft, ref(curdata), p / 4, p / 2 - 1, k);
			thread T2(fft, ref(curdata), p / 2, 3 * p / 4 - 1, k);
			thread T3(fft, ref(curdata), 3 * p / 4, p - 1, k);
			fft(curdata, 0, p / 4 - 1, k);
			T1.join();
			T2.join();
			T3.join();
		}
		else if (p == 2) {  //2 data blocks
			//divide by Point
			thread T1(fft2, ref(curdata), 0, 0, (N / 8) - 1, k);
			thread T2(fft2, ref(curdata), 0, N / 8, (N / 4) - 1, k);
			thread T3(fft2, ref(curdata), 1, 0, (N / 8) - 1, k);
			fft2(curdata, 1, N / 8, (N / 4) - 1, k);
			T1.join();
			T2.join();
			T3.join();
		}
		else {            //1 data block
			//divide by point
			thread T1(fft2, ref(curdata), 0, 0, (N / 8) - 1, k);
			thread T2(fft2, ref(curdata), 0, N / 8, N / 4 - 1, k);
			thread T3(fft2, ref(curdata), 0, N / 4, 3 * N / 8 - 1, k);
			fft2(curdata, 0, 3 * N / 8, N / 2 - 1, k);
			T1.join();
			T2.join();
			T3.join();
		}
	}

	//output the result
	ofstream out("output_data.txt");
	for (int i = 0; i < N; i++) {
		out << curdata[i];
		if (i < N - 1) out << "\n";
	}
	out.close();

	return 0;
}