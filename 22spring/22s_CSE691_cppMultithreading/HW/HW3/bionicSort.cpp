#include <iostream>
#include <vector>
#include <thread>
#include <list>
#include <fstream>
#include <complex>
#include <math.h>
using namespace std;

void bionicSort(vector<int> &A,int l,int r,bool dir) {
	if (l >= r) return;
	int tmid = l + (r - l) / 2;
	int mid = (r - l) / 2;
	if (dir == true) { //handle up half
		for (int i = l; i <= l+mid; ++i) {
			if (A[i] > A[i + mid + 1]) swap(A[i], A[i+mid+1]);
		}
	}
	else {  //handle down half
		for (int i = r; i >= r-mid; --i) {
			if (A[i] > A[i-mid-1]) swap(A[i], A[i-mid-1]);
		}
	}
	bionicSort(A, l, tmid, dir);
	bionicSort(A, tmid + 1, r, dir);
}


void merge(vector<int>& A, int l, int r, bool dir) {
	if (l >= r) return;  //out of bound
	int mid = l + (r - l) / 2;
	
	//do merge here
	merge(A, l, mid, true);  //true down
	merge(A, mid + 1, r, false); //false up

	//then do bionic sort here
	bionicSort(A, l, r, dir);
}

void prehandle(vector<int>& A, int l, int r, bool dir) {
	int mid = (r - l) / 2;
	if (dir == true) { //handle up half
		for (int i = l; i <= l+mid; ++i) {
			if (A[i] > A[i + mid + 1]) swap(A[i], A[i+mid+1]);
		}
	}
	else {  //handle down half
		for (int i = r; i >= r-mid; --i) {
			if (A[i] > A[i-mid-1]) swap(A[i], A[i-mid-1]);
		}
	}
}

int main() {
	int n{ 1024 };
	vector<int> A;
	for (int i = 0; i < n; ++i) {
		A.emplace_back(rand() % 10000);
	}
	//do code here
	//single thread
	//merge(A, 0, A.size() - 1, true);
	int N = A.size();

	//do fourthhread here
	//4 blocks 4 threads
	thread fT1(merge,ref(A),0,N/4-1,true);
	thread fT2(merge,ref(A),N/4,N/2-1,false);
	thread fT3(merge,ref(A),N/2,3*N/4-1,true);
	merge(A,3*N/4,N-1,false);
	fT1.join();
	fT2.join();
	fT3.join();

	//2 blocks 4 threads
	//use bionic sort prehandle first
	int mid = (N - 1) / 2;
	prehandle(A, 0, mid,true);
	prehandle(A, mid+1,N-1, false);
	//multithreadding
	thread bT1(bionicSort, ref(A), 0, N / 4 - 1, true);
	thread bT2(bionicSort, ref(A), N / 4, N / 2 - 1, true);
	thread bT3(bionicSort, ref(A), N / 2, 3 * N / 4 - 1, false);
	bionicSort(A, 3 * N / 4, N - 1, false);
	bT1.join();
	bT2.join();
	bT3.join();

	//1 block 4 threads
	//use bionic sort,prehandle first
	prehandle(A, 0, N - 1, true);
	prehandle(A, 0, mid, true);
	prehandle(A, mid + 1, N - 1, true);
	//multithreading
	thread bfT1(bionicSort, ref(A), 0, N / 4 - 1, true);
	thread bfT2(bionicSort, ref(A), N / 4, N / 2 - 1, true);
	thread bfT3(bionicSort, ref(A), N / 2, 3 * N / 4 - 1, true);
	bionicSort(A, 3 * N / 4, N - 1, true);
	bfT1.join();
	bfT2.join();
	bfT3.join();

	//output
	ofstream out("output.txt");
	for (int i = 0; i < N; i++) {
		out << A[i];
		if (i < N - 1) out << " ";
	}
	out.close();

	return 0;
}
