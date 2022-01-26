#include <list>
#include <tuple>
#include <iostream>

using namespace std;

class myCompare
{
public:
    bool operator()(const int a, const int b) const
    {
        return a < b;
    }
};

int main()
{

    auto f = [](int a, int b)
    { return a < b; };
    auto isOdd = [](int a)
    { return (a % 2 == 1); };

    list<int> l1{1, 3, 4, 5, 56, 2, 1};
    list<int> l2{2, 3, 5, 1, 13, 3, 523, 4123};
    list<int> l3(5, 100);
    list<int> l4(5, 100);

    l1.sort(myCompare());
    l2.sort(f);

    for (auto i = l1.begin(); i != l1.end(); i++)
    {
        cout << *i << ", ";
    }

    cout << endl;

    for (int i : l2)
    {
        cout << i << ", ";
    }
    cout << endl;

    for (int i : l4)
    {
        cout << i << ", ";
    }
    cout << endl;

    auto p = l1.begin();

    p++;
    p++;
    p++;

    l4.assign(l1.begin(), p);

    for (int i : l4)
    {
        cout << i << ", ";
    }

    cout << endl;

    cout << "===============================" << endl;

    l1.merge(l2);
    l1.merge(l3);

    for (auto i = l1.begin(); i != l1.end(); i++)
    {
        cout << *i << ", ";
    }

    cout << endl;

    l1.remove_if(isOdd);

    for (auto i = l1.begin(); i != l1.end(); i++)
    {
        cout << *i << ", ";
    }

    cout << endl;

    for_each(l1.begin(), l1.end(), [](int &a)
             {a *= 2; return; });

    for (auto i = l1.begin(); i != l1.end(); i++)
    {
        cout << *i << ", ";
    }

    cout << endl;

    tuple<int, string, int> t{1, "WFT", 2};

    for (int i = 0; i <= 3; i++)
        cout << get<1>(t) << ", ";

    cout << endl;

    return 0;
}