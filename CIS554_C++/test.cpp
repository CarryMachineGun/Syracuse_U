#include <iostream>



void foo1(int *val){
    //@Yuchen_Qst: Why this one is not able to run ?
    val = new int(3);
}

void foo2(int *val){
    int temp = 3;
    val = &temp;
}


int main()
{
    enum test {one = 'a', two , five, six };

    test k = two;

    std::cout << k << " " << six << std::endl;

    int *p;

    foo1(p);
    
    std::cout << *p << std::endl;

    // foo2(p);

    std::cout << *p << std::endl;

    delete p;
    
    return 0;
}