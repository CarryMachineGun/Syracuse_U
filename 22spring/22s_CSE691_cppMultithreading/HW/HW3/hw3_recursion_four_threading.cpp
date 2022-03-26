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

    if (end - start <= arr.size() / 4 && !multithreading)
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
    for (int i = start; i < end; i += offset)
    {
        eachStage(up, offset / 2, i, i + offset, arr, multithreading);

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
        thread T1{threadAllocation, 0, arr.size() / 4, offset, up, ref(arr), true};
        thread T2{threadAllocation, arr.size() / 4, arr.size() / 2, offset, !up, ref(arr), true};
        thread T3{threadAllocation, arr.size() / 2, arr.size() * 3 / 4,offset, up, ref(arr), true};
        threadAllocation(arr.size() * 3 / 4, arr.size(), offset, !up, arr, true);

        T1.join();
        T2.join();
        T3.join();
    }
    else
    {
        threadAllocation(0, arr.size(), offset, up, arr, false);
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

    for (int i : arr)
    {
        cout << i << " ";
    }

    cout << endl;

    bitonicSort(arr, arr.size());

    for (int i : arr)
    {
        cout << i << " ";
    }

    cout << endl;

    out.close();

    return 0;
}