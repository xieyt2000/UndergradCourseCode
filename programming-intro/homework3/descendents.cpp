//descendents of prime numbers
#include<iostream>
using namespace std;
int main(){
	int a=0,t=0;
	cin>>t;
	for(int i=1;i<=t;i++){
		cin>>a;
		int A=a;
		int count=0;
		for(int j=2;j<=a-1;j++){
			
			if(A%j==0){
				A=A/j; 
				j--; 
				count++	;							
			}
		}
		if(count==2){
			cout<<"Yes"<<endl;
		}
		else{
			cout<<"No"<<endl;
		}		
	}
	return 0;	
}
