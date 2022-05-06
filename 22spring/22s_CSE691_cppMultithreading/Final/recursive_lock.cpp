#include <mutex>
#include <iostream>
#include <thread>

using namespace std;

recursive_mutex m;
mutex m2;

void myFunc2()
{
    unique_lock<recursive_mutex> UL(m);
    // unique_lock<mutex> UL(m2);

    for (int i = 0; i < 10; i++)
    {
        UL.unlock();
        UL.lock();
    }

    return;
}

void myFunc()
{
    unique_lock<recursive_mutex> UL(m);
    // unique_lock<mutex> UL(m2);

    myFunc2();
    // for(int i = 0; i < 10; i++){
    //     UL.lock();
    // }

    // for(int i = 0; i < 10; i++){
    //     UL.unlock();
    // }

    return;
}

int main()
{
    {
        // m2.lock();
        unique_lock<mutex> UL2(m2);
        cout << m2.try_lock() << endl;
    }

    m2.lock();

    thread T1{myFunc};
    thread T2{myFunc};

    T1.join();
    T2.join();

    m2.unlock();

    return 0;
}