
//Smart Pointer
#include <iostream>
#include <memory>
#include <vector>
#include <list>

using namespace std;

int main() {
	int* p1{ new int{100} }; //p1 is a "raw" pointer
	
	//All smart pointers: unique, shared, or weak pointers, once declared, will have default initial value nullptr.
	
	//Unique pointer
	unique_ptr<int> up1{ make_unique<int>(10) };
	cout << *up1 << endl;//10
	//unique_ptr<int> up2{ up1 }; Error!  A unique object can only be pointed by 
	//exactly one unique pointer.

	up1.reset(); //the same as up1 = nullptr;
	//unique object 10 will automatically deleted when not pointed by pointer
	//or when reference count = 0;

	//Shared Pointers -- the commonly used smart pointers
	shared_ptr<int> sp1{ make_shared<int>(20) };//{20} won't work.
	cout << *sp1 << endl;//20
	{
		shared_ptr<int> sp2{ sp1 };
		cout << sp1.use_count() << endl;//2 reference count: number of pointers pointing at this object
	}
	cout << sp1.use_count() << endl;//1
	sp1 = make_shared<int>(50);
	//alternatively, sp1.reset(new int(50));  old style
	//Object 20 with RC =0 will be automatically deleted

	weak_ptr<int> wp1{ sp1 };
	cout << sp1.use_count() << endl;//1
	//weak pointers do not contribute to reference count
	sp1.reset();
	//Object 50 will be deleted automatically.
	if (wp1.expired()) cout << "It is expired." << endl;

	sp1 = make_shared<int>(5);
	wp1 = sp1;
	//cout << *wp1 << endl;  Error!  Weak pointers do not support * or -> operator.
	shared_ptr<int> sp2;
	//sp2 = wp1;  weak_ptr can be assigned to shared_ptr

	cout << *wp1.lock() << endl;//lock will return a temporary shared_ptr.
	sp2 = wp1.lock();

	weak_ptr<int> wp2{ make_shared<int>(22) };//shared object 22 will be immediately deleted due to RC = 0.

	int* p2{ new int{99} };
	shared_ptr<int> sp3{ p2 };  
	if (sp3.get() == p2) cout << "Sp3 points to the same objec as p2" << endl;




	sp3.reset();
	//object 99 will be deleted automatically.  Raw poiters do not contribute to RC.

	shared_ptr<int> sp4{ make_shared<int>(44) };
	//shared_ptr<int> sp4{ new int{44} }; is also OK, but slower

	shared_ptr<list<int>> sp5{ make_shared<list<int>>(initializer_list<int>{1,2,3,4,5}) };

	shared_ptr < list<shared_ptr<int>>> sp6{ make_shared<list<shared_ptr<int>>>(
		initializer_list<shared_ptr<int>>{make_shared<int>(10), make_shared<int>(20) }
		)
	};

	list<int*>* p3{ new list<int*>  {new int {10}, new int{20}} };






	return 0;
}

