#include <vector>
#include <iostream>

using namespace std;

void QuickSort(vector<int>& arr, int start, int end){
    if(start >= end){
        return;
    }

    int povit = arr[end], l_end = start;

    for(int i = start; i < end; i++){
        if(arr[i] < povit){
            int temp = arr[i];
            arr[i] = arr[l_end];
            arr[l_end] = temp;
            l_end++;
        }
    }

    arr[end] = arr[l_end];
    arr[l_end] = povit;

    QuickSort(arr, start, l_end -1);
    QuickSort(arr, l_end+1, end);

    return;
}


template<typename T> ostream &operator<<(ostream& str, vector<T> arr){
    for(T i : arr){
        str << i << ", ";
    }

    str << endl;

    return str;
}


int main(){
    vector<int> arr{1,8,4,1,3,5,8,12};

    QuickSort(arr, 0, arr.size() - 1);

    cout << arr << endl;

    return 0;
}