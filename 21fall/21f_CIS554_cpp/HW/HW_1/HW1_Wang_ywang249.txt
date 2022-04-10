//HW1 by Yuchen Wang
//SU Net ID: ywang249  SUID: 905508464

//test case: minMax: tail and max are adjacemt; bubble: two digit linkedlist

//Due:  11:59pm, Tuesday, Sept. 14
#include <iostream>
using namespace std;

class Node
{
public:
    int value;
    Node *next;
    Node *previous;
    Node(int i)
    {
        value = i;
        next = previous = nullptr;
    }
    Node() { next = previous = nullptr; } //default constructor
};

class DoublyLinkedList
{
public:
    Node *head;
    Node *tail;
    DoublyLinkedList() { head = tail = nullptr; }
    void makeList(int n, int m); //create an n-node linked list with random values in 0 ... m-1
    void print_F();
    void print_B();

    void bubbleSort();
    //2 3 1 6 8 5 9 6 2 5 7 7 4 2 becomes
    //1 2 2 2 3 4 5 5 6 6 7 7 8 9

    //In case multiple nodes have the same min value, the
    //first of them will be swapped with the node pointed by head.
    //In case multiple nodes have the same max value, the
    //last of them will be swapped with the node pointed by tail.
    //For example,    6 5 3 7 3 7 5 4 will become 3 5 6 7 3 4 5 7

    //You only can modify next and previous of nodes, but not value of nodes.
    //You are required to directly work on the linked list.

    //You are not allowed to use any external structures such as arrays
    // to perform operations and copy the results back to the linked list.

    //You are not allowed to create additional functions.
    //You can use while loop, but not for loop.

    void minMax(); //swap the node of min value with the first node;
                   //swap the node of max value with the last node

    // 14 5 6 2 17 9 8
    // 2 5 6 14 8 9 17

    //In case multiple nodes have the same min value, the
    //first of them will be swapped with the node pointed by head.
    //In case multiple nodes have the same max value, the
    //last of them will be swapped with the node pointed by tail.
    //For example,    6 5 3 7 3 7 5 4 will become 3 5 6 7 3 4 5 7

    //Similar constraints apply as repeatedly stated below.
    //You only can modify next and previous of nodes, but not value of nodes.
    //You are required to directly work on the linked list.

    //You are not allowed to use any external structures such as arrays
    // to perform operations and copy the results back to the linked list.

    //You are not allowed to create additional functions.
    //You can use while loop, but not for loop.
};

void DoublyLinkedList::minMax()
{
    //Your code

    //popUpMin
    Node *dummy = head->next, *min = head;

    while (dummy)
    {
        if (min->value > dummy->value)
        {
            min = dummy;
        }
        dummy = dummy->next;
    }

    if (min != head)
    {
        //swap min with head
        if (head->next == min)
        {
            min->next->previous = head;

            head->next = min->next;
            head->previous = min;

            min->next = head;
            min->previous = nullptr;
        }
        else
        {
            min->previous->next = head;
            min->next->previous = head;

            head->next->previous = min;

            dummy = head->next;
            head->next = min->next;
            head->previous = min->previous;

            min->next = dummy;
            min->previous = nullptr;
        }

        head = min;
    }

    //pushDownMax
    //find the index of last max node 'max'
    dummy = tail->previous;
    Node *max = tail;

    while (dummy)
    {
        if (max->value < dummy->value)
        {
            max = dummy;
        }
        dummy = dummy->previous;
    }

    if (max != tail)
    {
        if (tail->previous == max)
        {
            max->previous->next = tail;

            tail->previous = max->previous;
            tail->next = max;

            max->next = nullptr;
            max->previous = tail;
        }
        else
        {
            max->previous->next = tail;
            max->next->previous = tail;

            tail->previous->next = max;

            dummy = tail->previous;
            tail->previous = max->previous;
            tail->next = max->next;

            max->next = nullptr;
            max->previous = dummy;
        }

        tail = max;
    }
}

void DoublyLinkedList::bubbleSort()
{
    //Your code
    Node *n1 = head, *n2 = head->next;
    if (!n1 || !n2)
    {
        return;
    }

    bool swapFlag = true;

    while (swapFlag)
    {
        swapFlag = false;
        n1 = head, n2 = head->next;

        while (n2)
        {
            if (n1->value > n2->value)
            {
                //handle attribue of n1.pre and n2.next
                if (n1->previous != nullptr)
                {
                    n1->previous->next = n2;
                }
                if (n2->next != nullptr)
                {
                    n2->next->previous = n1;
                }

                //Handle attribute of n1 and n1
                n2->previous = n1->previous;
                n1->next = n2->next;

                n2->next = n1;
                n1->previous = n2;

                // if head or tail is swapped
                if (n1 == head)
                {
                    head = n2;
                }
                if (n2 == tail)
                {
                    tail = n1;
                }

                swapFlag = true;
            }

            // move one node right
            if (n2->next == n1)
            {
                n2 = n1->next;
            }
            else
            {
                n1 = n2;
                n2 = n2->next;
            }
        }
    }

    return;
}

void DoublyLinkedList::makeList(int n, int m)
{
    for (int i = 0; i < n; ++i)
    {
        // srand ( time(NULL) );
        Node *p1{new Node{rand() % m}};
        if (!head)
        {
            head = tail = p1;
        } //currently empty linked list
        else
        {
            tail->next = p1;
            p1->previous = tail;
            tail = p1;
        }
    }
}
void DoublyLinkedList::print_F()
{
    Node *p1{head};
    while (p1)
    {
        cout << p1->value << " ";
        p1 = p1->next;
    }
    cout << endl;
}
void DoublyLinkedList::print_B()
{
    Node *p1{tail};
    while (p1)
    {
        cout << p1->value << " ";
        p1 = p1->previous;
    }
    cout << endl;
}

int main()
{
    DoublyLinkedList L1;
    L1.makeList(19, 15);
    L1.print_F();
    L1.print_B();
    L1.minMax();
    L1.print_F();
    L1.print_B();

    DoublyLinkedList L2;
    L2.makeList(25, 30);
    L2.bubbleSort();
    L2.print_F();
    L2.print_B();
    return 0;
}