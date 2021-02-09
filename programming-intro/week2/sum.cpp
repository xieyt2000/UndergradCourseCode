#include<iostream>
#include<cmath>
using namespace std;
int main(){
	int n=0,a=0,b=0,c=0;
	cin>>n;
	a=(0+n/3*3)*(n/3+1)/2;
	b=(0+n/5*5)*(n/5+1)/2;
	c=a+b;
	cout<<c;
	return 0;
}
