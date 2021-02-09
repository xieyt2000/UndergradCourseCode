#include<iostream>
using namespace std;
int n,m,a[1100],b[1100],c[2100];
int main(){
	//initialize
	for(int i=0;i<1100;i++){
		a[i]=0;
		b[i]=0;
	}
	for(int i=0;i<2100;i++) c[i]=0;
	// input
	cin>>n;
	for(int i=0;i<n;i++){
		cin>>a[i];
	}
	cin>>m;
	for(int i=0;i<m;i++){
		cin>>b[i];
	}
	// intersect
	for(int i=0;i<n;i++){               
		for(int j=0;j<m;j++){
			if(a[i]==b[j]){
				cout<<a[i]<<" ";
				break;
			}
			if(a[i]<b[j]) break;
		}
	}
	cout<<endl;
	// union
	for(int i=0;i<n;i++){
		c[i]=a[i];
	}
	for(int i=0;i<m;i++){
		c[n+i]=b[i];
	}
	for(int i=m+n-1;i>=0;i--){
		for(int j=0;j<i;j++){
			if(c[j]>c[j+1]){
				int t=c[j];
				c[j]=c[j+1];
				c[j+1]=t;
			}
		}
	}
	for(int i=0;i<m+n-1;i++){
		if(c[i]!=c[i+1]){
			cout<<c[i]<<" ";
		}
	}
	if((m+n)!=0) cout<<c[m+n-1];
	cout<<endl;
	//complement
	for(int i=0;i<n;i++){
		bool e=1;
		for(int j=0;j<m;j++){
			if(a[i]==b[j]){
				e=0;
				break;				
			}			
		}
		if(e) cout<<a[i]<<" ";
	}
	cout<<endl;	
	return 0;
}
