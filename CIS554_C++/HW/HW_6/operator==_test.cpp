#include <string>
#include <vector>
#include <unordered_set>
#include <iostream>

using namespace std;

class foo
{
public:
    vector<int> data;
    int sum;

    foo()
    {
        data = vector<int>();
        sum = 0;
    }

    foo(const initializer_list<int> &L1) : foo()
    {
        for (int i : L1)
        {
            data.push_back(i);
            sum += i;
        }
        return;
    }

    bool operator==(const foo &f2) const
    {
        return sum == f2.sum;
    }
};

class myHash
{
public:
    size_t operator()(const foo &f) const
    {
        hash<int> h;

        return h(f.sum);
    }

    // bool operator()(const foo &f1, const foo &f2) const
    // {
    //     return f1.sum == f2.sum;
    // }

};

int main()
{

    foo f1{1, 2, 3, 4, 5, 6};
    foo f2{6, 5, 4, 3, 2, 1};
    unordered_set<foo, myHash> s;

    s.insert(f1);
    s.insert(f2);

    cout << s.size() << endl;

    string str(5, '0');
    str[0] = '1';

    cout << str << endl;

    for(int i : f1.data) cout << i << "\n";

    cout << &(f1.data) << " sum f1 : " << &(f1.sum) << endl;

    for(int i : f2.data) cout << i << "\n";

    cout << "sum f2 : " << &(f2.sum) << endl;

    swap(f1,f2);

    cout << "after swap =========================" << endl;

    for(int i : f1.data) cout << i << "\n";

    cout << &(f1.data) << " sum f1 : " << &(f1.sum) << endl;

    for(int i : f2.data) cout << i << "\n";

    cout << "sum f2 : " << &(f2.sum) << endl;

    return 0;
}