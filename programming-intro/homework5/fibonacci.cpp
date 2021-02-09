#include<iostream>
using namespace std;
int f[30];
int main(){
	f[0]=1;
	f[1]=1;
	for(int i=2;i<=29;i++){
	f[i]=f[i-1]+f[i-2];
	}
	while(true){
		int n=1;
		int sum=0;
		cin>>n;
		if(n==0) break;
		for(int i=0;i<n;i++) sum=sum+f[i];
		cout<<sum<<endl;
	}
	return 0;
}
