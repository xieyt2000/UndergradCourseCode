#include<iostream>
using namespace std;
int main(){ 
	int a, b;
	cin>>a>>b;
	for(int i=a;i<=b;i++){
		if((i<=10)||((i%2!=0)&&(i%3!=0)&&(i%5!=0))){
		int I=i,dig[15]={}, J=0;
		for(int j=1;j<15;j++){
			dig[j]=I%10;
			I=I/10;
			if(I==0){
				J=j;
				break;
			}
		}
		bool isre=1;
		for(int j=1;j<=J/2+1;j++){
			if(dig[j]!=dig[J+1-j]){
				isre=0;
				break;
			}
		}
		if(isre){
			bool isprime=1;
			for(int j=2;j*j<=i+1;j++){
				cout<<j;
				if(i%j==0){
					isprime=0;
					break;
				}
			}
			if(isprime) cout<<i<<endl;
		}
	}
			
		}	
		
	return 0;
}
