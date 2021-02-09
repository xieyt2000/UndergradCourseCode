#include<iostream>
#include<string.h>
using namespace std;
char m[110], n[110], result[110];
int main(){
	int max;
	cin>>m>>n;
	int M=strlen(m), N=strlen(n);
	if(M>N){
		max=M;
		result[M+1]=0;
	    n[M]=0;
		for(int i=M-1;i>=M-N;i--){
			n[i]=n[i-M+N];
		}
		for(int i=0;i<M-N;i++){
			n[i]='0';
		}
	}
	else{
		max=N;
		result[N+1]=0;
		m[N]=0;
		for(int i=N-1;i>=N-M;i--){
			m[i]=m[i-N+M];
			}
		for(int i=0;i<N-M;i++){
			m[i]='0';
		}
	}
	int carry=max+10;
	result[0]='0';
	for(int i=max-1;i>=0;i--){
		result[i+1]=m[i]+n[i]-'0';
		if(carry==i) result[i+1]++;
		if(result[i+1]>'9'){
			result[i+1]=result[i+1]-10;
			carry=i-1;
		}
	}
	if(carry==-1){
		result[0]++;
	}
	if(result[0]=='0'){
		for(int i=0;i<=max;i++){
			result[i]=result[i+1];
		}
		result[max]=0;
	}
	cout<<result<<endl;
	return 0;
}

