#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <vector>
#include <chrono>
#include <atomic>

using namespace std;
using namespace chrono;

mutex m1, m2, buffer_lock;
condition_variable cv1, cv2;

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
    int max_wait_time;

public:
    vector<int> load_order;
    vector<int> local_state;

    int getId()
    {
        return id;
    }

    // randomly fill the load till the size of load order
    void reloadLoadOrder();

    void partWorkerWorkflow(Buffer &buffer, const vector<Part> &parts);

    PartWorker()
    {
        size_of_load_order = 5;
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
    int max_wait_time;

public:
    vector<int> assembly_order;
    vector<int> cart_state;

    int getId()
    {
        return id;
    }

    // randomly fill the load till the size of load order
    void reloadAssemblyOrder();

    void productWorkerWorkflow(Buffer &buffer, const vector<Part> &parts);

    ProductWorker()
    {
        size_of_assembly_order = 5;
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

void PartWorkerScheduler(PartWorker &worker, Buffer &buffer, vector<Part> &parts, int num_of_iteration)
{
    // each worker to finish 5 iterations
    // int num_of_iteration = 5;

    while (num_of_iteration-- > 0)
    {
        worker.partWorkerWorkflow(buffer, parts);
    }

    return;
}

void ProductWorkerScheduler(ProductWorker &worker, Buffer &buffer, vector<Part> &parts, int num_of_iteration)
{
    // each worker to finish 5 iterations
    // int num_of_iteration = 5;

    while (num_of_iteration-- > 0)
    {
        worker.productWorkerWorkflow(buffer, parts);
    }

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
    int num_of_iteration = 5;
    vector<thread> part_worker_threads;
    vector<thread> product_worker_threads;
    for (int i = 0; i < part_workers.size(); i++)
        part_worker_threads.emplace_back(PartWorkerScheduler, ref(part_workers[i]), ref(buffer), ref(parts), num_of_iteration);
    for (int i = 0; i < product_workers.size(); i++)
        product_worker_threads.emplace_back(ProductWorkerScheduler, ref(product_workers[i]), ref(buffer), ref(parts), num_of_iteration);
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

    // produce parts we need but not in local state
    int sleep_time = 0;
    for (int i = 0; i < load_order.size(); i++)
        sleep_time += (load_order[i] - local_state[i]) * parts[i].producting_time_comsumption;
    if (sleep_time != 0)
        this_thread::sleep_for(microseconds(sleep_time));
    sleep_time = 0;

    // now we have all the parts we need ready in local state
    int num_of_part_to_drop = 0;
    local_state = load_order;
    for (int part_num : local_state)
        num_of_part_to_drop += part_num;

    // try to put into buffer - need a lock here for buffer
    int wait_time = 0;
    while (true)
    {
        // lock to preventing buffer be used by partworker and productworker at the same time
        if (buffer_lock.try_lock())
        {
            // put parts into buffer
            for (int i = 0; i < local_state.size(); i++)
            {
                int num_of_dropped_parts = (buffer.buffer_capacity[i] - buffer.buffer_state[i]) > local_state[i] ? local_state[i] : (buffer.buffer_capacity[i] - buffer.buffer_state[i]);

                buffer.buffer_state[i] += num_of_dropped_parts;
                local_state[i] -= num_of_dropped_parts;

                sleep_time += num_of_dropped_parts * parts[i].moving_time_consumption;
            }

            // no access to buffer from the code below
            buffer_lock.unlock();

            // time calcuation and sleep - no sleep no print
            wait_time += sleep_time;
            if (sleep_time != 0)
                this_thread::sleep_for(microseconds(sleep_time));
            sleep_time = 0;

            // check wether all the types have been dropped
            if (num_of_part_to_drop == 0 || wait_time > max_wait_time)
                break;

            // if can not do any more drop and there are still parts haven't be dropped, wait for notify from productworkers
            cv1.wait(UG1);
        }
    }

    // we need to put the parts left in local state back home
    sleep_time = 0;
    if (num_of_part_to_drop != 0)
    {
        for (int i = 0; i < local_state.size(); i++)
            sleep_time += local_state[i] * parts[i].moving_time_consumption;

        if (sleep_time != 0)
            this_thread::sleep_for(microseconds(sleep_time));
    }

    // notify productWorkers the buffer have been refilled
    cv2.notify_all();

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