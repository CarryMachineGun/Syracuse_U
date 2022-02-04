//Example showing difference between push_back and emplace_back
#include <vector>
#include <array>
#include <list>
#include <iostream>
#include <typeinfo>
using namespace std;

class ThreeD {
public:
    int ht;
    int wid;
    int dep;
    ThreeD() {}
    ThreeD(double i) { ht = wid = dep = i; }//implict type casting  double -> int
private:
    explicit ThreeD(int i) { ht = wid = dep = i; } //No implicit type casting 
};

int main() {
    int AA1[]   { 1,2,3,4,5 };
    array<int,5> A1{ 1,2,3,4,5 };
    cout << A1.at(0) << " " << A1[0] << " " << A1.at(3) << " " << A1[3] << endl;//1 1 4 4
    for (auto it = A1.begin(); it != A1.end(); ++it) {
        cout << *it << " ";
    }
    cout << endl;

    std::vector<int> myvector = { 10,20,30 };

    auto it = myvector.emplace(myvector.begin() + 1, 100);//10 100 20 30
    //Insert an in-place constructed element right before the positon/iterator
    //An iterator that points to the newly emplaced element.

    myvector.emplace(it, 200);//10 200 100 20 30
    myvector.emplace(myvector.end(), 300);//10 200 100 20 30 300

    std::cout << "myvector contains:";
    for (auto& x : myvector)
        std::cout << ' ' << x; //10 200 100 20 30 300

    std::cout << '\n';

    vector<int> V1{ 1,2,3,4,5 };
    V1.emplace_back(6);//1 2 3 4 5 6
    V1.push_back(7);//1 2 3 4 5 6 7
    //You can pretty much replace push_back with emplace_back.
    //Only in some very race cases will there be difference between the two.
    //emplace_back is faster than push_back

    for (auto i : V1) { cout << i << " "; }//1 2 3 4 5 6


//The following example showing the difference between emplace_back and push_back
    vector<ThreeD>().push_back(0); // OK  anonymous threeD object  int 0 -> double 0.0
    vector<ThreeD>().emplace_back(0.0); // OK
    //vector<ThreeD>().emplace_back(0); // error!

    cout << endl;

    //cbegin, cend

   // vector< const int> V10{ 1,2,3,4,5 }; not allowed
    //list< const int> L1 {11, 2, 3, 4, 5}; //not allowed

    const vector<int> V10{ 1,2,3,4,5 };//OK
    //V10[5] = 6;  error! const element
    const list<int> L1{ 2,3,4,5,6 };//OK

    auto it1{ V10.cbegin() }, it2{ V10.cend() };//it1 and it2 are pointing to const element
    cout << *it1 << " " << *(it2 - 1) << endl;//1 5
    //*it1 = 10; error

    //const int x {10}
    //similar to const int * p1 = &x;


    vector<int> V11{ 4,5,6, 7,8 };
    auto p = V11.data();//p points to first element of V11
    cout << typeid(p).name() << endl;//int *
    ++p;//p points to the second element
    *p = 300;
    cout << V11[1] << endl;//300

    V11.erase(V11.begin());
    for (auto& i : V11) { cout << i << " "; }
    cout << endl;

    V11.erase(V11.begin() + 2, V11.end());//[ ... )
    for (const auto& i : V11) { cout << i << " "; }//& makes it faster
    cout << endl;

    vector<int> V12, V13{ 1,2,3 };
    V12.assign(4, 100);//100 100 1000 100
    for (auto& i : V12) { cout << i << " "; }
    cout << endl;


    vector<int> V25{ 100,200,300,400,500,600,700,800,900,1000 }, V26, V27;
    V26.assign(V25.begin() + 3, V25.end() - 2);//400 500 600 700 800
    for (auto& i : V26) { cout << i << " "; }
    cout << endl;


    int A5[]{ 11,22,33,44,55,66,77 };
    V27.assign(A5, A5 + 3);//11 22 33
    for (auto& i : V27) { cout << i << " "; }
    cout << endl;


    V13.resize(5, 100);//1 2 3 100 100
    V13.resize(7);//1 2 3 100 100 0 0
    for (auto& i : V13) { cout << i << " "; }//1 2 3 100 100 0 0
    cout << endl;
    auto it3 = V13.insert(V13.end(), 2, 500);//1 2 3 100 100 0 0 500 500
    V13.insert(it3, 3, 999);//1 2 3 100 100 0 0 999 999 999 500 500
    for (auto& i : V13) { cout << i << " "; }//1 2 3 100 100 0 0 999 999 999 500 500
    cout << endl;
    cout << V13.size() << " " << V13.capacity() << " " << V13.max_size() << endl;//12 15 .......

    V13.reserve(30);//capacity = 30
    cout << V13.size() << " " << V13.capacity() << " " << V13.max_size() << endl;//12 30 .......

    for (auto& i : V13) { cout << i << " "; }
    cout << endl;


    V13.resize(25);//add 13 0's in the back
    for (auto& i : V13) { cout << i << " "; }
    cout << endl;
    cout << V13.size() << " " << V13.capacity() << " " << V13.max_size() << endl;
    V13.shrink_to_fit();//capacity = size
    cout << V13.size() << " " << V13.capacity() << " " << V13.max_size() << endl;//25 25 .....

    V13.swap(V12);
    //The same as V12.swap(V13);

    cout << endl;
    for (auto& i : V12) { cout << i << " "; }
    cout << endl;
    for (auto& i : V13) { cout << i << " "; }

    V13 = V12;
    cout << endl;
    for (auto& i : V13) { cout << i << " "; }
    cout << endl;

    for (auto rit = V13.rbegin(); rit != V13.rend(); rit++) { cout << *rit << " "; }
    cout << endl;

    auto crit1{ V13.crbegin() }, crit2{ V13.crend() };
    cout << *crit1 << " " << *(crit2 - 1) << endl;


    //  *crit1 = 10;  Erorr!
    //  *(crit2 - 1) = 20;  Error!


    vector<int> myvector1;
    int* p1;
    unsigned int i;

    //The following example is from cplusplus.com
    // allocate an array with space for 5 elements using vector's allocator:
    p1 = myvector1.get_allocator().allocate(5);

    // construct values in-place on the array:
    for (i = 0; i < 5; i++) myvector1.get_allocator().construct(&p1[i], i);

    cout << "The allocated array contains:";
    for (i = 0; i < 5; i++) std::cout << ' ' << p1[i];
    std::cout << '\n';

    // destroy and deallocate:
    for (i = 0; i < 5; i++) myvector1.get_allocator().destroy(&p1[i]);//0 1 2 3 4
    myvector1.get_allocator().deallocate(p1, 5);

    return 0;
}




/*

emplace_back() vs push_back()

push_back() copies a ThreeD into a vector. First, a new ThreeD object will
be implicitly created initialized with provided ThreeD.
Then push_back will be called which will copy this ThreeD object into the vector using
the copy constructor.
Then the temporary object will be destroyed.

emplace_back() constructs a ThreeD in-place, so no temporary ThreeD will be created
but rather emplace_back() will be called directly with ThreeD argument.
It will then create a ThreeD to be stored in the vector initialized with this ThreeD.
So, in this case, we avoid constructing and destroying an unnecessary temporary ThreeD object.


*/