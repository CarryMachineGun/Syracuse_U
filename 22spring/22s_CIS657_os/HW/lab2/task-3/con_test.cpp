#include <iostream>


using namespace std;

class foo{
public:
    int val;

    foo(int a){
        val = a;
    }

    int getVal() const{
        val = 6;
    }

    int setVal() {
        val = 6;
    }
};