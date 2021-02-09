#include<iostream>
using namespace std;
int main(){
	double x=0.0,y=0.0;
	const double PI=3.14159;
	cin>>x>>y;
	double S=PI*(x*x+y*y)/2;
	int year=S/50+1;
	cout<<year;
	return 0;
}
