#include <functional>
#include <unordered_set>
#include <set>
#include <unordered_map>
#include <vector>
#include <iostream>
#include <queue>

using namespace std;

class foo
{
public:
    shared_ptr<vector<int>> val;
    shared_ptr<int> times;

    foo()
    {
        val = make_shared<vector<int>>();
        times = nullptr;
    }

    foo(const initializer_list<int> &L, int time) : foo()
    {
        for (int i : L)
        {
            val->push_back(i);
        }

        times = make_shared<int>(time);

        return;
    }
};

class myCompare2{
public:
    bool operator()(int a, int b){
        return a > b;
    }

};


class myCompare
{
public:
    size_t operator()(const foo &f) const
    {
        hash<int> h;

        int sum = 0;

        for (int i : *(f.val))
            sum += i;

        sum *= *(f.times);

        return h(sum);
    }

    bool operator()(const foo &f1, const foo &f2) const
    {
        int sum1 = 0, sum2 = 0;

        for (int i : *(f1.val))
            sum1 += i;
        sum1 *= *(f1.times);

        for (int i : *(f2.val))
            sum2 += i;
        sum2 *= *(f2.times);

        return sum1 == sum2;
    }
};

bool compare(const foo &f1, const foo &f2)
{
    int sum1 = 0, sum2 = 0;

    for (int i : *(f1.val))
        sum1 += i;
    sum1 *= *(f1.times);

    for (int i : *(f2.val))
        sum2 += i;
    sum2 *= *(f2.times);

    return sum1 == sum2;
}

bool my_greater(int a, int b){
    return a > b;
}

int max(int a, int b, bool (*F)(int a, int b)){
    return F(a,b) ? a : b;
}

int main()
{
    auto g = [](int a, int b){return a > b;};
    cout << "set, hash and equal_to ============================== " <<endl;

    foo f1({1, 2, 3}, 2);
    foo f2({1, 2, 3}, 1);
    foo f3{{2, 4, 6}, 1};

    // set
    unordered_set<foo, myCompare, myCompare> s;
    s.insert(f1);
    s.insert(f2);
    s.insert(f2);
    
    unordered_map<foo, int,  myCompare, myCompare> m;
    m[f1]++;
    m[f2]++;
    m[f3]++;

    cout << s.size() << endl;


    set<int, decltype(g)> s2(g);

    s2.insert(1);
    s2.insert(2);
    s2.insert(3);

    for(int i : s2){
        cout << i << ", ";
    }

    cout << endl;

    cout << "priorityQueue and  lameda ============================== " <<endl;

    [](foo &f){cout << f.val->at(0) << endl; return; }(f1);

    // auto f = [](int a, int b){return a < b;};
    // priorityQueue
    // priority_queue<int, vector<int>, function<bool(int a, int b)>> pq([](int a, int b){return a < b;});
    priority_queue<int, vector<int>, myCompare2> pq;

    pq.emplace(1);
    pq.emplace(2);
    pq.emplace(7);
    pq.emplace(5);

    while(!pq.empty()){
        cout << pq.top() << ", ";
        pq.pop();
    }

    cout << endl;

    priority_queue<foo, vector<foo>, function<bool(foo &a, foo &b)>> pq2([&m](foo &a, foo &b){return m[a] < m[b];});

    pq2.emplace(f1);
    pq2.emplace(f2);

    while(!pq2.empty()){
        cout << m[pq2.top()] << ", ";
        pq2.pop();
    }

    cout << endl;

    cout << "functionPointer ============================== " <<endl;

    int a = 5, b = 3;

    bool (*fP) (int a, int b);

    fP = my_greater;

    cout << "the greater between " << a << " and " << b << " is " << max(a,b,my_greater) << endl;

    return 0;
}