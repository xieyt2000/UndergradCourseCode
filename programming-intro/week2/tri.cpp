#include<iostream>
#include<cmath>
using namespace std;
int main(){
	const double PI=3.14159 ;
	double a=0.0, b=0.0, c=0.0 ,d=0.0 ;
	cin>>a>>b>>c>>d;
	a=a/180*PI;
	b=b/180*PI;
	c=c/180*PI;
	d=d/180*PI;
	double answer = acos(cos(a)*cos(b)*cos(c-d)+sin(a)*sin(b));
	cout <<answer<<endl;
	return 0;
} 
