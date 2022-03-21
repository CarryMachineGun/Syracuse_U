#include <iostream>
#include <vector>
#include <fstream>
#include <thread>

using namespace std;

void eachStage(bool up, int offset, int start, int end, vector<int> &arr, bool multithreading)
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

    // eachStage(up, offset / 2, start, (start + end) / 2, arr, true);
    // eachStage(up, offset / 2, (start + end) / 2, end, arr, true);

    if (end - start <= arr.size() / 2 && !multithreading)
    {
        thread T1{eachStage, up, offset / 2, start, (start + end) / 2, ref(arr), true};
        eachStage(up, offset / 2, (start + end) / 2, end, ref(arr), true);
        T1.join();
    }
    else
    {
        eachStage(up, offset / 2, start, (start + end) / 2, arr, multithreading);
        eachStage(up, offset / 2, (start + end) / 2, end, arr, multithreading);
    }

    return;
}

void threadAllocation(int start, int end, int offset, bool up, vector<int> &arr, bool multithreading)
{
    // cout << "start: " << start << ", end: " << end << ", offset: " << offset << endl;
    for (int i = start; i < end; i += offset)
    {
        eachStage(up, offset / 2, i, i + offset, arr, multithreading);

        up = up == true ? false : true;
    }

    return;
}

void bitonicSort(vector<int> &arr)
{

    for (int offset = 2; offset <= arr.size(); offset *= 2)
    {
        int up = false;

        if (offset < arr.size())
        {
            // cout << offset << " new thread created" << endl;
            thread T1{threadAllocation, 0, arr.size() / 2, offset, up, ref(arr), true};

            // If offset == arr.size() / 2, we need to flip the value of up
            if (offset == arr.size() / 2)
                threadAllocation(arr.size() / 2, arr.size(), offset, !up, arr, true);
            else
                threadAllocation(arr.size() / 2, arr.size(), offset, up, arr, true);

            T1.join();

            // for (int i : arr)
            //     cout << i << " ";

            // cout << endl;
        }
        else
        {
            threadAllocation(0, arr.size(), offset, up, arr, false);

            // for (int i : arr)
            //     cout << i << " ";

            // cout << endl;
        }
    }

    return;
}

int main()
{
    string line;
    vector<int> arr;
    ifstream in("data.txt");
    ofstream out("output_data.txt");

    if (in.is_open())
    {
        while (getline(in, line, ' '))
        {
            arr.push_back(stod(line));
        }
        in.close();
    }

    cout << "input:  ";
    for (int i : arr)
    {
        cout << i << " ";
    }
    cout << endl;

    bitonicSort(arr);

    cout << "output: ";
    for (int i : arr)
    {
        cout << i << " ";
    }
    cout << endl;

    out.close();

    return 0;
}