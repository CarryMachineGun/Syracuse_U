#include <iostream>
#include <complex>
#include <cmath>
#include <iterator>
#include <vector>
#include <thread>
#include <fstream>

using namespace std;

typedef complex<double> cx;

// ---------------------------------------------------- iterative one ----------------------------------------

unsigned int bitReverse(unsigned int x, int log2n)
{
    int n = 0;
    int mask = 0x1;
    for (int i = 0; i < log2n; i++)
    {
        n <<= 1;
        n |= (x & 1);
        x >>= 1;
    }
    return n;
}

const double pi = 3.1415926536;

// template <class Iter_T>
void fft1(vector<cx> &a, vector<cx> &b, int log2n)
{
    // typedef typename iterator_traits<Iter_T>::value_type complex;
    const cx J(0, 1);
    int n = 1 << log2n;
    for (unsigned int i = 0; i < n; ++i)
    {
        b[bitReverse(i, log2n)] = a[i];
    }
    for (int s = 1; s <= log2n; ++s)
    {
        int m = 1 << s;
        int m2 = m >> 1;
        cx w(1, 0);
        cx wm = exp(-J * (pi / m2));
        for (int j = 0; j < m2; ++j)
        {
            for (int k = j; k < n; k += m)
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

// ---------------------------------------------------- iterative two ----------------------------------------

unsigned int bitReverse2(int x, int log2n)
{
    int n = 0;
    for (int i = 0; i < log2n; i++)
    {
        n <<= 1;
        n |= (x & 1);
        x >>= 1;
    }
    return n;
}

// Iterative FFT function to compute the DFT
// of given coefficient vector
void fft3(vector<cx> &a, vector<cx> &b)
{
    const cx J(0, 1);
    int log2n = 1;

    while (pow(2, log2n) != a.size())
    {
        log2n++;
    }

    // bit reversal of the given array
    for (int i = 0; i < a.size(); i++)
    {
        int rev = bitReverse2(i, log2n);
        b[i] = a[rev];
    }

    int count = 0;

    // int m = 1 << i;  // 2 power s
    // int m2 = m >> 1; // m2 = m/2 -1
    for (int i = 1; i <= log2n; i++)
    {
        int m = 1 << i; // 2 power s
        // int m2 = m >> 1; // m2 = m/2 -1
        int m2 = m / 2; // m2 = m/2 -1
        // cout << m2 << endl;
        cx w(1, 0);

        // principle root of nth complex
        // root of unity.
        cx wm = exp(-J * (pi / m2));

        // cout << 0 << " " << m2 << " " << m << " " << m2 << " " << w << " " << wm << endl;
        for (int j = 0; j < m2; ++j)
        {
            // the problem is for last and the second last ilteration, j will only be 0 or 0 and 1, there is no space for 4 mutithreadings
            for (int k = j; k < b.size(); k += m)
            {

                // t = twiddle factor
                cx t = w * b[k + m2];
                cx u = b[k];

                // similar calculating y[k]
                b[k] = u + t;

                // similar calculating y[k+n/2]
                b[k + m2] = u - t;
            }
            // cout << w << endl;
            w *= wm;

        }

        cout << w << endl;
        // cout << endl;
    }

    return;
}

// ---------------------------------------------------- recursive one ----------------------------------------

void fft2(vector<cx> &a)
{
    if (a.size() == 1)
        return;

    const cx J(0, 1);
    cx wn = exp(-J * (2 * pi / a.size()));
    cx w(1, 0); // start from complex (1.0)
    vector<cx> a_even(a.size() / 2), a_odd(a.size() / 2);

    for (int i = 0; i < a.size() / 2; i++)
    {
        a_even[i] = a[2 * i];
        a_odd[i] = a[2 * i + 1];
    }

    fft2(a_odd);
    fft2(a_even);

    // double ang = 2 * PI / n;
    for (int i = 0; i < a.size() / 2; i++)
    {
        a[i] = a_even[i] + w * a_odd[i];
        a[i + a.size() / 2] = a_even[i] - w * a_odd[i];
        cout << w << endl;
        w *= wn;
    }
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
    // fft1(a, b, 6);
    fft3(a, b);
    // for (int i = 0; i < b.size(); ++i)
    //     cout << b[i] << "\n";
    // fft2(a);
    // for (int i = 0; i < a.size(); ++i)
    //     cout << a[i] << "\n";

    for (cx &i : b)
    {
        out << i << "\n";
        // cout << i << endl;
    }

    out.close();
}

// (16,16)
// (-4.82843,-11.6569)
// (0,0)
// (-0.343146,0.828427)
// (0,0)
// (0.828427,-0.343146)
// (0,0)
// (-11.6569,-4.82843)