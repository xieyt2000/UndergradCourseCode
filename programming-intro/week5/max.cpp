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
	cout<<"��"<<id+1<<"�������Ϊ"<<max<<endl; 
	return 0;
}
