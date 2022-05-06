//packaged_task, future, async, promise
#include <iostream>
#include <future>//packaged_task, async, promise
#include <thread>
#include <cmath>


using namespace std;

int Sum(int a, int b){
    return a + b;
}

int main(){
    // packaged_task<int(int, int)> task(Sum);
    // future<int> fut = task.get_future();

    // task(10, 12);
    // cout << fut.get() << endl;

    packaged_task<int(int, int)> task([](int a, int b){
        return a + b;
    });

    future<int> fut = task.get_future();
    task(22, 3);
    cout << fut.get() << endl;

    return 0; 
}