#include<iostream>
using namespace std;
int main(){
	int a[10];
	for(int i=0;i<10;i++){
		cin>>a[i];
	}
	int max=a[0],id=0;
	for(int i=1;i<10;i++){
		if (max<a[i]){
			max=a[i];
			id=i;
		}
	}
	cout<<"第"<<id+1<<"个数最大为"<<max<<endl; 
	return 0;
}
