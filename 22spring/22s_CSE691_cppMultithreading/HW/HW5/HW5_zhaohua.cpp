// HW5_CES691.cpp by Zhaohua Zhang SUID:483906542
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


ofstream out("log_hw5.txt");
mutex m1, m2, m3;
int product = 0;
condition_variable cv1, cv2;
const int MaxTimePart{ 18000 }, MaxTimeProduct{ 20000 };
vector<int>ProduceT = { 500,500,600,600,700 };
vector<int>MoveT = { 200,200,300,300,400 };
vector<int>assembleT = { 600,600,700,700,800 };
const string statusList[3] = { "New Order","Wakeup-Notified"," Wakeup-Timeout" };
system_clock::time_point start;
class partworker {
public:
    int id;
    string status;
    vector<int>loadorder = { 0,0,0,0,0 };
    vector<int>remainpart = { 0,0,0,0,0 };
    vector<int>originload = { 0,0,0,0,0 };
    vector<int>originbuffer = { 0,0,0,0,0 };
    int movet = 0; int partt = 0;
    bool remain = false;
    bool wakeup = false;
    bool timeout = false;
    int iter = 0;

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
    void regenerator() {
        int current = 0;
        partt = 0;
        for (int i = 0; i < 5; i++) {
            current += this->loadorder[i];
            originload[i] = loadorder[i];
        }
        //srand(300);
        for (int i = 0; i < 5 - current; i++) {
            this->loadorder[rand() % 5] += 1;
        }
        for (int i = 0; i < 5; i++) {

            partt += loadorder[i] * ProduceT[i] - remainpart[i] * ProduceT[i];
        }
        this_thread::sleep_for(microseconds(partt));
        this->remain = true;
    }

};
class productworker {
public:
    int id;
    string status;
    vector<int>pickuporder = { 0,0,0,0,0 };
    vector<int>realpickup = { 0,0,0,0,0 };
    vector<int>cartstate = { 0,0,0,0,0 };
    vector<int>localstate = { 0,0,0,0,0 };
    vector<int>opk = { 0,0,0,0,0 };
    vector<int>ocs = { 0,0,0,0,0 };
    vector<int>obs = { 0,0,0,0,0 };
    vector<int>ols = { 0,0,0,0,0 };
    int asmbT = 0;
    int iter = 0;
    bool timeout = false;
    bool wakeup = false;
    bool cartfull = false;
    bool regenerate = false;
    void pickup() {
        int TYPE[2] = { 2,3 };
        //srand(this->id);
        int n = rand() % 2;
        for (int i = 0; i < 5; i++) {
            this->cartstate[i] = 0;
            this->localstate[i] = 0;
            this->ols[i] = 0;
        }
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
            cartstate[i] = 0;
            ocs[i] = 0;
            ols[i] = localstate[i];
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
    void asemble() {
        /*for (int i = 0; i < 5; i++) {
            this->ocs[i] = this->cartstate[i];
        }*/
        if (!regenerate) {
            for (int i = 0; i < 5; i++) {
                asmbT += cartstate[i] * assembleT[i];
                //cartstate[i] = 0;
                //localstate[i] = 0;
            }
        }
        else {
            for (int i = 0; i < 5; i++) {
                int parts = cartstate[i] + localstate[i];
                asmbT += parts * assembleT[i];
                //cartstate[i] = 0;
                //localstate[i] = 0;

            }
        }
        product++;
        //regenerate = false;
        this_thread::sleep_for(microseconds(asmbT));

    }
    void movetolocal() {
        int n = 0;
        int movet = 0;
        for (int i = 0; i < 5; i++) {
            if (this->cartstate[i] == 0) {
                n++;
            }
            this->ocs[i] = this->cartstate[i];
            if (!regenerate) {
                this->ols[i] = 0;
                this->localstate[i] = 0;
                this->opk[i] = this->pickuporder[i];
            }
            else {
                this->ols[i] = this->localstate[i];
                this->opk[i] = this->realpickup[i];
            }
        }
        if (n == 5) {
            regenerate = false;
            //cout << "abort!" << endl;
            for (int i = 0; i < 5; i++) {
                this->localstate[i] = 0;
                this->ols[i] = 0;
                this->cartstate[i] = 0;
            }
            return;
        }
        for (int i = 0; i < 5; i++) {
            this->ols[i] = this->localstate[i];
            this->ocs[i] = this->cartstate[i];
            this->localstate[i] += this->cartstate[i];
            //this->ols[i] = this->localstate[i];
            movet += cartstate[i] * MoveT[i];
            this->cartstate[i] = 0;
            
        }
        for (int i = 0; i < 5; i++) {
            if (!regenerate) {
                this->opk[i]= this->pickuporder[i];
            }
            else {
                this->opk[i]= this->realpickup[i];
            }
        }
        regenerate = true;
        this_thread::sleep_for(microseconds(movet));
    }
};
class Buffer {
public:
    vector<int>bufferstate = { 0,0,0,0,0 };
    vector<int>buffercapacity = { 5,5,4,3,3 };
    bool Aval_part=false;
    bool Aval_product=false;
    void partworkerprint(partworker& worker, system_clock::time_point& current, system_clock::duration&waittime) {
        lock_guard<mutex> LG2(m3);
        system_clock::duration Current{ current - start };
        out << "current time is : " << duration_cast<microseconds>(Current).count() << " us" << endl;
        out << "partworker id: " << worker.id << endl;
        out << "iteration :" << worker.iter << endl;
        out << "status: " << worker.status << endl;
        out << "accumulated waiting time is: " << duration_cast<microseconds>(waittime).count() << "us" << endl;
        if (!worker.timeout) {
            out << "Buffer State : " << "(" << worker.originbuffer[0] << "," << worker.originbuffer[1] << "," << worker.originbuffer[2] << "," << worker.originbuffer[3] << "," << worker.originbuffer[4] << ")" << endl;
            out << "load order: " << "(" << worker.originload[0] << "," << worker.originload[1] << "," << worker.originload[2] << "," << worker.originload[3] << "," << worker.originload[4] << ")" << endl;
            out << "Updated Buffer State : " << "(" << this->bufferstate[0] << "," << this->bufferstate[1] << "," << this->bufferstate[2] << "," << this->bufferstate[3] << "," << this->bufferstate[4] << ")" << endl;
            out << "Updated load order: " << "(" << worker.loadorder[0] << "," << worker.loadorder[1] << "," << worker.loadorder[2] << "," << worker.loadorder[3] << "," << worker.loadorder[4] << ")" << endl;
        }
        else {
            out << "Buffer State :  " << "(" << this->bufferstate[0] << "," << this->bufferstate[1] << "," << this->bufferstate[2] << "," << this->bufferstate[3] << "," << this->bufferstate[4] << ")" << endl;
            out << "load order:" << "(" << worker.loadorder[0] << "," << worker.loadorder[1] << "," << worker.loadorder[2] << "," << worker.loadorder[3] << "," << worker.loadorder[4] << ")" << endl;
            out << "Updated Buffer State : " << "(" << this->bufferstate[0] << "," << this->bufferstate[1] << "," << this->bufferstate[2] << "," << this->bufferstate[3] << "," << this->bufferstate[4] << ")" << endl;
            out << "Updated load order:" << "(" << worker.loadorder[0] << "," << worker.loadorder[1] << "," << worker.loadorder[2] << "," << worker.loadorder[3] << "," << worker.loadorder[4] << ")" << endl;
        }
        out << endl;
    }
    void productprint(productworker& worker, system_clock::time_point& current, system_clock::duration&waittime,system_clock::duration&currt2) {
        lock_guard<mutex> LG2(m3);
        system_clock::duration Current{ current - start };
        out << "current time is : " << duration_cast<microseconds>(Current).count() << " us" << endl;
        out << "productworker id: " << worker.id << endl;
        out << "iteration :" << worker.iter << endl;
        out << "status: " << worker.status << endl;
        out << "accumulated waiting time is: " << duration_cast<microseconds>(waittime).count() << "us" << endl;
       
        if (worker.timeout) {
            out << " Pickup Order : " << "(" << worker.opk[0] << "," << worker.opk[1] << "," << worker.opk[2] << "," << worker.opk[3] << "," << worker.opk[4] << ")" << endl;
            out << " Buffer State : " << "(" << bufferstate[0] << "," << bufferstate[1] << "," << bufferstate[2] << "," << bufferstate[3] << "," << bufferstate[4] << ")" << endl;
            out << " Local State : " << "(" << worker.ols[0] << "," << worker.ols[1] << "," << worker.ols[2] << "," << worker.ols[3] << "," << worker.ols[4] << ")" << endl;
            out << " Cart State : " << "(" << worker.ocs[0] << "," << worker.ocs[1] << "," << worker.ocs[2] << "," << worker.ocs[3] << "," << worker.ocs[4] << ")" << endl;
            out << " Updated Pickup Order : " << "(" << worker.opk[0] << "," << worker.opk[1] << "," << worker.opk[2] << "," << worker.opk[3] << "," << worker.opk[4] << ")" << endl;
            out << " Updated Buffer State : " << "(" << bufferstate[0] << "," << bufferstate[1] << "," << bufferstate[2] << "," << bufferstate[3] << "," << bufferstate[4] << ")" << endl;
            out << " Updated Local State : " << "(" << worker.ols[0] << "," << worker.ols[1] << "," << worker.ols[2] << "," << worker.ols[3] << "," << worker.ols[4] << ")" << endl;
            out << " Updated Cart State : " << "(" << worker.ocs[0] << "," << worker.ocs[1] << "," << worker.ocs[2] << "," << worker.ocs[3] << "," << worker.ocs[4] << ")" << endl;
        }
        else {
            out << " Pickup Order : " << "(" << worker.opk[0] << "," << worker.opk[1] << "," << worker.opk[2] << "," << worker.opk[3] << "," << worker.opk[4] << ")" << endl;
            out << " Local State : " << "(" << worker.ols[0] << "," << worker.ols[1] << "," << worker.ols[2] << "," << worker.ols[3] << "," << worker.ols[4] << ")" << endl;
            out << " Cart State : " << "(" << worker.ocs[0] << "," << worker.ocs[1] << "," << worker.ocs[2] << "," << worker.ocs[3] << "," << worker.ocs[4] << ")" << endl;
            out << " Buffer State : " << "(" << worker.obs[0] << "," << worker.obs[1] << "," << worker.obs[2] << "," << worker.obs[3] << "," << worker.obs[4] << ")" << endl;
            if (!worker.regenerate) {
                out << "Updated Pickup Order : " << "(" << worker.pickuporder[0] << "," << worker.pickuporder[1] << "," << worker.pickuporder[2] << "," << worker.pickuporder[3] << "," << worker.pickuporder[4] << ")" << endl;
            }//现在要改这个地方
            else {
                out << "Updated Pickup Order : " << "(" << worker.realpickup[0] << "," << worker.realpickup[1] << "," << worker.realpickup[2] << "," << worker.realpickup[3] << "," << worker.realpickup[4] << ")" << endl;
            }
            out << "Updated Buffer State : " << "(" << bufferstate[0] << "," << bufferstate[1] << "," << bufferstate[2] << "," << bufferstate[3] << "," << bufferstate[4] << ")" << endl;
            out << "Updated Local State :  " << "(" << worker.localstate[0] << "," << worker.localstate[1] << "," << worker.localstate[2] << "," << worker.localstate[3] << "," << worker.localstate[4] << ")" << endl;
            out << "Updated Cart State : " << "(" << worker.cartstate[0] << "," << worker.cartstate[1] << "," << worker.cartstate[2] << "," << worker.cartstate[3] << "," << worker.cartstate[4] << ")" << endl;
        }
       
        if (worker.cartfull) {
            out << "current time is : " << duration_cast<microseconds>(currt2).count() << " us" << endl;
            out << "Updated Local State :  " << "(" << 0 << "," << 0 << "," << 0 << "," << 0 << "," << 0 << ")" << endl;
            out << "Updated Cart State : " << "(" << 0 << "," << 0 << "," << 0 << "," << 0 << "," << 0 << ")" << endl;
        }
        if (worker.timeout) {
            out << "current time is : " << duration_cast<microseconds>(currt2).count() << " us" << endl;
            out << "Updated Cart State : " << "(" << 0 << "," << 0 << "," << 0 << "," << 0 << "," << 0 << ")" << endl;
            out << "Updated Local State :  " << "(" << worker.localstate[0] << "," << worker.localstate[1] << "," << worker.localstate[2] << "," << worker.localstate[3] << "," << worker.localstate[4] << ")" << endl;
        }
        out << "product number is " << product << endl;
        out << endl;
    }
    void load(partworker&worker) {
        //worker.movet = 0;
        //unique_lock<mutex>UG1(m1);
        system_clock::time_point currenttime;
        system_clock::time_point wakeuptime;
        system_clock::duration wait;
        while (worker.remain) {
            unique_lock<mutex>UG1(m1);
            this->check_aval_part(worker);
            worker.movet = 0;
            if (Aval_part) {
                //unique_lock<mutex>UG1(m1);
                currenttime = system_clock::now();
                for (int i = 0; i < 5; i++) {
                    worker.originbuffer[i] = bufferstate[i];
                    worker.originload[i] = worker.loadorder[i];
                }
                for (int i = 0; i < 5; i++) {

                    if (bufferstate[i] + worker.loadorder[i] <= buffercapacity[i]) {
                        bufferstate[i] += worker.loadorder[i];
                        worker.movet += MoveT[i] * worker.loadorder[i];
                        worker.loadorder[i] = 0;

                        //this->remainpart[i] = 0;

                    }
                    else if (bufferstate[i] + worker.loadorder[i] > buffercapacity[i] && bufferstate[i] != buffercapacity[i]) {
                        int increment = buffercapacity[i] - bufferstate[i];
                        worker.loadorder[i] = bufferstate[i] + worker.loadorder[i] - buffercapacity[i];
                        bufferstate[i] = buffercapacity[i];
                        worker.movet += MoveT[i] * increment;
                        //this->remainpart[i] = this->loadorder[i];

                    }

                }
                if (worker.wakeup) {
                    worker.status = statusList[1];
                    this->partworkerprint(worker,currenttime,wait);
                }
                else {
                    worker.status = statusList[0];
                    system_clock::time_point t1 = system_clock::now();
                    system_clock::time_point t2 = system_clock::now();
                    system_clock::duration t = t2 - t1;
                    this->partworkerprint(worker,currenttime,t);
                }
                this_thread::sleep_for(microseconds(worker.movet));
                for (int i = 0; i < 5; i++) {
                    worker.remainpart[i] = worker.loadorder[i];
                }
                worker.checkremain();
                cv2.notify_all();
            }
            else {
                //cv2.notify_all();
                worker.wakeup = false;
                system_clock::time_point startTime1{ system_clock::now() };
                auto wait_time = cv1.wait_for(UG1, microseconds(MaxTimePart));
                if (wait_time == cv_status::timeout) {
                system_clock::time_point timeout{ system_clock::now() };
                system_clock::duration waittime{ timeout - startTime1 };
                worker.status = statusList[2];
                worker.timeout = true;
                                //print something
                this->partworkerprint(worker,timeout,waittime);
                               
                                //worker.moveback();
                break;
                }
                else {
                    worker.wakeup = true;
                    system_clock::time_point wakeupt{ system_clock::now() };
                    wait = wakeupt - startTime1;
                    continue;
                }

            }
        }
        worker.wakeup = false;
    };
    void pickup(productworker&worker) {
        system_clock::time_point currentt;
        system_clock::time_point timeout;
        system_clock::time_point wakeup;
        system_clock::time_point startW;
        system_clock::time_point currt2;
        //unique_lock<mutex>UG1(m1);
        while (!worker.cartfull) {
            unique_lock<mutex>UG1(m1);
            this->check_aval_product(worker);
            int carttotal = 0;
            if (Aval_product) {
                currentt = system_clock::now();
                for (int i = 0; i < 5; i++) {
                    worker.obs[i] = bufferstate[i];
                    worker.ocs[i] = worker.cartstate[i];
                    if (!worker.regenerate) {
                        worker.opk[i] = worker.pickuporder[i];
                    }
                    else {
                        worker.opk[i] = worker.realpickup[i];
                    }
                }
                if (!worker.regenerate) {
                    for (int i = 0; i < 5; i++) {
                        if (bufferstate[i] >= worker.pickuporder[i]) {
                            worker.cartstate[i] += worker.pickuporder[i];
                            bufferstate[i] -= worker.pickuporder[i];
                            worker.pickuporder[i] -= worker.pickuporder[i];
                        }
                        else if (bufferstate[i] < worker.pickuporder[i] && bufferstate[i] != 0) {
                            worker.cartstate[i] += bufferstate[i];
                            worker.pickuporder[i] -= bufferstate[i];
                            bufferstate[i] -= bufferstate[i];
                        }

                    }
                    for (int i = 0; i < 5; i++) {
                        carttotal += worker.cartstate[i];
                    }
                    if (carttotal == 5) {
                        worker.cartfull = true;
                        worker.asemble();
                        currt2 = system_clock::now();
                    }
                    else {
                        worker.cartfull = false;
                    }

                }
                else {
                    for (int i = 0; i < 5; i++) {
                        if (bufferstate[i] >= worker.realpickup[i]) {
                            worker.cartstate[i] += worker.realpickup[i];
                            bufferstate[i] -= worker.realpickup[i];
                            worker.realpickup[i] -= worker.realpickup[i];
                        }
                        else if (bufferstate[i] < worker.realpickup[i] && bufferstate[i] != 0) {
                            worker.cartstate[i] += bufferstate[i];
                            worker.realpickup[i] -= bufferstate[i];
                            bufferstate[i] -= bufferstate[i];
                        }

                    }
                    for (int i = 0; i < 5; i++) {
                        carttotal = carttotal + worker.cartstate[i] + worker.localstate[i];
                    }
                    if (carttotal == 5) {
                        worker.cartfull = true;
                        worker.asemble();
                        currt2 = system_clock::now();

                    }
                    else {
                        worker.cartfull = false;
                    }


                }
                if (worker.wakeup) {
                    system_clock::duration Awaitt{ wakeup - startW };
                    worker.status = statusList[1];
                    system_clock::duration current2{ currt2 - start };
                    this->productprint(worker,currentt,Awaitt,current2);
                }
                else {
                    worker.status = statusList[0];
                    system_clock::time_point t1 = system_clock::now();
                    system_clock::time_point t2 = system_clock::now();
                    system_clock::duration t = t2 - t1;
                    system_clock::duration current2{ currt2 - start };
                    this->productprint(worker,currentt,t,current2);
                }
                if (worker.cartfull) { worker.regenerate = false; }
                cv1.notify_all();
            }
            else {
                //cv1.notify_all();
                startW = system_clock::now();
                auto wait_time = cv2.wait_for(UG1, microseconds(MaxTimeProduct));
                if (wait_time == cv_status::timeout) {
                    worker.status = statusList[2];
                    timeout = system_clock::now();
                    system_clock::duration timeoutt{ timeout - startW };
                    worker.timeout = true;
                    worker.movetolocal();
                    system_clock::time_point time1 = system_clock::now();
                    system_clock::duration current12{ time1 - start };
                    this->productprint(worker,timeout,timeoutt,current12);
                    //worker.regenerate = true;
                    break;
                }
                else {
                    wakeup = system_clock::now();
                    worker.wakeup = true;
                    continue;
                }
            }
        }
        worker.wakeup = false;
       
    };
    void check_aval_part(partworker&worker) {
        int n = 0;
        //lock_guard<mutex>LG1(m1);
        for (int i = 0; i < 5; i++) {
            if (this->bufferstate[i] < this->buffercapacity[i] && worker.loadorder[i] != 0) {
                n++;
            }
        }
        if (n > 0) {
            Aval_part = true;
        }
        else {
            Aval_part = false;
        }
    };
    void check_aval_product(productworker&worker) {
        int n = 0;
        for (int i = 0; i < 5; i++) {
            if (!worker.regenerate) {
                if (bufferstate[i] != 0 && worker.pickuporder[i] != 0) {
                    n++;
                }
            }
            else {
                if (bufferstate[i] != 0 && worker.realpickup[i] != 0) {
                    n++;
                }
            }
        }
        if (n > 0) {
            Aval_product = true;
        }
        else {
            Aval_product = false;
        }
    };
 
};

void partworkercycle(partworker& worker, Buffer& buffer) {
    srand(system_clock::now().time_since_epoch().count());
    for (int i = 0; i < 5; i++) {
        worker.timeout = false;
        worker.wakeup = false;
        worker.iter++;
        worker.regenerator();
        buffer.load(worker);
        if (worker.timeout) {
            worker.moveback();
            continue;
        }
    }
}
void productworkercycle(productworker& worker, Buffer& buffer) {
    srand(system_clock::now().time_since_epoch().count());
    for (int i = 0; i < 5; i++) {
        worker.iter++;
        worker.timeout = false;
        worker.cartfull = false;
       /* int n = 0;
        for (int j = 0; j < 5; j++) {
            if (worker.localstate[i] == 0) {
                n++;
            }
        }
        if (n > 0) {
            worker.regenerate = true;
        }
        else {
            worker.regenerate = false;
        }*/
        if (!worker.regenerate) {
            worker.pickup();
            buffer.pickup(worker);
            if (worker.timeout) {
                continue;
            }
        }
        else {
            worker.regenerator();
            buffer.pickup(worker);
            if (worker.timeout) {
                continue;
            }
        }
    }
}

int main()
{
    
    vector<productworker>V2;
    vector<partworker>V1;
    vector<thread>Partworker;
    vector<thread>Productworker;
    Buffer buffer;
   int m = 16; int n = 20;
    for (int i = 0; i < m; i++) {
        productworker worker;
        worker.id = i;
        V2.push_back(worker);
    }
    for (int i = 0; i < n; i++) {

        partworker worker1;
        worker1.id = i;
        V1.push_back(worker1);
    }
    for (int i = 0; i < n; i++) {
        Partworker.emplace_back(partworkercycle, ref(V1[i]), ref(buffer));
    }
    for (int i = 0; i < m; i++) {
        Productworker.emplace_back(productworkercycle, ref(V2[i]), ref(buffer));
    }
    start = system_clock::now();
    for (auto& i : Partworker)i.join();
    for (auto& i : Productworker)i.join();
    cout << "Finish!" << endl;
    return 0;

}

