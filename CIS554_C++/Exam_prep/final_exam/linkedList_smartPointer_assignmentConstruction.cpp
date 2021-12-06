#include <iostream>
#include <memory>
#include <vector>
using namespace std;

class Node
{
public:
    shared_ptr<vector<int>> value;
    shared_ptr<Node> next;
    weak_ptr<Node> previous;
    // Node *next;
    // Node *previous;
    Node()
    {
        next.reset();
        previous.reset();
        // next = nullptr;
        // previous = nullptr;
        value = make_shared<vector<int>>();
    } // default constructor

    Node(const Node &N):Node()
    {
        for (int i : *(N.value)){
            value->push_back(i);
        }

        return;
    }

    Node(const initializer_list<int> &L) : Node()
    {
        for (int i : L)
        {
            value->push_back(i);
        }
        return;
    }
};

class DoublyLinkedList
{
public:
    shared_ptr<Node> head;
    shared_ptr<Node> tail;
    DoublyLinkedList() { head = tail = nullptr; }
    DoublyLinkedList(const initializer_list<initializer_list<int>> &L);
    DoublyLinkedList(const DoublyLinkedList &L);
    DoublyLinkedList(DoublyLinkedList &&L);
    ~DoublyLinkedList()
    {
        tail.reset();
        head.reset();
    }
    DoublyLinkedList operator=(DoublyLinkedList &&L);
    DoublyLinkedList operator=(const DoublyLinkedList &L);
    DoublyLinkedList kTimes(int k);
    void print_F();
    void print_B();

    // void bubbleSort();
    // void minMax(); //swap the node of min value with the first node;
    //                //swap the node of max value with the last node

    void remove(int i);
    void reverse();
};

DoublyLinkedList::DoublyLinkedList(const DoublyLinkedList &L) : DoublyLinkedList()
{
    if (!L.head)
        return;

    head = make_shared<Node>(*(L.head));
    shared_ptr<Node> curr = head, L_curr = L.head;

    while (L_curr->next)
    {
        curr->next = make_shared<Node>(*(L_curr->next));

        curr->next->previous = curr;
        curr = curr->next;
        L_curr = L_curr->next;
    }

    tail = curr;

    cout << "Copy Constructor" << endl;
    return;
}
DoublyLinkedList::DoublyLinkedList(DoublyLinkedList &&L) : DoublyLinkedList()
{
    head = L.head;
    tail = L.tail;

    L.head.reset();
    L.tail.reset();

    cout << "Move Constructor" << endl;

    return;
}
DoublyLinkedList DoublyLinkedList::operator=(DoublyLinkedList &&L)
{
    head.reset();
    tail.reset();

    cout << "Move Assignment" << endl;

    if (!L.head)
        return *this;

    head = L.head;
    tail = L.tail;

    L.head.reset();
    L.tail.reset();

    return *this;
}
DoublyLinkedList DoublyLinkedList::operator=(const DoublyLinkedList &L)
{
    head.reset();
    tail.reset();

    cout << "Copy Assignment" << endl;

    if (!L.head)
        return *this;

    head = make_shared<Node>(*(L.head));
    shared_ptr<Node> curr = head, L_curr = L.head;

    while (L_curr->next)
    {
        curr->next = make_shared<Node>(*(L_curr->next));

        curr->next->previous = curr;

        curr = curr->next;
        L_curr = L_curr->next;
    }

    tail = curr;

    return *this;
}

DoublyLinkedList DoublyLinkedList::kTimes(int k)
{
    DoublyLinkedList temp(*this);

    shared_ptr<Node> curr = temp.head;

    while(curr){
        for(int &i : *(curr->value)){
            i = k * i;
        }

        curr = curr->next;
    }

    return temp;
}

ostream &operator<<(ostream &str, const Node &N)
{
    str << "{ ";

    for (int i : *(N.value))
    {
        str << i << " ";
    }

    str << "} ";

    return str;
}

void DoublyLinkedList::print_F()
{
    shared_ptr<Node> curr = head;

    cout << "( ";

    while (curr)
    {
        cout << *curr;
        curr = curr->next;
    }

    cout << ")" << endl;

    return;
}

void DoublyLinkedList::print_B()
{
    shared_ptr<Node> curr = tail;

    cout << "( ";

    while (curr)
    {
        cout << *curr;
        curr = (curr->previous).lock();
    }

    cout << ")" << endl;

    return;
}

//双链表remove
void DoublyLinkedList::remove(int i)
{
    if (i == 1)
    {
        head = head->next;
        return;
    }

    shared_ptr<Node> curr = head;

    while (i-- > 1)
    {
        curr = curr->next;
        if (!curr)
        {
            cout << "Input index is too long" << endl;
            return;
        }
    }

    if (curr == tail)
    {
        tail = tail->previous.lock();
        tail->next.reset();
        return;
    }

    curr->previous.lock()->next = curr->next;
    curr->next->previous = curr->previous;

    return;
}

// reverse

void DoublyLinkedList::reverse()
{
    if (!head || !head->next)
        return;

    shared_ptr<Node> curr = head, next = head->next, pre = head->previous.lock();

    head = tail;
    tail = curr;

    while (curr)
    {
        curr->next = pre;
        curr->previous = next;

        pre = curr;
        curr = next;
        if (next)
            next = next->next;
    }

    return;
}
//双链表reorder
DoublyLinkedList::DoublyLinkedList(const initializer_list<initializer_list<int>> &L)
{
    head = make_shared<Node>(*(L.begin()));
    shared_ptr<Node> curr = head;

    for (auto i = L.begin() + 1; i != L.end(); i++)
    {
        curr->next = make_shared<Node>(*i);
        curr->next->previous = curr;
        curr = curr->next;
    }

    tail = curr;

    return;
}

// remove all node contains value k

int main()
{
    DoublyLinkedList L1{{1, 2, 3}, {3, 4, 5}, {5, 6, 7}, {9, 10, 12}, {11, 23, 57}};
    L1.print_F();
    L1.print_B();

    L1.reverse();
    L1.remove(3);

    L1.print_F();
    L1.print_B();

    cout << "===============================" << endl;

    DoublyLinkedList L2{L1};

    L2.print_F();
    L2.print_B();

    DoublyLinkedList L3{{1, 2, 3, 4, 5}, {2, 3, 4, 5, 6, 6}, {1, 23, 5, 6, 1}, {3243526, 3, 56, 7, 2, 1}};
    L2 = L3;

    L2.print_F();
    L2.print_B();

    L2 = L1.kTimes(2);

    L2.print_F();
    L2.print_B();

    return 0;
}