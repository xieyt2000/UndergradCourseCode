//decompose
#include<iostream>
using namespace std;
int main(){
	int a=0,b=0,I=0;
	cin>>a>>b;
	for(int i=a;i<=b;i++){
		cout<<i<<"=";
		I=i;//I-quotient after each division
		for(int j=2;j*j<=I+1;j++){//if I is the last quotient, for will break whatsoever
			if(I%j==0){
				cout<<j<<"*";
				I=I/j;
				j--;//to include the square(eg.2*2)
			}//st, the last quotient(on condition of composite number) won't be printed					
		}
		cout<<I;// totalize prime and composite
		cout<<endl;
	}
	return 0;
}
