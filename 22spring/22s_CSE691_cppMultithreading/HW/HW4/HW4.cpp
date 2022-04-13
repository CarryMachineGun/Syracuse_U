#include <vector>
#include <thread>
#include <iostream>

using namespace std;

class PartWorker
{
private:
    int id;
    int size_of_load_order;
    int wait_time;
    int max_wait_time;

public:
    vector<int> load_order;

    int getId()
    {
        return id;
    }

    // randomly fill the load till the size of load order
    void reloadLoadOrder()
    {
        //calcuate the size we need to reload
        int size_to_reload = size_of_load_order;
        for (int order : load_order)
        {
            size_to_reload -= order;
        }

        //reload the load order
        srand (time(NULL));
        while (size_to_reload-- > 0)
        {
            load_order[rand() % 5]++;
        }

        return;
    }

    void resetWaitTime()
    {
        wait_time = 0;

        return;
    }

    bool isWaitOverMax()
    {
        return wait_time >= max_wait_time;
    }

    PartWorker()
    {
        size_of_load_order = 5;
        wait_time = 0;
        load_order = {0, 0, 0, 0, 0};
        reloadLoadOrder();

        return;
    }

    PartWorker(int id, int max_wait_time) : PartWorker()
    {
        this->id = id;
        this->max_wait_time = max_wait_time;

        return;
    }
};

class ProductWorker
{
private:
    int id;
    int size_of_assembly_order;
    int wait_time;
    int max_wait_time;

public:
    vector<int> assembly_order;

    ProductWorker(){
        size_of_assembly_order = 5;
        wait_time = 0;
        assembly_order = {0, 0, 0, 0, 0};

        return;
    }

    ProductWorker(int id):ProductWorker()
    {
        this->id = id;
    }
};

class Buffer
{
public:
    const vector<int> buffer_capacity = {5, 5, 4, 3, 3};
    vector<int> buffer_state;

    Buffer()
    {
        buffer_state = {0, 0, 0, 0, 0};

        return;
    }
};

//move parts from a worker to the buffer 
void loadBuffer(PartWorker worker, Buffer buffer){

}

class Part
{
public:
    int producting_time_comsumption;
    int moving_time_consumption;
    int assembly_time_comsumption;

    Part(int producting_time_comsumption, int moving_time_consumption, int assembly_time_comsumption)
    {
        this->producting_time_comsumption = producting_time_comsumption;
        this->moving_time_consumption = moving_time_consumption;
        this->assembly_time_comsumption = assembly_time_comsumption;

        return;
    }
};

int main()
{
    // part attribute initialization
    Part A(500, 200, 600), B(500, 200, 600), C(600, 300, 700), D(600, 300, 700), E(700, 400, 800);
    Buffer buffer;


    PartWorker w1(1, 200);

    for(int i : w1.load_order){
        cout << i << ", ";
    }

    cout << endl;

    // thread T1{&PartWorker::test, &work_a};
    // T1.join();

    return 0;
}