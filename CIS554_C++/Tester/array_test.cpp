#include <iostream>
#include <vector>

using namespace std;

int main(){

    int arr[5];
    bool arr2[5];

    for(int i : arr){
        cout << i << endl;
    }

    for(int i : arr2){
        cout << i << endl;
    }


    vector<vector<int>> arr3(5, vector<int>(2));

    for(vector<int> &i : arr3){
         for(int j : i) cout << j << ", ";
    }

    cout << endl;

    return 0;
}