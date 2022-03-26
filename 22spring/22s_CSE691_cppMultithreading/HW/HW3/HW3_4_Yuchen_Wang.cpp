// Yuchen Wang; ywang249
// four thread
#include <iostream>
#include <vector>
#include <fstream>
#include <thread>

using namespace std;
using namespace chrono;

class Timer
{
public:
    chrono::system_clock::time_point Begin, End;
    system_clock::duration Runtime;
    ofstream *out;
    Timer(ofstream *out)
    { // constructor
        this->out = out;
        Begin = system_clock::now();
    }
    ~Timer()
    {
        End = system_clock::now();
        Runtime = End - Begin;
        *out << "Runtime = " << chrono::duration_cast<chrono::microseconds>(Runtime).count() << endl;
    }
};

void shift(vector<int> &arr, bool up, int start, int end, int offset);
void eachStage(bool up, int offset, int start, int end, vector<int> &arr);
void threadAllocation(int start, int end, int offset, bool up, vector<int> &arr);
void bitonicSort(vector<int> &arr, int offset);

void shift(vector<int> &arr, bool up, int start, int end, int offset)
{
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

    return;
}

void eachStage(bool up, int offset, int start, int end, vector<int> &arr)
{
    if (offset < 1)
        return;

    shift(arr, up, start, end, offset);

    eachStage(up, offset / 2, start, (start + end) / 2, arr);
    eachStage(up, offset / 2, (start + end) / 2, end, arr);

    return;
}

void threadAllocation(int start, int end, int offset, bool up, vector<int> &arr)
{
    for (int i = start; i < end; i += offset)
    {
        eachStage(up, offset / 2, i, i + offset, arr);

        up = up == true ? false : true;
    }

    return;
}

void bitonicSort(vector<int> &arr, int offset)
{
    if (offset < 2)
        return;

    bitonicSort(arr, offset / 2);

    bool up = false;

    if (offset <= arr.size() / 4)
    {
        thread T1{threadAllocation, 0, arr.size() / 4, offset, up, ref(arr)};
        thread T2{threadAllocation, arr.size() / 4, arr.size() / 2, offset, !up, ref(arr)};
        thread T3{threadAllocation, arr.size() / 2, arr.size() * 3 / 4, offset, up, ref(arr)};
        threadAllocation(arr.size() * 3 / 4, arr.size(), offset, !up, arr);

        T1.join();
        T2.join();
        T3.join();
    }
    //The second last stage
    else if (offset == arr.size() / 2)
    {
        shift(arr, up, 0, arr.size() / 2, offset / 2);
        shift(arr, !up, arr.size() / 2, arr.size(), offset / 2);

        //we start do mutithreading at the second sub-stage of the last stage
        thread T1{threadAllocation, 0, arr.size() / 4, offset / 2, up, ref(arr)};
        thread T2{threadAllocation, arr.size() / 4, arr.size() / 2, offset / 2, up, ref(arr)};
        thread T3{threadAllocation, arr.size() / 2, arr.size() * 3 / 4, offset / 2, !up, ref(arr)};
        threadAllocation(arr.size() * 3 / 4, arr.size(), offset / 2, !up, arr);

        T1.join();
        T2.join();
        T3.join();
    }
    //The last stage
    else
    {
        shift(arr, up, 0, arr.size(), offset / 2);

        shift(arr, up, 0, arr.size() / 2, offset / 4);
        shift(arr, up, arr.size() / 2, arr.size(), offset / 4);

        //we start do mutithreading at the third sub-stage of the last stage
        thread T1{threadAllocation, 0, arr.size() / 4, offset / 4, up, ref(arr)};
        thread T2{threadAllocation, arr.size() / 4, arr.size() / 2, offset / 4, up, ref(arr)};
        thread T3{threadAllocation, arr.size() / 2, arr.size() * 3 / 4, offset / 4, up, ref(arr)};
        threadAllocation(arr.size() * 3 / 4, arr.size(), offset / 4, up, arr);

        T1.join();
        T2.join();
        T3.join();
    }

    return;
}

int main()
{
    string line;
    ofstream out("output4.txt");

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
        out << i << endl;

    out.close();

    return 0;
}