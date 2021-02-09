#include <iostream>
#include<string>
#include "MyAnswer.h"
using namespace std;

#define Option_A auto testA = f1(b);
#define Option_B auto testB = f2(b);
#define Option_C auto testC = f3(b);
#define Option_D auto testD = f3(b);
#define Option_E auto& testE = f4(f);
#define Option_F auto testF = f5(b);
class A {
public:
	string name;
	A(const string a) {
		name = a;
		cout << "A constructing..." << name << endl;
	}
	A() {
		cout << "A constructing..." << endl;
	}
	~A() {
		cout << "A destructing..." << name << endl;
	}
};
class B {
private:
	static A data1;
	A data2;
public:
	string name;
	B(string a):data2(a + ".data2") {
		name = a;
		cout << "B constructing..." << name << endl;
	}
	B() {
		cout << "B constructing..." << endl;
	}
	~B() {
		cout << "B destructing..." << name << endl;
	}
};
A B::data1("B::data1");

A f1(A b) {//co 1 A de 2 A
	cout << "------after call------" << endl;
	A f("f");
	cout << "------before return------" << endl;
	//cout<<&f;
	return f;
}

A f2(A b) {//de 2 A
	cout << "------after call------" << endl;
	A f = b;
	//A *ff = &f;
	f.name = "f";
	cout << "------before return------" << endl;
	return f;
}

A f3(A b) {//co 1 A de 1 A the first time, next only de 1 A
	cout << "------after call------" << endl;
	static A f("f");
	cout << "------before return------" << endl;
	return f;
}

A& f4(A* b) {//out nothing
	cout << "------after call------" << endl;
	A *f = b;
	cout << "------before return------" << endl;
	return *f;
}

A* f5(A& b) {//out nothing
	cout << "------after call------" << endl;
	A* f = &b;
	cout << "------before return------" << endl;
	return f;
}

void work()
{
	cout << "=======entering work=======" << endl;
	A b("b");
	B t("t");
	const string f00 = "f[0]";
	const string f11 = "f[1]";
	A f[2] = { f00,f11 };
	f[0] = b;
	f[0].name = "f[0]";

	//(1)
	cout << "------before call------" << endl;
	Answer1				//co 1 A, de 1 A
		testC.name = "testC";
		cout << "------after return------" << endl << endl;

	//(2)
	cout << "------before call------" << endl;
	Answer2				//de 1 A
		testD.name = "teseD";
		cout << "------after return------" << endl << endl;

	//(3)
	cout << "------before call------" << endl;
	Answer3           //de 1 A	
		testB.name = "testB";
		cout << "------after return------" << endl << endl;

	//(4)
	cout << "------before call------" << endl;
	Answer4				//out nothing
		cout << "------after return------" << endl << endl;

	//(5)
	cout << "------before call------" << endl;
	Answer5			//co 1 A de 1 A
		testA.name = "testA";
		//cout<<&testA;
		cout << "------after return------" << endl << endl;

	//(6)
	cout << "------before call------" << endl;
	Answer6				//out nothing
		cout << "------after return------" << endl << endl;
	cout << "=======exiting work=======" << endl;
}

int main() {
	cout << "=======entering main=======" << endl;
	work();
	//de 8 A 1 B
	cout << "=======exiting main=======" << endl;
	return 0;
}
//de 2 A
