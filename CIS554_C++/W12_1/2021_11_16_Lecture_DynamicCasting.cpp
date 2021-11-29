  	

class B {//base class

	int b1 = 1;
protected:
	int b2 = 2;
public:
	int b3 = 3;
	void f1() {
		cout << "B::f1" << endl;
	}
	virtual void f2() { //virtual member function can be redefined in the derived class
		cout << "B::f2" << endl;
		cout << b3 * b3 << endl;
	}
};

class D : public B {

	int d1 = 4;
protected:
	int d2 = 5;
public:
	int d3 = 6;
	void f2() {
		cout << "D::f2" << endl;
		cout << d3 * d3 << endl;
	}
};





	D o1;
	B* p3 = static_cast<B*>(&o1); //upcasting
	D* p4 = dynamic_cast<D*>(p3); //downcasting
	if (!p4) cout << "p4 is nullptr" << endl; //p4 is not nullptr; 
	else { //This else part will be executed
		//p4 has access to b3, d3, f1 and f2
		p4->f1();//prints B::f1
		p4->f2();//prints B::f2 and, in the next line, 9
		cout << p4->d3 << endl;//prints 12515912 (just something arbitrary)
	}