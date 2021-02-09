#include<iostream>
using namespace std;
int *sum(int x, int y){
	int* t =&x;
	return t;
}
int main(){
	char **a=new char*[10];
	a[0]=new char [10];
	a[0][0]='1';
	cout<<a<<endl<<*a<<endl<<**a;
	return 0;
}
