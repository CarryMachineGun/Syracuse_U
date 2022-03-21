#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

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

void bitonicSort(vector<int> &arr)
{

    for (int offset = 2; offset <= arr.size(); offset *= 2)
    {
        int up = false;

        for (int i = 0; i < arr.size(); i += offset)
        {
            eachStage(up, offset / 2, i, i + offset, arr);

            up = up == true ? false : true;
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

    for (int i : arr)
    {
        cout << i << " ";
    }

    cout << endl;

    bitonicSort(arr);

    for (int i : arr)
    {
        cout << i << " ";
    }

    cout << endl;

    out.close();

    return 0;
}