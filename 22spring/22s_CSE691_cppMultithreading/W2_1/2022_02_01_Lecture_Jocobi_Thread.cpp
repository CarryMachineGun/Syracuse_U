//https://en.wikipedia.org/wiki/Jacobi_method
//Solving Cx=b linear systems using Jacobi method.
#include <iostream>
#include <vector>
#include <thread>
using namespace std;




void solve(vector<float>& A, vector<float>& B, vector<vector<float>>& C, vector<float>& b, int i1, int i2) {
    for (int i = i1; i <= i2; ++i) {
        B[i] = b[i];
        for (size_t j = 0; j < C[1].size(); ++j) {
            if (j == i) continue;
            B[i] -= (A[j] * C[i][j]);
        }
        B[i] /= C[i][i];
    }
}


int main()
{

    /*
    float q {3.56f};
    float p {3.5};//double 3.5 will be typecast to float 3.5
    */
    vector<float> A(4), B(4);
    vector<vector<float>> C{ {10., -1., 2., 0.},
        {-1., 11., -1., 3.},
        {2., -1., 10., -1.},
        {0.0, 3., -1., 8.} };
    vector<float> b{ 6, 25, -11, 15 };
    float diff;
    while (true) {
        thread T1;
        T1 = thread(solve, ref(A), ref(B), ref(C), ref(b), 2, 3);//right side is an anonymous thread
        //assign in thread is always move assignment, Rvalue assignment

        solve(ref(A), ref(B), ref(C), ref(b), 0, 1);
        T1.join();
        diff = 0;
        for (size_t i = 0; i < A.size(); ++i) {
            diff += abs(A[i] - B[i]);
        }
        if (diff < 0.000001) break;
        A = B;
    }
    for (float i : B) cout << i << " ";

    cout << endl;

    return 0;
}