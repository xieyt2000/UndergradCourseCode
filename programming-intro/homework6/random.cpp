#include<iostream>
using namespace std;
int N, a[110], count;
int main(){
	cin>>N;
	count=N;
	for(int i=0;i<N;i++){
		cin>>a[i];
	}
	for(int i=0;i<N;i++){
		if(a[i]==2000) count--; 
		else{		
			for(int j=i+1;j<N;j++){
			if(a[i]==a[j]){
				a[j]=2000;
			}
			if(a[i]>a[j]){
				int t=a[i];
				a[i]=a[j];
				a[j]=t;
			}
			}
		}		
	}
	cout<<count<<endl;
	for(int i=0;i<N;i++){
			if(a[i]==2000) ;
			else cout<<a[i]<<" ";
	}
	cout<<endl;
	return 0;
}
