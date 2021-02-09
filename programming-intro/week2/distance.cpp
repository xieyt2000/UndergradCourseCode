//根据经纬度计算两个城市的距离 
#include<iostream>
#include<cmath>
using namespace std;
int main(){
	const double PI=3.14159 ,R=6371;
	double a=0.0, b=0.0, c=0.0 ,d=0.0 ;
	cout <<"请输入城市1的经纬度："<< endl;
	cin>>a>>c;
	cout<<"请输入城市2的经纬度："<<endl;
	cin>>b>>d;
	a=a/180*PI;
	b=b/180*PI;
	c=c/180*PI;
	d=d/180*PI;
	double answer = acos(cos(a)*cos(b)*cos(c-d)+sin(a)*sin(b));
	cout <<answer*R<<endl;
	return 0;
} 
