// factory.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <vector>
#include <chrono>
#include <atomic>
#include<fstream>


using namespace std;
using namespace chrono;
using namespace literals::chrono_literals;

ofstream Out("log.txt");
mutex m1, m2, m3, z, z1;
condition_variable cv1, cv2;
const int MaxTimePart{ 18000 }, MaxTimeProduct{ 20000 };
const string statusList[3] = { "New Order","Wakeup-Notified"," Wakeup-Timeout" };
system_clock::time_point start;

int product = 0;
int bufferstate[5] = { 0,0,0,0,0 };
int buffercapacity[5] = { 5,5,4,3,3 };
vector<int>ProduceT = { 500,500,600,600,700 };
vector<int>MoveT = { 200,200,300,300,400 };
vector<int>assembleT = { 600,600,700,700,800 };

class partworker {
public:
	int id;
	int loadorder[5] = { 0,0,0,0,0 };
	int remainpart[5] = { 0,0,0,0,0 };
	int originload[5] = { 0,0,0,0,0 };
	int originbuffer[5] = { 0,0,0,0,0 };
	int PT = 0;
	int MT = 0;
	string status;
	bool remain = false;
	bool timeout = false;
	bool aval = false;
	int iter = 1;
	//srand(this->id);
	void checkremain() {
		int n = 0;
		for (int i = 0; i < 5; i++) {
			if (remainpart[i] == 0) {
				n++;

			}
		}
		if (n == 5) {
			remain = false;
		}
		else {
			remain = true;
		}

	}
	void moveback() {
		int mbt = 0;
		for (int i = 0; i < 5; i++) {
			if (timeout) {
				mbt += loadorder[i] * MoveT[i];
			}
		}
		this_thread::sleep_for(microseconds(mbt));
	}
	void loadbuffer() {
		MT = 0;
		for (int i = 0; i < 5; i++) {
			originbuffer[i] = bufferstate[i];
			originload[i] = loadorder[i];
		}
		for (int i = 0; i < 5; i++) {

			if (bufferstate[i] + this->loadorder[i] <= buffercapacity[i]) {
				bufferstate[i] += this->loadorder[i];
				MT += MoveT[i] * this->loadorder[i];
				this->loadorder[i] = 0;

				//this->remainpart[i] = 0;

			}
			else if (bufferstate[i] + this->loadorder[i] > buffercapacity[i] && bufferstate[i] != buffercapacity[i]) {
				int increment = buffercapacity[i] - bufferstate[i];
				this->loadorder[i] = bufferstate[i] + this->loadorder[i] - buffercapacity[i];
				bufferstate[i] = buffercapacity[i];
				MT += MoveT[i] * increment;
				//this->remainpart[i] = this->loadorder[i];

			}

		}
		this_thread::sleep_for(microseconds(MT));
		for (int i = 0; i < 5; i++) {
			this->remainpart[i] = this->loadorder[i];
		}
		this->checkremain();

		//if (remain) {
			//auto wait_time = cv1.wait_for(UG1, microseconds(MaxTimePart));
		//}

		//cv2.wait_for

	}
	void regenerate() {
		int current = 0;
		PT = 0;
		for (int i = 0; i < 5; i++) {
			current += this->loadorder[i];
			originload[i] = loadorder[i];
		}
		//srand(300);
		for (int i = 0; i < 5 - current; i++) {
			this->loadorder[rand() % 5] += 1;
		}
		for (int i = 0; i < 5; i++) {

			PT += loadorder[i] * ProduceT[i] - remainpart[i] * ProduceT[i];
		}
		this_thread::sleep_for(microseconds(PT));
	}
	void checkavaibility() {
		int n = 0;
		for (int i = 0; i < 5; i++) {
			if (bufferstate[i] < buffercapacity[i] && loadorder[i] != 0) {
				n++;
			}
		}
		if (n > 0) {
			aval = true;
		}
		else {
			aval = false;
		}
	}

	void Print(system_clock::duration& waittime, system_clock::time_point& start) {
		lock_guard<mutex> LG2(m3);
		//system_clock::time_point wakeUpTime{ system_clock::now() };
		//system_clock::duration waitTime{ wakeUpTime - start };
		system_clock::time_point Time = system_clock::now();
		system_clock::duration current = Time - start;
		Out << "current time is : " << duration_cast<microseconds>(current).count() << " us" << endl;
		Out << "partworker id: " << this->id << endl;
		Out << "iteration :" << this->iter << endl;
		Out << "status: " << this->status << endl;
		Out << "accumulated waiting time is: " << duration_cast<microseconds>(waittime).count() << "us" << endl;
		if (!timeout) {
			Out << "Buffer State : " << "(" << this->originbuffer[0] << "," << this->originbuffer[1] << "," << this->originbuffer[2] << "," << this->originbuffer[3] << "," << this->originbuffer[4] << ")" << endl;
			Out << "load order: " << "(" << this->originload[0] << "," << this->originload[1] << "," << this->originload[2] << "," << this->originload[3] << "," << this->originload[4] << ")" << endl;
			Out << "Updated Buffer State : " << "(" << bufferstate[0] << "," << bufferstate[1] << "," << bufferstate[2] << "," << bufferstate[3] << "," << bufferstate[4] << ")" << endl;
			Out << "Updated load order: " << "(" << this->loadorder[0] << "," << this->loadorder[1] << "," << this->loadorder[2] << "," << this->loadorder[3] << "," << this->loadorder[4] << ")" << endl;
		}
		else {
			Out << "Updated Buffer State : " << "(" << bufferstate[0] << "," << bufferstate[1] << "," << bufferstate[2] << "," << bufferstate[3] << "," << bufferstate[4] << ")" << endl;
			Out << "load order: " << "(" << this->originload[0] << "," << this->originload[1] << "," << this->originload[2] << "," << this->originload[3] << "," << this->originload[4] << ")" << endl;
			Out << "Updated Buffer State : " << "(" << bufferstate[0] << "," << bufferstate[1] << "," << bufferstate[2] << "," << bufferstate[3] << "," << bufferstate[4] << ")" << endl;
			Out << "Updated load order: " << "(" << this->loadorder[0] << "," << this->loadorder[1] << "," << this->loadorder[2] << "," << this->loadorder[3] << "," << this->loadorder[4] << ")" << endl;
		}
		Out << endl;

	}
	void Print1(system_clock::time_point& start) {
		lock_guard<mutex> LG2(m3);
		system_clock::time_point time = system_clock::now();
		system_clock::duration Current = time - start;
		Out << "current time is : " << duration_cast<microseconds>(Current).count() << " us" << endl;
		Out << "partworker id: " << this->id << endl;
		Out << "iteration :" << this->iter << endl;
		Out << "status: " << this->status << endl;
		Out << "accumulated waiting time is: " << 0 << "us" << endl;
		if (!timeout) {
			Out << "Buffer State : " << "(" << this->originbuffer[0] << "," << this->originbuffer[1] << "," << this->originbuffer[2] << "," << this->originbuffer[3] << "," << this->originbuffer[4] << ")" << endl;
			Out << "load order: " << "(" << this->originload[0] << "," << this->originload[1] << "," << this->originload[2] << "," << this->originload[3] << "," << this->originload[4] << ")" << endl;
			Out << "Updated Buffer State : " << "(" << bufferstate[0] << "," << bufferstate[1] << "," << bufferstate[2] << "," << bufferstate[3] << "," << bufferstate[4] << ")" << endl;
			Out << "Updated load order: " << "(" << this->loadorder[0] << "," << this->loadorder[1] << "," << this->loadorder[2] << "," << this->loadorder[3] << "," << this->loadorder[4] << ")" << endl;
		}
		else {
			Out << "Updated Buffer State : " << "(" << bufferstate[0] << "," << bufferstate[1] << "," << bufferstate[2] << "," << bufferstate[3] << "," << bufferstate[4] << ")" << endl;
			Out << "load order: " << "(" << this->originload[0] << "," << this->originload[1] << "," << this->originload[2] << "," << this->originload[3] << "," << this->originload[4] << ")" << endl;
			Out << "Updated Buffer State : " << "(" << bufferstate[0] << "," << bufferstate[1] << "," << bufferstate[2] << "," << bufferstate[3] << "," << bufferstate[4] << ")" << endl;
			Out << "Updated load order: " << "(" << this->loadorder[0] << "," << this->loadorder[1] << "," << this->loadorder[2] << "," << this->loadorder[3] << "," << this->loadorder[4] << ")" << endl;
		}
		Out << endl;

	}

	void test() {
		srand(this->id);
		for (int i = 0; i < 5; i++) {
			if (!timeout)
			{
				this->regenerate();
			}
			timeout = false;
			iter = i + 1;
			{
				unique_lock<mutex>UG1(m1);
				this->checkavaibility();
				if (aval) {
					//lock_guard<mutex>LG3(z);
					this->loadbuffer();
					status = statusList[0];
					this->Print1(start);
				}
				if(!aval||remain) {
					//remain = true;
					system_clock::time_point wakeupTime = system_clock::now();
					system_clock::time_point wakeupTime1 = system_clock::now();
					//unique_lock<mutex>UG1(m1);
					while (remain) {
						system_clock::time_point starttime = system_clock::now();
						auto wait_time = cv1.wait_for(UG1, microseconds(MaxTimePart));
						if (wait_time == cv_status::timeout) {
							wakeupTime = system_clock::now();
							system_clock::duration waittime1{ wakeupTime - starttime };
							status = statusList[2];
							timeout = true;
							this->regenerate();
							this->Print(waittime1, start);
							this->moveback();
							break;
						}
						else {
							wakeupTime1 = system_clock::now();
							system_clock::duration waittime2{ wakeupTime1 - starttime };
							this->checkavaibility();
							if (aval) {
								this->loadbuffer();
								status = statusList[1];
								this->Print(waittime2, start);
							}
							else {
								continue;//continue wait
							}
						}
					}
				}
				cv2.notify_all();
			}
			//cv2.notify_all();


		}

	}

};

class productworker {
public:
	int id;
	int pickuporder[5] = { 0,0,0,0,0 };
	int realpickup[5] = { 0,0,0,0,0 };
	int cartstate[5] = { 0,0,0,0,0 };
	int asmbT = 0;
	int iter = 1;
	int obs[5] = { 0,0,0,0,0 };
	int opk[5] = { 0,0,0,0,0 };
	int ocs[5] = { 0,0,0,0,0 };
	int ols[5] = { 0,0,0,0,0 };
	int localstate[5] = { 0,0,0,0,0 };
	string status;
	bool avalibility = false;
	bool timeout = false;
	bool cartfull = false;
	bool regenerate = false;//如果为TRUE, use realpickup order
	void check1() {
		int n = 0;
		for (int i = 0; i < 5; i++) {
			if (bufferstate[i] !=0 && pickuporder[i] != 0) {
				n++;
			}

		}
		if (n > 0) {
			avalibility = true;
		}
		else {
			avalibility = false;
		}
	}
	void check2() {
		int n = 0;
		for (int i = 0; i < 5; i++) {
			if (bufferstate[i] !=0 && realpickup[i] != 0) {
				n++;
			}
		}
		if (n > 0) {
			avalibility = true;
		}
		else {
			avalibility = false;
		}
	}
	void pickup() {
		int TYPE[2] = { 2,3 };
		//srand(this->id);
		int n = rand() % 2;
		for (int i = 0; i < 5; i++) {
			pickuporder[i] = 0;
		}
		//int type = 2;
		if (TYPE[n] == 2) {
			int s1 = 1 + rand() % 3; int id1 = rand() % 5; int id2 = rand() % 5;
			pickuporder[id1] = s1;
			if (id1 != id2) {
				pickuporder[id2] = 5 - s1;
			}
			else {
				while (id1 == id2) {
					id2 = rand() % 5;
				}
				pickuporder[id2] = 5 - s1;
			}

		}
		if (TYPE[n] == 3) {
			int id3 = rand() % 5; int id4 = rand() % 5; int id5 = rand() % 5;
			while (id3 == id4 || id4 == id5 || id3 == id5) {
				id4 = rand() % 5;
				id5 = rand() % 5;

			}
			int ttype[2] = { 2,3 }; int q = rand() % 2;
			pickuporder[id3] = 1;
			pickuporder[id4] = ttype[q];
			pickuporder[id5] = 5 - 1 - ttype[q];

		}
		for (int i = 0; i < 5; i++) {
			opk[i] = pickuporder[i];
		}

		regenerate = false;
	}
	void regenerator() {
		vector<int>id;
		int currentP = 0;
		for (int i = 0; i < 5; i++) {
			if (localstate[i] != 0) {
				id.push_back(i);
				currentP += localstate[i];
			}
			pickuporder[i] = localstate[i];
			//ols[i] = localstate[i];
		}
		int newparts = 5 - currentP;
		if (id.size() == 3) {
			for (int i = 0; i < newparts; i++) {
				pickuporder[id[rand() % 3]] += 1;
			}
		}
		else if (id.size() == 2) {
			int Type2[2] = { 2,3 };
			int type2 = Type2[rand() % 2];
			if (type2 == 2) {

				int combin[2] = { id[0],id[1] };

				while (pickuporder[id[0]] + pickuporder[id[1]] < 5 && newparts) {
					pickuporder[combin[rand() % 2]] += 1;
					newparts--;
				}
			}
			else if (type2 == 3) {
				int Another1 = rand() % 5;
				while (Another1 == id[0] || Another1 == id[1]) {
					Another1 = rand() % 5;
				}
				int conbin2[3] = { id[0],id[1],Another1 };
				pickuporder[Another1] = 1;
				while (pickuporder[id[0]] + pickuporder[id[1]] + pickuporder[Another1] < 5 && newparts) {
					pickuporder[conbin2[rand() % 3]] += 1;
					newparts--;
				}
			}
		}
		else if (id.size() == 1) {
			int Type1[2] = { 2,3 };
			int type1 = Type1[rand() % 2];
			if (type1 == 2) {
				int Ano1 = rand() % 5;
				while (Ano1 == id[0]) {
					Ano1 = rand() % 5;
				}
				int combin[2] = { id[0],Ano1 };

				while (pickuporder[id[0]] + pickuporder[Ano1] < 5 && newparts) {
					pickuporder[combin[rand() % 2]] += 1;
					newparts--;
				}
			}
			else if (type1 == 3) {
				int ano11 = rand() % 5;
				int ano22 = rand() % 5;
				while (ano11 == ano22 || ano11 == id[0] || ano22 == id[0]) {
					ano11 = rand() % 5;
					ano22 = rand() % 5;
				}
				int combin13[3] = { id[0],ano11,ano22 };
				while (pickuporder[id[0]] + pickuporder[ano11] + pickuporder[ano22] < 5 && newparts) {
					pickuporder[combin13[rand() % 3]] += 1;
					newparts--;
				}
			}

		}
		//cout << "the real pick up order is" << endl;
		for (int i = 0; i < 5; i++) {
			realpickup[i] = pickuporder[i] - localstate[i];
			//cout << realpickup[i];
			opk[i] = realpickup[i];
		}
		//cout << endl;
		regenerate = true;
	}
	void movefrombuffer() {
		int carttotal = 0;
		for (int i = 0; i < 5; i++) {
			obs[i] = bufferstate[i];
			ocs[i] = cartstate[i];
			if (!regenerate) {
				opk[i] = pickuporder[i];
			}
			else {
				opk[i] = realpickup[i];
			}
		}
		if (!regenerate) {
			for (int i = 0; i < 5; i++) {
				if (bufferstate[i] >= pickuporder[i]) {
					cartstate[i] += pickuporder[i];
					bufferstate[i] -= pickuporder[i];
					pickuporder[i] -= pickuporder[i];
				}
				else if (bufferstate[i] < pickuporder[i] && bufferstate[i] != 0) {
					cartstate[i] += bufferstate[i];
					pickuporder[i] -= bufferstate[i];
					bufferstate[i] -= bufferstate[i];
				}

			}
			for (int i = 0; i < 5; i++) {
				carttotal += cartstate[i];
			}
			if (carttotal == 5) {
				cartfull = true;
			}

		}
		else {
			for (int i = 0; i < 5; i++) {
				if (bufferstate[i] >= realpickup[i]) {
					cartstate[i] += realpickup[i];
					bufferstate[i] -= realpickup[i];
					realpickup[i] -= realpickup[i];
				}
				else if (bufferstate[i] < realpickup[i] && bufferstate[i] != 0) {
					cartstate[i] += bufferstate[i];
					realpickup[i] -= bufferstate[i];
					bufferstate[i] -= bufferstate[i];
				}

			}
			for (int i = 0; i < 5; i++) {
				carttotal = carttotal + cartstate[i] + localstate[i];
			}
			if (carttotal == 5) {
				cartfull = true;
			}


		}

	}
	void movetolocal() {
		int n = 0;
		for (int i = 0; i < 5; i++) {
			if (this->cartstate[i] == 0) {
				n++;
			}
			this->ocs[i] = this->cartstate[i];
			if (!regenerate) {
				this->ols[i] = 0;
				this->localstate[i] = 0;
			}
			else {
				this->ols[i] = this->localstate[i];
			}
		}
		if (n == 5) {
			regenerate = false;
			cout << "abort!" << endl;
			return;
		}
		for (int i = 0; i < 5; i++) {
			this->ols[i] = this->localstate[i];
			this->ocs[i] = this->cartstate[i];
			this->localstate[i] += this->cartstate[i];
			this->cartstate[i] = 0;
		}
		regenerate = true;
	}
	void asemble() {
		if (!regenerate) {
			for (int i = 0; i < 5; i++) {
				asmbT += cartstate[i] * assembleT[i];
				cartstate[i] = 0;
				localstate[i] = 0;
			}
		}
		else {
			for (int i = 0; i < 5; i++) {
				int parts = cartstate[i] + localstate[i];
				asmbT += parts * assembleT[i];
				cartstate[i] = 0;
				localstate[i] = 0;

			}
		}
		product++;
		regenerate = false;
		this_thread::sleep_for(microseconds(asmbT));

	}
	void printmessgae(system_clock::duration& waittime) {
		//lock_guard<mutex> LG2(m3);
		system_clock::time_point time{ system_clock::now() };
		system_clock::duration Current{ time - start };
		Out << "current time is : " << duration_cast<microseconds>(Current).count() << " us" << endl;
		Out << "productworker id: " << this->id << endl;
		Out << "iteration :" << this->iter << endl;
		Out << "status: " << this->status << endl;
		Out << "accumulated waiting time is: " << duration_cast<microseconds>(waittime).count() << "us" << endl;
		//printf("Buffer State :(%d,%d,%d,%d,%d)\n",this->obs[0],this->obs[1],this->obs[2],this->obs[3],this->obs[4]);
		if (timeout) {
			//printf(" Pickup Order :(%d,%d,%d,%d,%d)\n", this->pickuporder[0], this->pickuporder[1], this->pickuporder[2], this->pickuporder[3], this->pickuporder[4]);
			Out << " Pickup Order : " << "(" << pickuporder[0] << "," << pickuporder[1] << "," << pickuporder[2] << "," << pickuporder[3] << "," << pickuporder[4] << ")" << endl;
			//printf("Buffer State :(%d,%d,%d,%d,%d)\n", bufferstate[0], bufferstate[1], bufferstate[2], bufferstate[3], bufferstate[4]);
			Out << " Buffer State : " << "(" << bufferstate[0] << "," << bufferstate[1] << "," << bufferstate[2] << "," << bufferstate[3] << "," << bufferstate[4] << ")" << endl;
			Out << " Local State : " << "(" << localstate[0] << "," << localstate[1] << "," << localstate[2] << "," << localstate[3] << "," << localstate[4] << ")" << endl;
			Out << " Cart State : " << "(" << cartstate[0] << "," << cartstate[1] << "," << cartstate[2] << "," << cartstate[3] << "," << cartstate[4] << ")" << endl;
			//printf(" Local State :(%d,%d,%d,%d,%d)\n", this->localstate[0], this->localstate[1], this->localstate[2], this->localstate[3], this->localstate[4]);
			//printf(" Cart State :(%d,%d,%d,%d,%d)\n", this->cartstate[0], this->cartstate[1], this->cartstate[2], this->cartstate[3], this->cartstate[4]);
		}
		else {
			//printf("Pickup Order :(%d,%d,%d,%d,%d)\n", this->opk[0], this->opk[1], this->opk[2], this->opk[3], this->opk[4]);
			Out << " Pickup Order : " << "(" << opk[0] << "," << opk[1] << "," << opk[2] << "," << opk[3] << "," << opk[4] << ")" << endl;
			Out << " Local State : " << "(" << localstate[0] << "," << localstate[1] << "," << localstate[2] << "," << localstate[3] << "," << localstate[4] << ")" << endl;
			//printf("Local State :(%d,%d,%d,%d,%d)\n", this->localstate[0], this->localstate[1], this->localstate[2], this->localstate[3], this->localstate[4]);
			Out << " Cart State : " << "(" << ocs[0] << "," << ocs[1] << "," << ocs[2] << "," << ocs[3] << "," << ocs[4] << ")" << endl;
			//printf("Cart State :(%d,%d,%d,%d,%d)\n", this->ocs[0], this->ocs[1], this->ocs[2], this->ocs[3], this->ocs[4]);
			Out << " Buffer State : " << "(" << obs[0] << "," << obs[1] << "," << obs[2] << "," << obs[3] << "," << obs[4] << ")" << endl;
			//printf("Buffer State :(%d,%d,%d,%d,%d)\n", this->obs[0], this->obs[1], this->obs[2], this->obs[3], this->obs[4]);
		}
		if (!regenerate) {
			//printf("Updated Pickup Order :(%d,%d,%d,%d,%d)\n", this->pickuporder[0], this->pickuporder[1], this->pickuporder[2], this->pickuporder[3], this->pickuporder[4]);
			Out << "Updated Pickup Order : " << "(" << pickuporder[0] << "," << pickuporder[1] << "," << pickuporder[2] << "," << pickuporder[3] << "," << pickuporder[4] << ")" << endl;
			//cout << "brand new order" << endl;
		}
		else {
			//printf("Updated Pickup Order :(%d,%d,%d,%d,%d)\n", this->realpickup[0], this->realpickup[1], this->realpickup[2], this->realpickup[3], this->realpickup[4]);
			Out << "Updated Pickup Order : " << "(" << realpickup[0] << "," << realpickup[1] << "," << realpickup[2] << "," << realpickup[3] << "," << realpickup[4] << ")" << endl;
			//cout << "reuse order" << endl;
		}
		//printf("Updated Pickup Order :(%d,%d,%d,%d,%d)\n", pickuporder[0], pickuporder[1], pickuporder[2], pickuporder[3], pickuporder[4]);
		Out << "Updated Buffer State : " << "(" << bufferstate[0] << "," << bufferstate[1] << "," << bufferstate[2] << "," << bufferstate[3] << "," << bufferstate[4] << ")" << endl;
		Out << "Updated Local State : " << "(" << localstate[0] << "," << localstate[1] << "," << localstate[2] << "," << localstate[3] << "," << localstate[4] << ")" << endl;
		Out << "Updated Cart State : " << "(" << cartstate[0] << "," << cartstate[1] << "," << cartstate[2] << "," << cartstate[3] << "," << cartstate[4] << ")" << endl;
		Out << "product number is " << product << endl;
		Out << endl;
	}
	void printmessgae1() {
		//lock_guard<mutex> LG2(m3);
		system_clock::time_point time{ system_clock::now() };
		system_clock::duration Current{ time - start };
		Out << "current time is : " << duration_cast<microseconds>(Current).count() << " us" << endl;
		Out << "productworker id: " << this->id << endl;
		Out << "iteration :" << this->iter << endl;
		Out << "status: " << this->status << endl;
		Out << "accumulated waiting time is: " << 0 << "us" << endl;
		//printf("Buffer State :(%d,%d,%d,%d,%d)\n",this->obs[0],this->obs[1],this->obs[2],this->obs[3],this->obs[4]);
		if (timeout) {
			//printf(" Pickup Order :(%d,%d,%d,%d,%d)\n", this->pickuporder[0], this->pickuporder[1], this->pickuporder[2], this->pickuporder[3], this->pickuporder[4]);
			Out << " Pickup Order : " << "(" << pickuporder[0] << "," << pickuporder[1] << "," << pickuporder[2] << "," << pickuporder[3] << "," << pickuporder[4] << ")" << endl;
			//printf("Buffer State :(%d,%d,%d,%d,%d)\n", bufferstate[0], bufferstate[1], bufferstate[2], bufferstate[3], bufferstate[4]);
			Out << " Buffer State : " << "(" << bufferstate[0] << "," << bufferstate[1] << "," << bufferstate[2] << "," << bufferstate[3] << "," << bufferstate[4] << ")" << endl;
			Out << " Local State : " << "(" << localstate[0] << "," << localstate[1] << "," << localstate[2] << "," << localstate[3] << "," << localstate[4] << ")" << endl;
			Out << " Cart State : " << "(" << cartstate[0] << "," << cartstate[1] << "," << cartstate[2] << "," << cartstate[3] << "," << cartstate[4] << ")" << endl;
			//printf(" Local State :(%d,%d,%d,%d,%d)\n", this->localstate[0], this->localstate[1], this->localstate[2], this->localstate[3], this->localstate[4]);
			//printf(" Cart State :(%d,%d,%d,%d,%d)\n", this->cartstate[0], this->cartstate[1], this->cartstate[2], this->cartstate[3], this->cartstate[4]);
		}
		else {
			//printf("Pickup Order :(%d,%d,%d,%d,%d)\n", this->opk[0], this->opk[1], this->opk[2], this->opk[3], this->opk[4]);
			Out << " Pickup Order : " << "(" << opk[0] << "," << opk[1] << "," << opk[2] << "," << opk[3] << "," << opk[4] << ")" << endl;
			Out << " Local State : " << "(" << localstate[0] << "," << localstate[1] << "," << localstate[2] << "," << localstate[3] << "," << localstate[4] << ")" << endl;
			//printf("Local State :(%d,%d,%d,%d,%d)\n", this->localstate[0], this->localstate[1], this->localstate[2], this->localstate[3], this->localstate[4]);
			Out << " Cart State : " << "(" << ocs[0] << "," << ocs[1] << "," << ocs[2] << "," << ocs[3] << "," << ocs[4] << ")" << endl;
			//printf("Cart State :(%d,%d,%d,%d,%d)\n", this->ocs[0], this->ocs[1], this->ocs[2], this->ocs[3], this->ocs[4]);
			Out << " Buffer State : " << "(" << obs[0] << "," << obs[1] << "," << obs[2] << "," << obs[3] << "," << obs[4] << ")" << endl;
			//printf("Buffer State :(%d,%d,%d,%d,%d)\n", this->obs[0], this->obs[1], this->obs[2], this->obs[3], this->obs[4]);
		}
		if (!regenerate) {
			//printf("Updated Pickup Order :(%d,%d,%d,%d,%d)\n", this->pickuporder[0], this->pickuporder[1], this->pickuporder[2], this->pickuporder[3], this->pickuporder[4]);
			Out << "Updated Pickup Order : " << "(" << pickuporder[0] << "," << pickuporder[1] << "," << pickuporder[2] << "," << pickuporder[3] << "," << pickuporder[4] << ")" << endl;
			//cout << "brand new order" << endl;
		}
		else {
			//printf("Updated Pickup Order :(%d,%d,%d,%d,%d)\n", this->realpickup[0], this->realpickup[1], this->realpickup[2], this->realpickup[3], this->realpickup[4]);
			Out << "Updated Pickup Order : " << "(" << realpickup[0] << "," << realpickup[1] << "," << realpickup[2] << "," << realpickup[3] << "," << realpickup[4] << ")" << endl;
			//cout << "reuse order" << endl;
		}
		//printf("Updated Pickup Order :(%d,%d,%d,%d,%d)\n", pickuporder[0], pickuporder[1], pickuporder[2], pickuporder[3], pickuporder[4]);
		Out << "Updated Buffer State : " << "(" << bufferstate[0] << "," << bufferstate[1] << "," << bufferstate[2] << "," << bufferstate[3] << "," << bufferstate[4] << ")" << endl;
		Out << "Updated Local State : " << "(" << localstate[0] << "," << localstate[1] << "," << localstate[2] << "," << localstate[3] << "," << localstate[4] << ")" << endl;
		Out << "Updated Cart State : " << "(" << cartstate[0] << "," << cartstate[1] << "," << cartstate[2] << "," << cartstate[3] << "," << cartstate[4] << ")" << endl;
		Out << "product number is " << product << endl;
		Out << endl;
	}
	void test() {
		srand(system_clock::now().time_since_epoch().count());
		for (int i = 0; i < 5; i++) {
			iter = i + 1;
			if (!regenerate) {
				cartfull = false;
				timeout = false;
				{
					unique_lock<mutex>UG1(m1);
					this->pickup();
					this->check1();
					if (avalibility)
					{
						status = statusList[0];
						//lock_guard<mutex>lg(z1);
						this->movefrombuffer();
						this->printmessgae1();
					}
					if(!avalibility||!cartfull) {
						//unique_lock<mutex>UG1(m1);
						while (!cartfull) {
							system_clock::time_point startTime1{ system_clock::now() };
							auto wait_time = cv2.wait_for(UG1, microseconds(MaxTimeProduct));
							if (wait_time == cv_status::timeout) {
								system_clock::time_point wakeUpTime1{ system_clock::now() };
								system_clock::duration waitTime1{ wakeUpTime1 - startTime1 };
								this->movetolocal();
								status = statusList[2];
								timeout = true;
								this->printmessgae(waitTime1);
								//regenerate = true;
								//timeout = true;
								break;
							}
							else {

								this->check1();
								system_clock::time_point wakeUpTime2{ system_clock::now() };
								system_clock::duration waitTime2{ wakeUpTime2 - startTime1 };
								if (avalibility) {
									this->movefrombuffer();
									status = statusList[1];
									this->printmessgae(waitTime2);
								}
								else {
									continue;
								}

							}

						}
					}
					if (!timeout)this->asemble();
					//timeout = false;
					cv1.notify_all();
				}
				//cv1.notify_all();
			}
			else {
				timeout = false;
				cartfull = false;
				//this->regenerator();
				{
					unique_lock<mutex>UG1(m1);
					this->regenerator();
					this->check2();
					if (avalibility)
					{
						status = statusList[0];
						//lock_guard<mutex>lg(z1);
						this->movefrombuffer();
						this->printmessgae1();
					}
					if (!avalibility || !cartfull) {
						//unique_lock<mutex>UG1(m1);
						while (!cartfull) {
							system_clock::time_point startTime2{ system_clock::now() };
							auto wait_time = cv2.wait_for(UG1, microseconds(MaxTimeProduct));
							if (wait_time == cv_status::timeout) {
								system_clock::time_point wakeUpTime3{ system_clock::now() };
								system_clock::duration waitTime3{ wakeUpTime3 - startTime2 };
								this->movetolocal();
								status = statusList[2];
								timeout = true;
								this->printmessgae(waitTime3);
								//regenerate = true;
								//timeout = true;
								break;
							}
							else {
								system_clock::time_point wakeUpTime4{ system_clock::now() };
								system_clock::duration waitTime4{ wakeUpTime4 - startTime2 };
								this->check2();
								if (avalibility) {
									this->movefrombuffer();
									status = statusList[1];
									this->printmessgae(waitTime4);
								}
								else {
									continue;
								}

							}

						}
					}
					if (!timeout)this->asemble();
					//timeout = false;
					cv1.notify_all();
				}
				//cv1.notify_all();
			}
		}



	}

};







int main() {
	vector<thread>Partworker;
	vector<thread>Productworker;
	vector<productworker>V1;
	vector<partworker>V2;

	for (int i = 0; i < 16; i++) {
		productworker worker;
		worker.id = i;
		V1.push_back(worker);
	}
	for (int i = 0; i < 20; i++) {

		partworker worker1;
		worker1.id = i;
		V2.push_back(worker1);
	}
	for (int i = 0; i < 16; i++) {
		Productworker.emplace_back(&productworker::test, &V1[i]);
	}
	for (int i = 0; i < 20; i++) {
		Partworker.emplace_back(&partworker::test, &V2[i]);
	}
	start = system_clock::now();
	for (auto& i : Partworker)i.join();
	for (auto& i : Productworker)i.join();
	cout << "Finish!" << endl;
	return 0;
}
