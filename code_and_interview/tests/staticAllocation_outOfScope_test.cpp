#include <vector>
#include <iostream>

using namespace std;

class foo
{
public:
    int val;
    foo *next;

    foo(int val)
    {
        this->val = val;
        next = nullptr;
    }
};

class fooList
{

public:
    foo *root;

    fooList()
    {
        root = nullptr;
    }

    void print()
    {
        foo *curr = root;

        while(curr)
        {
            cout << curr->val << ", ";
            curr = curr->next;
        }

        cout << endl;

        return;
    }
};

void add(vector<foo> &arr)
{
    foo foo1(1);
    foo foo2(2);
    foo foo3(3);

    arr.push_back(foo1);
    arr.push_back(foo2);
    arr.push_back(foo3);

    return;
}

void print(vector<foo> &arr)
{

    for (foo i : arr)
    {
        cout << i.val << ", ";
    }

    cout << endl;

    return;
}

void makeFooNext(foo &curr)
{
    foo temp(2);
    curr.next = &temp;

    cout << &curr << " 's next is null: " << (curr.next == nullptr) << " , and the value is " << curr.next->val << endl;

    return;
}

int main()
{
    //test1 - arr element still exist because vector push_back copy of foo objects`
    vector<foo> arr;

    add(arr);
    print(arr);

    //test2
    foo foo1(0);
    makeFooNext(foo1);
    cout << &foo1 << " 's next is null: " << (foo1.next == nullptr) << " , and the value is " << foo1.next->val << endl;

    //test3
    fooList list;

    foo root(0);
    list.root = &root;
    foo *curr = list.root;

    for (int i = 1; i < 10; i++)
    {
        // foo new_foo(i);
        // curr->next = &new_foo;

        curr->next = new foo(i);

        curr = curr->next;
    }

    list.print();

    return 0;
}