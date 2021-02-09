#include<iostream>
#include<cmath>
#include<iomanip>
using namespace std;
int main(){

	cout <<	setprecision(3)<<
	 sin(20.0/180.0*3.14159)
	*cos(20.0/180.0*3.14159)
	-cos(10.0/180.0*3.14159)
	/tan(10.0/180.0*3.14159)
	<<endl;
	return 0;
} 
