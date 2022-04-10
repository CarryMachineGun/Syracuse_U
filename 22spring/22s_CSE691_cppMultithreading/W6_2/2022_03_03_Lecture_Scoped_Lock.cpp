//Taken from C++ standard's examples (Not written by Professor Chen)
//Need to set project property to use C++ 2017 or later to run scoped_lock
#include <mutex>
#include <thread>
#include <iostream>
#include <vector>
#include <chrono>
#include <string>

using namespace std;
using namespace chrono;
using namespace literals::chrono_literals;

struct Employee {
    Employee(string id) : id(id) {}
    string id;
    vector<string> lunch_partners;
    mutex m;
    string output() const
    {
        string ret = "Employee " + id + " has lunch partners: ";
        for (const auto& partner : lunch_partners)
            ret += partner + " ";
        return ret;
    }
};

void send_mail(Employee&, Employee&)
{
    //doing something
    this_thread::sleep_for(chrono::seconds(1));
}

void assign_lunch_partner(Employee& e1, Employee& e2)
{
    static mutex io_mutex;//shared by all calls to this function
    {
        lock_guard<mutex> lk(io_mutex);
        cout << e1.id << " and " << e2.id << " are waiting for locks" << std::endl;
    }

    {

        scoped_lock lock(e1.m, e2.m);//scoped_lock behave like a lock_guard; RAII

        {
            lock_guard lk(io_mutex);
            cout << e1.id << " and " << e2.id << " got locks" << std::endl;
        }
        e1.lunch_partners.push_back(e2.id);
        e2.lunch_partners.push_back(e1.id);
    }

    send_mail(e1, e2);
    send_mail(e2, e1);
}

int main()
{
    Employee alice("alice"), bob("bob"), christina("christina"), dave("dave");

    std::vector<thread> threads;
    threads.emplace_back(assign_lunch_partner, ref(alice), ref(bob));
    threads.emplace_back(assign_lunch_partner, ref(christina), ref(bob));
    threads.emplace_back(assign_lunch_partner, ref(christina), ref(alice));
    threads.emplace_back(assign_lunch_partner, ref(dave), ref(bob));

    for (auto& thread : threads) thread.join();
    cout << alice.output() << '\n' << bob.output() << '\n'
        << christina.output() << '\n' << dave.output() << '\n';
}