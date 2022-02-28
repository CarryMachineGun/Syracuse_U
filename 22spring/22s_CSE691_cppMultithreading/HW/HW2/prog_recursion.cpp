#include <iostream>
#include <complex>
#include <vector>
#include <thread>
#include <fstream>

using namespace std;

typedef complex<double> cx;
const double PI = 3.1415926536;
const cx J(0, 1);

void myfun(vector<cx> &a,vector<cx> &a_even, vector<cx> &a_odd, int start, int end, cx w, cx wn)
{
    for (int i = start; i < end; i++)
    {
        a[i] = a_even[i] + w * a_odd[i];
        a[i + a.size() / 2] = a_even[i] - w * a_odd[i];
        w *= wn;
    }
}

void fft(vector<cx> &a)
{
    if (a.size() == 1)
        return;

    const cx J1(0, 1);
    cx wn = exp(-J * (2 * PI / a.size()));
    cx w(1, 0); //start from complex (1.0)
    vector<cx> a_even(a.size() / 2), a_odd(a.size() / 2);

    for (int i = 0; i < a.size() / 2; i++)
    {
        a_even[i] = a[2 * i];
        a_odd[i] = a[2 * i + 1];
    }

    fft(a_odd);
    fft(a_even);

    thread T1{myfun, ref(a), ref(a_even), ref(a_odd), 0, a.size() / 8, cx(0,1), };
    myfun(b, (log2n - 1) * 3 / 4 + 1, log2n + 1);
    T1.join();
    T2.join();
    T3.join();

    // double ang = 2 * PI / n;
    // for (int i = 0; i < a.size() / 2; i++)
    // {
    //     a[i] = a_even[i] + w * a_odd[i];
    //     a[i + a.size() / 2] = a_even[i] - w * a_odd[i];
    //     w *= wn;
    // }
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

    fft(a);

    for(cx &i : a){
        out << i << "\n";
    }

    out.close();

    return 0;
}