#include <iostream>
#include <thread>
#include <vector>

using namespace std;

void myMerge(vector<int> &arr, int l, int r){
    vector<int> temp;
    int mid = (l + r) / 2, l_ptr = l, r_ptr = mid;

    while(l_ptr < mid && r_ptr < r){
        if(arr[l_ptr] < arr[r_ptr]){
            temp.push_back(arr[l_ptr++]);
        }else{
            temp.push_back(arr[r_ptr++]);
        }
    }

    while(l_ptr < mid) temp.push_back(arr[l_ptr++]);

    while(r_ptr < r) temp.push_back(arr[r_ptr++]);
    
    for(int i = 0, j = l; j < r; j++, i++){
        arr[j] = temp[i];
    }
    
    return;
}


void mergeSort(vector<int> &arr, int l, int r){
    if(r - l <= 1) return; 

    mergeSort(arr, l, (r + l) / 2);
    mergeSort(arr, (r + l) / 2, r);

    myMerge(arr, l, r);

    return;
}


int main(){
    vector<int> test_case{3,311,23,56,23123,5,2,878,3,1};

    thread T1{mergeSort, ref(test_case), 0, test_case.size() / 4};
    thread T2{mergeSort, ref(test_case), test_case.size() / 4, test_case.size() / 2};
    thread T3{mergeSort, ref(test_case), test_case.size() / 2, test_case.size() * 3 / 4};
    mergeSort(test_case, test_case.size() * 3 / 4, test_case.size());

    T1.join();
    T2.join();
    T3.join();

    thread T4{myMerge, ref(test_case), 0, test_case.size() / 2};
    myMerge(test_case, test_case.size() / 2, test_case.size());
    T4.join();

    myMerge(test_case, 0, test_case.size());

    for(int i : test_case) cout << i << " ";
    cout << endl;


    return 0;
}