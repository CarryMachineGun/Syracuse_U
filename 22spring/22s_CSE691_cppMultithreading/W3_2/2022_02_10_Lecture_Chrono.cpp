//chrono
#pragma warning(disable: 4996) //ctime
#include <iostream>
#include <thread>
//#include <chrono> //optional for vs2022
//#include <ctime> //optional for vs2022


using namespace std;
using namespace chrono;
using namespace literals::chrono_literals;//s, h, min, ms, us, ns


int main() {

	ratio<3, 5> r1;
	cout << r1.num << "/" << r1.den << endl;
	cout << chrono::system_clock::period::num << "/" << system_clock::period::den << " seconds" <<endl;
	cout << chrono::steady_clock::period::num << "/" << steady_clock::period::den << " seconds" << endl;
	cout << high_resolution_clock::period::num << "/" << high_resolution_clock::period::den << " seconds" << endl;

	system_clock::time_point t1{ system_clock::now() };
	this_thread::sleep_for(milliseconds(500));
	auto t2(system_clock::now());
	system_clock::duration Delay{ t2 - t1 };
	cout << Delay.count() << " 10^-7 seconds" << endl;
	cout << chrono::duration_cast<milliseconds>(Delay).count() << " ms" << endl;
	cout << chrono::duration<double>(Delay).count() << " seconds" << endl;//automatically switch unit to seconds

	cout << t1.time_since_epoch().count() << "  10^-7 seconds" << endl;
	//epoch is 00:00 January 1, 1970, Greenwich time.

	time_t t1_t{ system_clock::to_time_t(t1) };//time_t is a c function to convert time_point to time_t
	cout << ctime(&t1_t) << endl;
	auto t0{ system_clock::time_point{} };//will return epoch time_point   you can replace {} with ()
	//anonynmous time_point object with default constructor

	time_t t0_t{ system_clock::to_time_t(t0) };
	cout << "Epoch is " << ctime(&t0_t) << endl;

	//auto yesterday{ system_clock::now() - hours(24) };
	auto yesterday{ system_clock::now() - 24h };
	auto yes_t{ system_clock::to_time_t(yesterday) };
	cout << "yesterday " << ctime(&yes_t) << endl;

	this_thread::sleep_for(120ms);//milliseconds(120);

	
	return 0;
}

