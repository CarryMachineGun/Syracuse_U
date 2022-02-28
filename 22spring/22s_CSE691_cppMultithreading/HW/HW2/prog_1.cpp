#include <iostream>
#include <complex>
#include <vector>
#include <thread>
#include <fstream>

using namespace std;

typedef complex<double> cx;
const double pi = 3.1415926536;
const cx J(0, 1);

void myfun(vector<cx> &b, int start, int end, int m, int m2, cx w, cx wm)
{
    // if (start == 0)
    // cout << start << " " << end << " " << m << " " << m2 << " " << w << " " << wm << endl;

    for (int j = start; j < end; ++j)
    {
        for (int k = j; k < b.size(); k += m)
        {
            cx t = w * b[k + m2];
            cx u = b[k];

            b[k] = u + t;
            b[k + m2] = u - t;
        }
        w *= wm;
        // cout << w << endl;
    }

    if (end == m2 && end - start == m2 / 4){
        // cout << w << endl;
        // w /= wm; 
        cout << w << endl;
    }
    // cout << endl;
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

    for (int i = 1; i <= log2n; i++)
    {
        int m = 1 << i;
        int m2 = m >> 1;
        cx w1(1, 0);
        cx wm = exp(-J * (pi / m2));

        if (i == 1)
        {
            myfun(b, 0, m2, m, m2, w1, wm);
        }
        else if (i == 2)
        {
            cx w2 = w1 * exp(-J * (pi / 2));
            // cout << w1 << " " << w2 << endl;
            thread T1{myfun, ref(b), 0, m2 / 2, m, m2, w1, wm};
            myfun(b, m2 / 2, m2, m, m2, w2, wm);
            T1.join();
        }
        else
        {
            cx w2 = w1 * exp(-J * (pi / 4));
            cx w3 = w2 * exp(-J * (pi / 4));
            cx w4 = w3 * exp(-J * (pi / 4));
            // cout << w1 << " " << w2 << " " << w3 << " " << w4 << endl;
            thread T1{myfun, ref(b), 0, m2 / 4, m, m2, w1, wm};
            thread T2{myfun, ref(b), m2 / 4, m2 / 2, m, m2, w2, wm};
            thread T3{myfun, ref(b), m2 / 2, m2 * 3 / 4, m, m2, w3, wm};
            myfun(b, m2 * 3 / 4, m2, m, m2, w4, wm);
            T1.join();
            T2.join();
            T3.join();
        }
    }

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

    for (cx &i : b)
    {
        out << i << "\n";
    }

    out.close();

    return 0;
}