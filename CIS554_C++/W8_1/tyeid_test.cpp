#include <iostream>

using namespace std;

int d;

int main(){
    int a = 0;
    char b = 'v';
    decltype(a) c;

    cout << typeid(a).name() << " " << typeid(c).name() << endl; 
    cout << c << endl;
    cout << d << endl;


    return 0;
}