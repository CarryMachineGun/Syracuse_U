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

    // void bubbleSort();
    // void minMax(); //swap the node of min value with the first node;
    //                //swap the node of max value with the last node

    void remove(int i);
    void reverse();
};

void DoublyLinkedList::makeList(int n, int m)
{
    for (int i = 0; i < n; ++i)
    {
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

//双链表remove
void DoublyLinkedList::remove(int i){
    if(i == 1){
        head = head->next;
        head->previous = nullptr;
    }

    Node* curr = head;

    while(i-- > 1){
        curr = curr->next;
        if(!curr){
            cout << "Input index is too long" << endl;
            return;
        }
    }

    if(curr == tail){
        tail = tail->previous;
        tail->next = nullptr;
        return;
    }

    curr->previous->next = curr->next;
    curr->next->previous = curr->previous;

    return;
}

//reverse

void DoublyLinkedList::reverse(){
    Node* curr = head;

    head = tail;
    tail = curr;
    
    // while(curr){
    //     Node* next = curr->next;
    //     curr->next = curr->previous;
    //     curr->previous = next;

    //     curr = next;
    // }

    while(curr){
        swap(curr->next, curr->previous);

        curr = curr->previous;
    }

    return;
}
//双链表reorder

    


int main()
{
    DoublyLinkedList L1;
    L1.makeList(19, 15);
    L1.print_F();
    L1.print_B();

    L1.reverse();
    // L1.remove(3);

    // cout << L1.head->value << endl;
    // cout << L1.head->next->value << endl;
    // cout << L1.head->next->next->value << endl;

    L1.print_F();
    L1.print_B();

    // DoublyLinkedList L2;
    // L2.makeList(0, 30);
    // L2.print_F();
    // L2.print_B();
    return 0;
}