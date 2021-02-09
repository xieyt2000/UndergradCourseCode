#include <iostream>
using namespace std;
class Test {
public:
	int * buf; //// only for demo.
	Test() {
		buf = new int(3); //???3????
		cout << "Test(): this->buf @ " << hex << buf << endl;
	}
	~Test() {
		cout << "~Test(): this->buf @ " << hex << buf << endl;
		if (buf) delete buf;
	}
	Test(const Test& t) : buf(new int(*t.buf)) {
		cout << "Test(const Test&) called. this->buf @ "
			<< hex << buf << endl;
	}
	Test(Test&& t) : buf(t.buf) {
		cout << "Test(Test&&) called. this->buf @ "
			<< hex << buf << endl;
		t.buf = nullptr;
	}
};
Test GetTemp() {
	Test tmp;
	cout << "GetTemp(): tmp.buf @ "
	<< hex << tmp.buf << endl;
	return tmp;
}
void fun(Test t) {
	cout << "fun(Test t): t.buf @ "
	<< hex << t.buf << endl;
}
int main() {
	Test a;
	Test b=move(a);
	return 0;
}

