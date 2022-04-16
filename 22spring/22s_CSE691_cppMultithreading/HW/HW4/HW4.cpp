#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <vector>
#include <chrono>
#include <atomic>
#include <string>
#include <fstream>

using namespace std;
using namespace chrono;

mutex print_lock, buffer_lock;
condition_variable cv1, cv2;
ofstream fout;
int total_complete;

const int MaxTimePart{18000}, MaxTimeProduct{20000};

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
    int part_types;
    microseconds max_wait_time;

public:
    vector<int> load_order;
    vector<int> local_state;

    int getId()
    {
        return id;
    }

    // randomly fill the load till the size of load order
    void reloadLoadOrder();

    void partWorkerWorkflow(Buffer &buffer, const vector<Part> &parts, int iteration, system_clock::time_point &ori_start_time);

    PartWorker()
    {
        part_types = 5;
        size_of_load_order = 5;
        load_order = vector<int>(part_types, 0);
        local_state = vector<int>(part_types, 0);
        reloadLoadOrder();

        return;
    }

    PartWorker(int id, microseconds max_wait_time) : PartWorker()
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
    int part_types;
    microseconds max_wait_time;

public:
    vector<int> assembly_order;
    vector<int> cart_state;

    int getId()
    {
        return id;
    }

    // randomly fill the load till the size of load order
    void reloadAssemblyOrder();

    void productWorkerWorkflow(Buffer &buffer, const vector<Part> &parts, int iteration, system_clock::time_point &ori_start_time);

    ProductWorker()
    {
        part_types = 5;
        size_of_assembly_order = 5;
        assembly_order = vector<int>(part_types, 0);
        cart_state = vector<int>(part_types, 0);
        reloadAssemblyOrder();

        return;
    }

    ProductWorker(int id, microseconds max_wait_time) : ProductWorker()
    {
        this->id = id;
        this->max_wait_time = max_wait_time;
    }
};

void PrintPartWorker(PartWorker &worker, int iteration, system_clock::time_point &ori_start_time, vector<int> &prev_buffer_state, vector<int> &prev_local_state, Buffer &buffer, int status_index, system_clock::duration &dur)
{
    // return;
    print_lock.lock();
    vector<string> status{"New Load Order", "Wakeup-Notified", " Wakeup-Timeout"};

    fout << "Current Time: " << (system_clock::now().time_since_epoch().count() - ori_start_time.time_since_epoch().count()) << "us" << endl;
    fout << "Iteration " << iteration << endl;
    fout << "Part Worker ID: " << worker.getId() << endl;
    fout << "Status: " << status[status_index] << endl;
    fout << "Accumulated Wait Time: " << duration_cast<microseconds>(dur).count() << "us" << endl;
    fout << string("Buffer State: (" + to_string(prev_buffer_state[0]) + "," + to_string(prev_buffer_state[1]) + "," + to_string(prev_buffer_state[2]) + "," + to_string(prev_buffer_state[3]) + "," + to_string(prev_buffer_state[4]) + ")") << endl;
    fout << string("Load Order: (" + to_string(prev_local_state[0]) + "," + to_string(prev_local_state[1]) + "," + to_string(prev_local_state[2]) + "," + to_string(prev_local_state[3]) + "," + to_string(prev_local_state[4]) + ")") << endl;
    fout << string("Updated Buffer State: (" + to_string(buffer.buffer_state[0]) + "," + to_string(buffer.buffer_state[1]) + "," + to_string(buffer.buffer_state[2]) + "," + to_string(buffer.buffer_state[3]) + "," + to_string(buffer.buffer_state[4]) + ")") << endl;
    fout << string("Updated Load Order: (" + to_string(worker.local_state[0]) + "," + to_string(worker.local_state[1]) + "," + to_string(worker.local_state[2]) + "," + to_string(worker.local_state[3]) + "," + to_string(worker.local_state[4]) + ")") << endl;
    fout << endl;

    print_lock.unlock();

    return;
}

void PrintProductWorker(ProductWorker &worker, int iteration, system_clock::time_point &ori_start_time, Buffer &buffer, int status_index, system_clock::duration &dur, vector<int> &prev_buffer_state, vector<int> &pre_pickup_order, vector<int> &prev_local_state, vector<int> &prev_cart_state, vector<int> &pickup_order, vector<int> &local_state, vector<int> &real_cart_state)
{
    // if (worker.getId() != 1)
    //     return;
    print_lock.lock();
    vector<string> status{"New Pickup Order", "Wakeup-Notified", " Wakeup-Timeout"};

    fout << "Current Time :" << (system_clock::now().time_since_epoch().count() - ori_start_time.time_since_epoch().count()) << "us" << endl;
    fout << "Iteration " << iteration << endl;
    fout << "Product Worker ID :" << worker.getId() << endl;
    fout << "Status :" << status[status_index] << endl;
    fout << "Accumulated Wait Time :" << duration_cast<microseconds>(dur).count() << "us" << endl;
    fout << string("Buffer State: (" + to_string(prev_buffer_state[0]) + "," + to_string(prev_buffer_state[1]) + "," + to_string(prev_buffer_state[2]) + "," + to_string(prev_buffer_state[3]) + "," + to_string(prev_buffer_state[4]) + ")") << endl;
    fout << string("Pickup Order: (" + to_string(pre_pickup_order[0]) + "," + to_string(pre_pickup_order[1]) + "," + to_string(pre_pickup_order[2]) + "," + to_string(pre_pickup_order[3]) + "," + to_string(pre_pickup_order[4]) + ")") << endl;
    fout << string("Local State: (" + to_string(prev_local_state[0]) + "," + to_string(prev_local_state[1]) + "," + to_string(prev_local_state[2]) + "," + to_string(prev_local_state[3]) + "," + to_string(prev_local_state[4]) + ")") << endl;
    fout << string("Cart State: (" + to_string(prev_cart_state[0]) + "," + to_string(prev_cart_state[1]) + "," + to_string(prev_cart_state[2]) + "," + to_string(prev_cart_state[3]) + "," + to_string(prev_cart_state[4]) + ")") << endl;
    fout << string("Updated Buffer State: (" + to_string(buffer.buffer_state[0]) + "," + to_string(buffer.buffer_state[1]) + "," + to_string(buffer.buffer_state[2]) + "," + to_string(buffer.buffer_state[3]) + "," + to_string(buffer.buffer_state[4]) + ")") << endl;
    fout << string("Updated Pickup Order: (" + to_string(pickup_order[0]) + "," + to_string(pickup_order[1]) + "," + to_string(pickup_order[2]) + "," + to_string(pickup_order[3]) + "," + to_string(pickup_order[4]) + ")") << endl;
    fout << string("Local State: (" + to_string(local_state[0]) + "," + to_string(local_state[1]) + "," + to_string(local_state[2]) + "," + to_string(local_state[3]) + "," + to_string(local_state[4]) + ")") << endl;
    fout << string("Cart State: (" + to_string(real_cart_state[0]) + "," + to_string(real_cart_state[1]) + "," + to_string(real_cart_state[2]) + "," + to_string(real_cart_state[3]) + "," + to_string(real_cart_state[4]) + ")") << endl;
    fout << "Total Completed Products: " << total_complete << endl;
    fout << endl;

    print_lock.unlock();

    return;
}

void PartWorkerScheduler(PartWorker &worker, Buffer &buffer, vector<Part> &parts, int num_of_iteration, system_clock::time_point &ori_start_time)
{
    // each worker to finish 5 iterations
    for (int i = 0; i < num_of_iteration; i++)
    {
        worker.partWorkerWorkflow(buffer, parts, i + 1, ori_start_time);
    }

    return;
}

void ProductWorkerScheduler(ProductWorker &worker, Buffer &buffer, vector<Part> &parts, int num_of_iteration, system_clock::time_point &ori_start_time)
{
    // each worker to finish 5 iterations
    for (int i = 0; i < num_of_iteration; i++)
    {
        worker.productWorkerWorkflow(buffer, parts, i + 1, ori_start_time);
    }

    return;
}

int main()
{
    srand(time(NULL));
    system_clock::time_point start_time = system_clock::now();
    const int m = 20, n = 16;
    fout = ofstream("log.txt");
    total_complete = 0;

    // parts and buffer initialization
    vector<Part> parts{Part(500, 200, 600), Part(500, 200, 600), Part(600, 300, 700), Part(600, 300, 700), Part(700, 400, 800)};
    Buffer buffer;

    // have the works
    vector<PartWorker> part_workers;
    vector<ProductWorker> product_workers;
    for (int i = 0; i <= m; i++)
        part_workers.push_back(PartWorker(i + 1, (microseconds)MaxTimePart));
    for (int i = 0; i <= n; i++)
        product_workers.push_back(ProductWorker(i + 1, (microseconds)MaxTimeProduct));

    // push workers into their workflow
    int num_of_iteration = 5;
    vector<thread> part_worker_threads;
    vector<thread> product_worker_threads;
    for (int i = 0; i < part_workers.size(); i++)
        part_worker_threads.emplace_back(PartWorkerScheduler, ref(part_workers[i]), ref(buffer), ref(parts), num_of_iteration, ref(start_time));
    for (int i = 0; i < product_workers.size(); i++)
        product_worker_threads.emplace_back(ProductWorkerScheduler, ref(product_workers[i]), ref(buffer), ref(parts), num_of_iteration, ref(start_time));
    for (thread &i : part_worker_threads)
        i.join();
    for (thread &i : product_worker_threads)
        i.join();

    fout << "Finish!" << endl;
    fout.close();

    return 0;
}

void PartWorker::partWorkerWorkflow(Buffer &buffer, const vector<Part> &parts, int iteration, system_clock::time_point &ori_start_time)
{
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
    system_clock::time_point start_time = system_clock::now();
    system_clock::duration dur((microseconds)0);
    vector<int> prev_buffer_state, prev_local_state;
    int status_index = 0;
    while (true)
    {
        // lock to preventing buffer be used by partworker and productworker at the same time
        unique_lock<mutex> UG1(buffer_lock);

        // put parts into buffer
        prev_buffer_state = buffer.buffer_state;
        prev_local_state = local_state;
        int prev_num_of_part_to_drop = num_of_part_to_drop;
        for (int i = 0; i < local_state.size(); i++)
        {
            int num_of_dropped_parts = (buffer.buffer_capacity[i] - buffer.buffer_state[i]) > local_state[i] ? local_state[i] : (buffer.buffer_capacity[i] - buffer.buffer_state[i]);

            buffer.buffer_state[i] += num_of_dropped_parts;
            local_state[i] -= num_of_dropped_parts;
            num_of_part_to_drop -= num_of_dropped_parts;
        }

        // // we need to put the parts left in local state back home
        // if (system_clock::now() - start_time > max_wait_time)
        // {
        // }

        // if can drop any, do print
        if (prev_num_of_part_to_drop != num_of_part_to_drop || status_index == 0)
        {
            PrintPartWorker(*this, iteration, ori_start_time, prev_buffer_state, prev_local_state, buffer, status_index, dur);
        }
        status_index = 1;

        // check wether all the types have been dropped or timeout
        if (num_of_part_to_drop == 0)
        {
            break;
        }

        // if can not do any more drop and there are still parts haven't be dropped, wait for notify from productworkers
        prev_buffer_state = buffer.buffer_state;
        prev_local_state = local_state;
        system_clock::time_point start_wait = system_clock::now();
        if (cv1.wait_until(UG1, start_time + max_wait_time) == cv_status::timeout)
        {
            dur += (system_clock::now() - start_wait);

            sleep_time = 0;
            if (num_of_part_to_drop != 0)
            {
                for (int i = 0; i < local_state.size(); i++)
                    sleep_time += local_state[i] * parts[i].moving_time_consumption;

                if (sleep_time != 0)
                    this_thread::sleep_for(microseconds(sleep_time));
            }

            PrintPartWorker(*this, iteration, ori_start_time, prev_buffer_state, prev_local_state, buffer, 2, dur);
            break;
        }
        dur += (system_clock::now() - start_wait);
        // cout << duration_cast<microseconds>(dur).count() << " " << start_time.time_since_epoch().count() << " " << system_clock::now().time_since_epoch().count() << endl;
    }

    // notify productWorkers the buffer have been refilled
    cv2.notify_all();

    return;
}

void ProductWorker::productWorkerWorkflow(Buffer &buffer, const vector<Part> &parts, int iteration, system_clock::time_point &ori_start_time)
{
    int sleep_time = 0;

    // calculate the parts we need to pickup
    int num_of_part_to_pickup = 0;
    vector<int> local_state = cart_state, pickup_order = vector<int>(part_types, 0), real_cart_state = vector<int>(part_types, 0);
    // vector<int> parts_to_pick_up(cart_state.size(), 0);
    for (int i = 0; i < cart_state.size(); i++)
    {
        pickup_order[i] = assembly_order[i] - cart_state[i];
        num_of_part_to_pickup += assembly_order[i] - cart_state[i];
    }

    // try to put into buffer - need a lock here for buffer
    system_clock::time_point start_time = system_clock::now();
    system_clock::duration dur(0);
    vector<int> prev_buffer_state, prev_cart_state, prev_pickup_order, prev_local_state;
    int status_index = 0;
    while (true)
    {
        // lock to preventing buffer be used by partworker and productworker at the same time
        unique_lock<mutex> UG2(buffer_lock);

        // put parts into cart
        prev_buffer_state = buffer.buffer_state;
        prev_cart_state = real_cart_state;
        prev_pickup_order = pickup_order;
        prev_local_state = local_state;
        int prev_num_of_part_to_pickup = num_of_part_to_pickup;
        for (int i = 0; i < cart_state.size(); i++)
        {
            int num_of_pickup_parts = buffer.buffer_state[i] > assembly_order[i] - cart_state[i] ? assembly_order[i] - cart_state[i] : buffer.buffer_state[i];

            buffer.buffer_state[i] -= num_of_pickup_parts;
            cart_state[i] += num_of_pickup_parts;
            real_cart_state[i] += num_of_pickup_parts;
            num_of_part_to_pickup -= num_of_pickup_parts;
            pickup_order[i] -= num_of_pickup_parts;
        }

        // if the cart_state meet the assembly, we assembly the parts and reset cart_state
        if (num_of_part_to_pickup == 0)
        {
            total_complete++;
            sleep_time = 0;
            for (int i = 0; i < cart_state.size(); i++)
                sleep_time += cart_state[i] * parts[i].assembly_time_comsumption;

            if (sleep_time != 0)
                this_thread::sleep_for(microseconds(sleep_time));

            cart_state = vector<int>(part_types, 0);
            real_cart_state = vector<int>(part_types, 0);
            local_state = vector<int>(part_types, 0);
        }
        // otherwise, we bring the parts we freshly pickuped back to cart
        // else if (system_clock::now() - start_time > max_wait_time)
        // {
        //     sleep_time = 0;
        //     for (int i = 0; i < cart_state.size(); i++)
        //     {
        //         sleep_time += (cart_state[i] - local_state[i]) * parts[i].moving_time_consumption;
        //     }

        //     if (sleep_time != 0)
        //         this_thread::sleep_for(microseconds(sleep_time));
        // }

        if (prev_num_of_part_to_pickup != num_of_part_to_pickup || status_index == 0)
            PrintProductWorker(*this, iteration, ori_start_time, buffer, status_index, dur, prev_buffer_state, prev_pickup_order, prev_local_state, prev_cart_state, pickup_order, local_state, real_cart_state);
        status_index = 1;

        // check wether all the types have been dropped
        if (num_of_part_to_pickup == 0)
        {
            break;
        }

        // if can not do any more drop and there are still parts haven't be dropped, wait for notify from productworkers
        prev_buffer_state = buffer.buffer_state;
        prev_cart_state = real_cart_state;
        prev_pickup_order = pickup_order;
        prev_local_state = local_state;
        system_clock::time_point start_wait = system_clock::now();
        if (cv2.wait_until(UG2, start_time + max_wait_time) == cv_status::timeout)
        {
            dur += (system_clock::now() - start_wait);
            sleep_time = 0;
            for (int i = 0; i < cart_state.size(); i++)
            {
                sleep_time += (cart_state[i] - local_state[i]) * parts[i].moving_time_consumption;
            }

            if (sleep_time != 0)
                this_thread::sleep_for(microseconds(sleep_time));
            PrintProductWorker(*this, iteration, ori_start_time, buffer, 2, dur, prev_buffer_state, prev_pickup_order, prev_local_state, prev_cart_state, pickup_order, local_state, real_cart_state);
            break;
        }
        dur += (system_clock::now() - start_wait);
    }

    cv1.notify_all();

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
    int type_already_loaded = 0;
    vector<bool> types(part_types, false);
    for (int i = 0; i < assembly_order.size(); i++)
    {
        if (assembly_order[i] != 0)
        {
            types[i] = true;
            type_already_loaded++;
        }
    }

    type_to_reload = type_already_loaded < 3 ? type_to_reload = (rand() % 2) + 2 : 3;

    // decide what the types are
    while (type_already_loaded < type_to_reload)
    {
        int type = rand() % part_types;

        if (!types[type])
        {
            types[type] = true;
            type_already_loaded++;
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
    for (int type = 0; type < part_types; type++)
    {
        while (types[type] && assembly_order[type] == 0)
        {
            int type_to_reduce_individual = rand() % part_types;

            if (assembly_order[type_to_reduce_individual] > 1)
            {
                assembly_order[type_to_reduce_individual]--;
                assembly_order[type]++;
            }
        }
    }

    return;
}