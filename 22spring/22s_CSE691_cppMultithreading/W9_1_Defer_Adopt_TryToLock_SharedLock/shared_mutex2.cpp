#include <shared_mutex>
#include <mutex>
#include <iostream>
#include <thread>
#include <vector>

using namespace std;

shared_mutex m1;
int counter;

void f1(int id)
{
    // m1.lock(); //
    for (int i = 0; i < 5000; ++i)
    {
        // this_thread::sleep_for(100us);
        unique_lock<shared_mutex> ql(m1);
        counter++;
    }
    // m1.unlock();
}

void f2(int id)
{
    // m1.lock(); //
    for (int i = 0; i < 5000; ++i)
    {
        // this_thread::sleep_for(100us);
        shared_lock<shared_mutex> sl(m1);
        // m1.lock_shared();//
        cout << "ID = " << id << " count = " << counter << endl;
        // m1.unlock_shared();
    }
    // m1.unlock();
}

int main()
{
    vector<thread> threads;
    counter = 0;

    for (int i = 0; i < 10; i++)
    {
        if (i % 2 == 0)
            threads.push_back(thread(f2, i));
        else
            threads.push_back(thread(f1, i));
    }
    // there will be no line misplaced for id = 1;
    //  f1(0);

    for (thread &i : threads)
    {
        i.join();
    }

    cout << counter << endl;

    return 10;
}