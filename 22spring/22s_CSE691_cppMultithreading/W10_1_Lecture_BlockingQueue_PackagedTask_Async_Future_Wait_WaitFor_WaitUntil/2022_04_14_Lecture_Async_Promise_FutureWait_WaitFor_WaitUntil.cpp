//async
#include <future>
#include <thread>
#include <iostream>

using namespace std;

class myFunctorClass {
public:
	bool operator()(int n) const {


		for (int i = 2; i < n; ++i) {
			if (n % i == 0) return false;
		}
		return true;
	}




};

class myClass {
public:

	bool Is_Prime(int n)  const {
		for (int i = 2; i < n; ++i) {
			if (n % i == 0) return false;
		}
		return true;
	}

} f1;

bool Is_Prime(int n) {
	for (int i = 2; i < n; ++i) {
		if (n % i == 0) return false;
	}
	return true;
}

void IsPrime(future<int>& F, bool& B) {
	int a = F.get();
	for (int i = 2; i < a; ++i) {
		if (a % i == 0) { B = false;  return; }
	}
	B = true;
	return;

}

int main() {
	//future<bool> Fut1{ async(Is_Prime, 3478123) };//function
	//future<bool> Fut1{ async(myFunctorClass{}, 3478123) };//functor
	future<bool> Fut1{ //lambda
		async(
		[](int n) {
			for (int i = 2; i < n; ++i) {
				if (n % i == 0) return false;
			}
			return true; }

		, 3478123)
	};//lambda

	cout << "Fut1  " << Fut1.get() << endl;//

	//myClass m1;

	future<bool> Fut0 = async(&myClass::Is_Prime, &f1, 28282882) ;//Member Function
	cout << "Fut0 " << Fut0.get() << endl;


	//cout << Fut1.get() << endl;//future can only be access by get() once;  Use shared_future

	future<bool> Fut2{ async(launch::async, Is_Prime, 3478123) };
	cout << "Fut2  " << Fut2.get() << endl;

	future<bool> Fut3{ async(launch::deferred, Is_Prime, 3478123) };

	//......
	cout << "Fut3  " << Fut3.get() << endl;

	future<bool> Fut4{ async(launch::async | launch::deferred, Is_Prime, 3478123) };
	cout << "Fut4  " << Fut4.get() << endl;

	promise<int> Prom1;
	future<int> Fut5 = Prom1.get_future();
	//.......
	Prom1.set_value(100);
	cout << "Fut5 " << Fut5.get() << endl;

	promise<int> Prom2;
	future<int> Fut6 = Prom2.get_future();
	bool B{ false };

	thread T1{ IsPrime, ref(Fut6), ref(B) };
	//....
	Prom2.set_value(4348398);

	cout << "B " << B << endl;

	T1.join();

	future<bool> Fut7 = async(Is_Prime, 23456712);

	Fut7.wait();//wait until Is_Prime completes
	cout << "Fut7 " << Fut7.get() << endl;

	future<bool> Fut77 = async(launch::deferred, Is_Prime, 23456712);
	//A deferred async will start execution when encountering wait() or get().

	Fut77.wait();//wait until Is_Prime completes
	cout << "Fut77 " << Fut77.get() << endl;

	//.........


	future<bool> Fut8 = async(launch::deferred, Is_Prime, 23456712);

	if (Fut8.wait_for(chrono::nanoseconds(10000)) == future_status::deferred) {

		cout << "Fut8 " << Fut8.get() << "   deferred" << endl;

	}
	/*

	Three possible return values for wait_for or wait_until:

	future_status::timeout      if the async is not completed withiut  time interval
	future_status::ready        if the async is completed within the time interval
	future_status::deferred     if the aysnc has a launch::deferred specifer


	*/

	//.........





	//future.wait
	//future.wait_for
	//future.wait_until





	return 0;
}