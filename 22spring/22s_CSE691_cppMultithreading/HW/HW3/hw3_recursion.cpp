// Yuchen Wang; ywang249
// one thread

#include <iostream>
#include <vector>
#include <fstream>
#include <chrono>

using namespace std;
using namespace chrono;

class Timer
{
public:
    chrono::system_clock::time_point Begin, End;
    system_clock::duration Runtime;
    ofstream* out;
    Timer(ofstream* out)
    { // constructor
        this->out = out;
        Begin = system_clock::now();
    }
    ~Timer()
    {
        End = system_clock::now();
        Runtime = End - Begin;
        *out << "Runtime = " << chrono::duration_cast<chrono::milliseconds>(Runtime).count() << endl;
    }
};

void eachStage(bool up, int offset, int start, int end, vector<int> &arr)
{
    if (offset < 1)
        return;

    for (int i = start; i + offset < end; i++)
    {
        if (up)
        {
            if (arr[i] < arr[i + offset])
                swap(arr[i], arr[i + offset]);
        }
        else
        {
            if (arr[i] >= arr[i + offset])
                swap(arr[i], arr[i + offset]);
        }
    }

    eachStage(up, offset / 2, start, (start + end) / 2, arr);
    eachStage(up, offset / 2, (start + end) / 2, end, arr);

    return;
}

void bitonicSort(vector<int> &arr, int offset)
{
    if (offset < 2)
        return;

    bitonicSort(arr, offset / 2);

    bool up = false;

    for (int i = 0; i < arr.size(); i += offset)
    {
        eachStage(up, offset / 2, i, i + offset, arr);

        up = up == true ? false : true;
    }

    return;
}

int main()
{
    string line;
    ofstream out("output1.txt");

    int n{1024}; // Assume is a power of 2
    vector<int> arr;
    for (int i = 0; i < n; ++i)
        arr.emplace_back(rand() % 10000);

    {
        Timer t1(&out);
        bitonicSort(arr, arr.size());
    }

    for (int i = 1; i < arr.size(); i++)
    {
        if (arr[i] < arr[i - 1])
        {
            cout << "ERROR!!!!" << endl;
            break;
        }
    }

    for (int i : arr)
        out << i << " ";

    out << endl;

    out.close();

    return 0;
}