#include<iostream>
#include<string.h>
using namespace std;
int n;
int count=0;
int low[1100], high[1100];
int main(){
	cin>>n;
	for(int i=0;i<n;i++){
		cin>>low[i]>>high[i];
	}	
	for(int i=n-1;i>=0;i--){
		for(int j=0;j<i;j++){
			if(low[j]>low[j+1]){
				int tl=low[j];
				low[j]=low[j+1];
				low[j+1]=tl;
				int th=high[j];
				high[j]=high[j+1];
				high[j+1]=th;
			}
		}
	}
	for(int i=0;i<n-1;i++){
		if(high[i]<low[i+1]){
			count=count+high[i]-low[i];
		}
		if(high[i]>=low[i+1]&&high[i]<high[i+1]){
			count=count+low[i+1]-low[i];
		}
		if(high[i]>=high[i+1]){
			count=count+low[i+1]-low[i];
			high[i+1]=high[i];
		}
	}
	count=count+high[n-1]-low[n-1];
	cout<<count<<endl;
	return 0;
}
