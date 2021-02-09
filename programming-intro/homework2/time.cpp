#include<iostream>
using namespace std;
int main(){
	int a=0;
	cin>>a;
	int b=a/1440,c=a%1440/60,d=a%1440%60; 
	cout<<b<<" "<<c<<" "<<d<<" ";
	return 0;
}
