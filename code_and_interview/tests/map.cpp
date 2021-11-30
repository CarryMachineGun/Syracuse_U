#include <map>
#include <iostream>

using namespace std;

int main(){
    map<int, int> m1 {{1,2}, {2,3}, {2,5}};

    m1[1] = 5;

    cout << m1[1] << " " << m1[2] << endl;

    return 0;
}

