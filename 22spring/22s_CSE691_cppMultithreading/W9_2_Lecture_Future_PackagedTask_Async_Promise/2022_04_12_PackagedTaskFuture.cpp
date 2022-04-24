//packaged_task, future, async, promise
#include <iostream>
#include <future>//packaged_task, async, promise
#include <thread>
#include <cmath>

using namespace std;

struct myFunctorClass {
	int operator()(int a, int b) { return pow(a, b); }


}  f1;

int f(int a, int b) { return pow(a, b); }//cmath for pow

void Task_Function() {
	packaged_task<int(int, int)> task(f);//define something that will run asynchronously
	future<int> Fut = task.get_future();
	task(2, 15);
	cout << "Task_Function " << Fut.get() << endl;
}

void Task_Functor() {
	packaged_task<int(int, int)> task(f1);//define something that will run asynchronously
	future<int> Fut = task.get_future();
	task(2, 11);
	cout << "Task_Functor " << Fut.get() << endl;
}


void Task_Lambda() {
	packaged_task<int(int, int)> task([](int a, int b) {return pow(a, b); });//define something that will run asynchronously
	future<int> Fut = task.get_future();
	task(2, 8);
	cout << "Task_Lambda " << Fut.get() << endl;
}

void Task_Bind() {
	packaged_task<int()> task(bind(f, 2, 12));//define something that will run asynchronously
	future<int> Fut = task.get_future();
	task();
	cout << "Task_Bind " << Fut.get() << endl;
}

void Task_Thread() {

	packaged_task<int(int a, int b)> task(f);//define something that will run asynchronously
	future<int> Fut = task.get_future();
	thread T1(move(task), 2, 7);
	
	cout << "Task_Thread " << Fut.get() << endl;
	T1.join();

}


int main() {
	Task_Function();
	Task_Functor();
	Task_Lambda();
	Task_Bind();
	Task_Thread();

	return 0;
}

