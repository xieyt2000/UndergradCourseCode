#include<iostream>
using namespace std;

int main(){
	int a=0,*b=&a,**c=&b;
	cout<<b<<endl<<*b<<endl<<c<<endl<<*c<<endl<<**c;
	return 0;
}
