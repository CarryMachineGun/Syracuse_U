#include <iostream>

using namespace std;

int main() {
	int k;//static allocaiton
	//cout << k << endl; Error!

	//Dynamic memory management

	//@Yuchen_keyPoint: using new to return the point of a dynamic allocated entity.
	//@Yuchen: 'new' return a pointer
	int* p1 = new int(5);//the operator new requests the system for a storage space and
	//returns the address of the storage sapce

	cout << p1 << " " << *p1 << endl;

	//@Yuchen_keyPoint: using 'delete; to remove the dynamic allocated entity from system.
	
	//@Yuchen_Qst: what will happend if we dont 'delete p1' but do 'p1 = new int(6)' instead? A: This will cause a memory leak.
	
	//@Yuchen_Qst: Will the leaked memory be released when the program terminates? A: Yes it will. The OS still keeps track of all the memory allocated to a process, and will free it when that process terminates.
	delete p1;//return object (and its space) pointed by p1 to system
	// delete p1; //errors

	//!!!!!!!!!!!!!!
	//@Yuchen_Qst: Why the line below can still be printed? and will the pointer be released at end of the program? Why no error?
	cout << *p1 <<  endl;  //Error!
	// int* l = new int(100);
	// p1 = l;

	k = 100;
	p1 = &k;

	//@Yuchen_keyPoint: only can delete dynamic object; k is a static object.
	// delete p1;  

	p1 = new int[5]{ 1,2,3,4,5 };
	//Creates a dynamic array and retruns the address of the first element.
	for (int i = 0; i < 5; ++i) { cout << p1[i] << " "; }
	cout << endl;
	delete[] p1;//delete the dynamic array pointed by p1

	int A[6]{ 1,2,3,4,5,6 };
	for (int i : A) { cout << i << " "; }//p1 will not work for now.
	cout << endl;
	
	k = 2;
	//int AA[k];  array size has to be a constant
	
	p1 = new int[k];//no error.
	delete[] p1;

	return 0;
}