#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <vector>
#include <chrono>
#include <atomic>

using namespace std;

mutex m1, m2;

class Buffer
{
public:
    const vector<int> buffer_capacity = {5, 5, 4, 3, 3};
    vector<int> buffer_state;
    int total_complete_products;

    Buffer()
    {
        buffer_state = {0, 0, 0, 0, 0};
        total_complete_products = 0;

        return;
    }
};

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

class PartWorker
{
private:
    int id;
    int size_of_load_order;
    int wait_time;
    int max_wait_time;

public:
    vector<int> load_order;
    vector<int> local_state;

    int getId()
    {
        return id;
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

    // randomly fill the load till the size of load order
    void reloadLoadOrder();

    void partWorkerWorkflow(Buffer &buffer, const vector<Part> &parts);

    PartWorker()
    {
        size_of_load_order = 5;
        wait_time = 0;
        load_order = vector<int>(size_of_load_order, 0);
        local_state = vector<int>(size_of_load_order, 0);
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
    vector<int> cart_state;

    int getId()
    {
        return id;
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

    // randomly fill the load till the size of load order
    void reloadAssemblyOrder();

    void productWorkerWorkflow(Buffer &buffer, const vector<Part> &parts);

    ProductWorker()
    {
        size_of_assembly_order = 5;
        wait_time = 0;
        assembly_order = vector<int>(size_of_assembly_order, 0);
        cart_state = vector<int>(size_of_assembly_order, 0);
        reloadAssemblyOrder();

        return;
    }

    ProductWorker(int id, int max_wait_time) : ProductWorker()
    {
        this->id = id;
        this->max_wait_time = max_wait_time;
    }
};

// move parts from a worker to the buffer
void loadBuffer(PartWorker worker, Buffer buffer)
{
}

void testPartWorker(PartWorker &w1)
{
    cout << "PartWorker load order: ";

    for (int i : w1.load_order)
    {
        cout << i << ", ";
    }

    cout << endl;

    cout << "PartWorker local state: ";

    for (int i : w1.local_state)
    {
        cout << i << ", ";
    }

    cout << endl;

    return;
}

void testProductWorker(ProductWorker &w2)
{

    cout << "ProductWorker assembly order: ";

    for (int i : w2.assembly_order)
    {
        cout << i << ", ";
    }

    cout << endl;

    cout << "ProductWorker cart state: ";

    for (int i : w2.cart_state)
    {
        cout << i << ", ";
    }

    cout << endl;

    return;
}

int main()
{
    srand(time(NULL));

    // parts and buffer initialization
    vector<Part> parts{Part(500, 200, 600), Part(500, 200, 600), Part(600, 300, 700), Part(600, 300, 700), Part(700, 400, 800)};
    Buffer buffer;

    // have the works
    vector<PartWorker> part_workers;
    vector<ProductWorker> product_workers;
    for (int i = 0; i <= 8; i++)
        part_workers.push_back(PartWorker(i, 600));
    for (int i = 0; i <= 8; i++)
        product_workers.push_back(ProductWorker(i, 600));

    // push workers into their workflow
    vector<thread> part_worker_threads;
    vector<thread> product_worker_threads;
    for (int i = 0; i < part_workers.size(); i++)
        part_worker_threads.emplace_back(&PartWorker::partWorkerWorkflow, &part_workers[i], ref(buffer), ref(parts));
    for (int i = 0; i < product_workers.size(); i++)
        product_worker_threads.emplace_back(&ProductWorker::productWorkerWorkflow, &product_workers[i], ref(buffer), ref(parts));
    for (thread &i : part_worker_threads)
        i.join();
    for (thread &i : product_worker_threads)
        i.join();

    // testPartWorker(part_workers[0]);
    // testProductWorker(product_workers[0]);
    cout << "END!!!!!!!!-----------------------" << endl;

    return 0;
}

void PartWorker::partWorkerWorkflow(Buffer &buffer, const vector<Part> &parts)
{
    unique_lock<mutex> UG1(m1);
    // sleep

    return;
}
void ProductWorker::productWorkerWorkflow(Buffer &buffer, const vector<Part> &parts)
{
    unique_lock<mutex> UG2(m2);

    return;
}

void PartWorker::reloadLoadOrder()
{
    load_order = local_state;

    // calcuate the size we need to reload
    int size_to_reload = size_of_load_order;
    for (int order : load_order)
    {
        size_to_reload -= order;
    }

    // reload the load order
    while (size_to_reload-- > 0)
    {
        load_order[rand() % 5]++;
    }

    return;
}

void ProductWorker::reloadAssemblyOrder()
{
    assembly_order = cart_state;

    // calcuate the size we need to reload
    int size_to_reload = size_of_assembly_order;
    for (int order : assembly_order)
    {
        size_to_reload -= order;
    }

    // calcuate the number of type we want to reload
    int type_to_reload = 0;
    int type_already_reloaded = 0;
    vector<bool> types(size_of_assembly_order, false);
    for (int i = 0; i < assembly_order.size(); i++)
    {
        if (assembly_order[i] != 0)
        {
            types[i] = true;
            type_already_reloaded++;
        }
    }

    type_to_reload = type_already_reloaded < 3 ? type_to_reload = (rand() % 2) + 2 : 3;

    // decide what the types are
    while (type_already_reloaded < type_to_reload)
    {
        int type = rand() % size_of_assembly_order;

        if (!types[type])
        {
            types[type] = true;
            type_already_reloaded++;
        }
    }

    // reload the load order
    while (size_to_reload > 0)
    {
        int type = rand() % 5;

        if (types[type])
        {
            assembly_order[type]++;
            size_to_reload--;
        }
    }
    // we need to make sure all type having at least one individual existing
    for (int type = 0; type < size_of_assembly_order; type++)
    {
        while (types[type] && assembly_order[type] == 0)
        {
            int type_to_reduce_individual = rand() % size_of_assembly_order;

            if (assembly_order[type_to_reduce_individual] > 1)
            {
                assembly_order[type_to_reduce_individual]--;
                assembly_order[type]++;
            }
        }
    }

    return;
}