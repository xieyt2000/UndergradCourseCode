#include<iostream>
using namespace std;
char *sum(char *a,char *b){
	char *c=new char[3];
	*c=a[0]+b[0]-'0';
	*(c+1)=a[1]+b[1]-'0';
	return c;
}
int main(){
	char a[3]="11",  b[3]="22";
	int *c=&a[0]
	cout<<sum(a,b)<<endl<<&a;
	return 0;
}
