#include<iostream>
using namespace std;
int h=0;
int way_(int n){
	if(n<0) return 0;
	if(n==0) return 1;
	return way_(n-1)+way_(n-2)+way_(n-3);
}
int main(){
	cin>>h;
	if(h>20||h<4){
		cout<<0;
	}
	else{
		cout<<way_(h);
	}
	return 0;
}
