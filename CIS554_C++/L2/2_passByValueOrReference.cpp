#include <iostream>//cout , cin
using namespace std;


void f1(int j) { 
    cout << &j << " _two" << endl;
    j++; 
    }//call/pass by value
//@Yuchen_KP: A new copy of the object is created and used inside the function.
//Any change on this new object will not affect the original object  outside this function.


void f2(int &j) { j++;
    cout << &j << " _three" << endl;
 }//call/pass by reference(
//@Yuchen_KP: The same object outside the funciton is directly used inside the funcion.
//Any change on the object inside the function will acutally change the original object.

void f3(int A[], int size){
	//compiler will change the above into void f3(int * A, int size){
	for (int i = 0; i < size; i++) { A[i]++; }
}
void f4(int* p) {//p (the pointer) is pass by value.
	*p = 55;
	cout << p << " " << *p << " " << &p <<endl;
	p++;//will not affect the original pointer outside the function

}

void f5(int* &p) {//p (the pointer) is pass by value.
	*p = 60;
	cout << p << " " << *p << " " << &p << endl;
	p++;//will not affect the original pointer outside the function

}


int main() {
	//call/pass by value and call/pass by reference

	int i{ 1 };
    cout << &i << " _one" << endl;
	f1(i);
	cout << i << endl;//1
	f2(i);
	cout << i << endl; //2

	int B[4]{ 1,2,3,4 };
	f3(B, 4);
	for (int i : B) { cout << i << " "; }//2 3 4 5
	cout << endl;
	
    int* p2{ new int {50} };
	cout << p2 << " " << *p2 << " " << &p2 << endl;
	
    f4(p2);
	
    f5(p2);
	//!!!!!!!!!!!!!!!
    //@Yuchen_Qst: Why *p2 shows as 0?
	cout << p2 << " " << *p2 << " " << &p2 <<endl;

	return 0;
}