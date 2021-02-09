#include<iostream>
#include<string.h>
using namespace std;
int M[10]={-1,-1,-1,-1,-1,-1,-1,-1,-1,-1}, N[10], m, n, indi=0, count=0;
void lookup(int x){
	bool a=1;
	for(int i=0;i<m;i++){
		if(x==M[i]){
			a=0;
			break;
		}
	}
	if(a){
		count++;
		M[indi]=x;
		indi++;
	}
	if(indi>=m) indi=0;
}
int main(){
	cin>>m>>n;
	for(int i=0;i<n;i++){
		cin>>N[i];
	}
	for(int i=0;i<n;i++){
		lookup(N[i]);
	}
	cout<<count<<endl;
	return 0;
}
