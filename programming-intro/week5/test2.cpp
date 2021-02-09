#include<iostream>
using namespace std;

int main(){
	char a[10]="abcdefdfa";
	char*b=&a[0];
	b++;
	cout<<b;
	return 0;
}
