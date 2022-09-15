#include <shared_mutex>
#include <mutex>
#include <iostream>
#include <thread>
#include <vector>

using namespace std;

shared_mutex m1;

void f1(int id){
	// m1.lock(); //
	for (int i = 0; i < 5000; ++i)
	{
		this_thread::sleep_for(100us);
		unique_lock<shared_mutex> ql(m1);
		// m1.lock();//
		cout << "ID = " << id << " mutex  12111111111111"
			 << "  "
			 << " This is a very  very long text" << endl;
		// m1.unlock();
	}
	// m1.unlock();
}

void f2(int id){
	// m1.lock(); //
	for (int i = 0; i < 5000; ++i)
	{
		this_thread::sleep_for(100us);
		shared_lock<shared_mutex> sl(m1);
		// m1.lock_shared();//
		cout << "ID = " << id << " shared_mutex  21222222222222"
			 << "  "
			 << " This is a very  very long text" << endl;
		// m1.unlock_shared();
	}
	// m1.unlock();
}


int main(){
    vector<thread> threads;
    
	for(int i = 1; i < 10 ; i++){
		threads.push_back(thread(f2, i));
	}
	//there will be no line misplaced for id = 1;
	f1(0);

	for(thread & i : threads){
		i.join();
	}

	return 10;
}