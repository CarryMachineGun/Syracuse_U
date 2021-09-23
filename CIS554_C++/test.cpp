#include <iostream>

using namespace std;



// *int foo1(){
//     //@Yuchen_Qst: Why this one is not able to run ?
//     return new int(3);
// }
void foo1(int* &p){
    //@Yuchen_Qst: Why this one is not able to run ?
    p = new int(3);
    cout << "addr1: " << p << endl;
    return;
}

void foo2(int* &val){
    int temp = 5;
    cout << "addr2: " << &temp << endl;
    val = &temp;
    return;
}


int main()
{
    enum test {one = 'a', two , five, six };

    test k = two;

    std::cout << k << " " << six << std::endl;

    int *p;
    foo1(p);
    
    std::cout << *p << " "<< p <<  std::endl;

    foo2(p);

    std::cout << *p << " " << p << std::endl;

    // delete p;
    
    return 0;
}