#include <list>
#include <iostream>

using namespace std;

int main(){

    auto f = [](int a, int b){return a < b;};
    auto isOdd = [](int a){return (a % 2 == 1);};

    list<int> l1{1,3,4,5,56,2,1};
    list<int> l2{2,3,5,1,13,3,523,4123};
    list<int> l3(5, 100);

    l1.sort(f);
    l2.sort(f);

    for(auto i = l1.begin(); i != l1.end(); i++){
        cout << *i << ", ";
    }

    cout << endl;

    for(int i : l2){
        cout << i << ", ";
    }

    cout << endl;


    l1.merge(l2);
    l1.merge(l3);


    for(auto i = l1.begin(); i != l1.end(); i++){
        cout << *i << ", ";
    }

    cout << endl;

    l1.remove_if(isOdd);

    for(auto i = l1.begin(); i != l1.end(); i++){
        cout << *i << ", ";
    }

    return 0;
}