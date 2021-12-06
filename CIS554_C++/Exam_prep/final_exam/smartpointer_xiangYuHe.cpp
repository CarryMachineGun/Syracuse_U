#include<iostream>
#include<memory>
#include<vector>
using namespace std;



class node{
public:

    shared_ptr<vector<int>> val;
    shared_ptr<node> next;
    weak_ptr<node> prev;

    node(){
       val = make_shared<vector<int>>();
    }
};


ostream& operator<<(ostream& str, const vector<int>& V){
    str << "( ";
    for(auto& it : V){
        str << it << " ";
    }
    str << ")";
    return str;
}


class DLL{
public:
    shared_ptr<node> head;
    shared_ptr<node> tail;
    DLL(){};
    DLL(const initializer_list<initializer_list<int>>& I);
    ~DLL();
    void printF();
    void printB();
    DLL(const DLL& D);
    DLL operator=(const DLL& D);
    DLL(DLL&& D);
    DLL operator=(DLL&& D);
    DLL times(int k);
    
};

// =================== initializer list =======================
DLL::DLL(const initializer_list<initializer_list<int>>& I){
        for(auto it = I.end() - 1; it != I.begin() - 1; --it){
            shared_ptr<node> p {new node()};
            for(auto itv : *it){
                p->val->emplace_back(itv);
            }
            if(!head && !tail){head = tail = p;}
            else{
                p->next = head;
                head->prev = p;
                head = p;
            }
        }
        cout << "initializer list" << endl;
}


// =================== copy constructor =======================
DLL::DLL(const DLL& D){
    shared_ptr<node> pt{D.tail};
    while(pt != nullptr){
        shared_ptr<node> p {new node()};
        for(auto it : *(pt->val)){
            p->val->emplace_back(it);
        }
        if(!head && !tail){
            head = tail = p;      
        }
        else{
            p->next = head;
            head->prev = p;
            head = p;
        }
        pt = pt->prev.lock();
    }
    cout << "copy constructor" << endl;
}


// =================== copy assignment =======================
DLL DLL::operator=(const DLL& D){
    // ------- if current exist, delete this ------
    if(head){
        head.reset();
        tail.reset();
    } 
    // -------------------------------------------
    DLL temp {D}; // copy constructor
    this->head = temp.head;
    this->tail = temp.tail;
    temp.head.reset();
    temp.tail.reset();

    cout << "copy assignment" << endl;
    return *this; // copy assignment "return *this;"
}

// =================== move constructor =======================
DLL::DLL(DLL&& D){
    head = D.head;
    tail = D.tail;
    D.head.reset();
    D.tail.reset();
    
    cout << "move constructor" << endl;
}


// =================== move assignment =======================
DLL DLL::operator=(DLL&& D){
    // ------- if current exist, delete this ------
    if(head){
        head.reset();
        tail.reset();
    }

    head = D.head;
    tail = D.tail;
    D.head.reset();
    D.tail.reset();

    cout << "move assignment" << endl;
    return *this;
}

// =================== Times() =======================
DLL DLL::times(int k){
    DLL temp {*this}; // don't change original one, make new one and operate
    shared_ptr<node> p { temp.head };
    while(p){
        for(auto& it : *(p->val)){
            it *= k;
        }
        p = p->next;
    }
    return move(temp);
}


// =================== destructor =======================
DLL::~DLL(){
    head.reset();
    tail.reset();
    cout << "destructor" << endl;
}

void DLL::printF(){
    cout << "[ ";
    shared_ptr<node> pv{ head };
    while(pv != nullptr){
        cout << *(pv->val) << " ";
        pv = pv->next;
    }
    cout << "]" << endl;
    return;
}

void DLL::printB(){
    cout << "[ ";
    shared_ptr<node> pv{ tail };
    while(pv != nullptr){
        cout << *(pv->val) << " ";
        pv = pv->prev.lock();
    }
    cout << "]" << endl;
    return;
}






int main(){

    DLL D { {1,2,3}, {4,5,6},{7,8,9}, {10,11,12}, {13,14,15} };
    D.printF();
    D.printB();

    DLL D2{ D };
    D2.printF();
    cout << "===================" << endl;
    DLL D3;
    D3 = D2;
    D3.printF();
    cout << "===================" << endl;
    DLL D4;
    D4 = D3.times(2);
    D4.printF();
    D3.printF();
    


    return 0;
}