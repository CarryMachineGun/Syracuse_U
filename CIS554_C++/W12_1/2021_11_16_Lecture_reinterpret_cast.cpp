
// CPP program to demonstrate working of  
// reinterpret_cast 
//Need to be very careful in using reinterpret_cast
#include <iostream> 
using namespace std; 
  
int main() 
{ 
    int* p = new int(65); 
    char* ch = reinterpret_cast<char*>(p); 
    cout << *p << endl; 
    cout << *ch << endl; 
    cout << p << endl; 
    cout << ch << endl; //Note that *ch and ch give the same results
    return 0; 
} 
/*
Output:

65
A
0x1609c20
A
*/