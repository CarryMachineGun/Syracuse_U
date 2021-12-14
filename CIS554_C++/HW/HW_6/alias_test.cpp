#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

int main(){

    int i = 0;

    int &j = i;

    cout << i << " " << j << endl;

    i++;


    cout << i << " " << j << endl;

    j++;

    cout << i << " " << j << endl;

    unordered_map<int, vector<int>*> m;

    m[1] = new vector<int>{1,2,34};

    cout << (m[1] == nullptr) << " " << (m[2] == nullptr) << endl;

    return 0;
}