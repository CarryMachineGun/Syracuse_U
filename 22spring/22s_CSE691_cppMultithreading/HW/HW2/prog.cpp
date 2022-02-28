#include <iostream>
#include <complex>
#include <vector>
#include <thread>
#include <fstream>

using namespace std;

typedef complex<double> cx;
const double PI = 3.1415926536;
const cx J(0, 1);

void myfun(vector<cx> &b, int start, int end)
{
    for (int i = start; i < end; i++)
    {
        int m = 1 << i; 
        int m2 = m >> 1;
        cx w(1, 0);
        cx wm = exp(-J * (PI / m2));

        for (int j = 0; j < m2; ++j)
        {
            for (int k = j; k < b.size(); k += m)
            {
                cx t = w * b[k + m2];
                cx u = b[k];

                b[k] = u + t;
                b[k + m2] = u - t;
            }
            w *= wm;
        }
    }
}

int bitReverse(int x, int log2n)
{
    int reverse_x = 0;

    for (int i = 0; i < log2n; i++)
    {
        reverse_x <<= 1;
        reverse_x |= (x & 1);
        x >>= 1;
    }

    return reverse_x;
}

void fft(vector<cx> &a, vector<cx> &b)
{
    int log2n = 1;

    while (pow(2, log2n) != a.size())
        log2n++;

    // bit reversal of the given array
    for (int i = 0; i < a.size(); i++)
        b[i] = a[bitReverse(i, log2n)];

    thread T1{myfun, ref(b), 1, (log2n - 1) / 4 + 1};
    thread T2{myfun, ref(b), (log2n - 1) / 4 + 1, (log2n - 1) / 2 + 1};
    thread T3{myfun, ref(b), (log2n - 1) / 2 + 1, (log2n - 1) * 3 / 4 + 1};
    myfun(b, (log2n - 1) * 3 / 4 + 1, log2n + 1);
    T1.join();
    T2.join();
    T3.join();

    return;
}

int main()
{
    string line;
    vector<cx> a;
    ifstream in("data.txt");
    ofstream out("output_data.txt");

    if (in.is_open())
    {
        while (getline(in, line, ' '))
        {
            a.push_back(stod(line));
            // cout << a.back() << endl;
        }
        // cout << a.size() << endl;
        in.close();
    }

    vector<cx> b(a.size());

    fft(a, b);

    for(cx &i : b){
        out << i << "\n";
    }

    out.close();

    return 0;
}