#include<iostream>
#include<cmath>
using namespace std;

int main(){
	int I,J,dig[15];
	cin>>I;
	for(int j=1;j<15;j++){
		dig[j]=I%10;
		I=I/10;
		if(I==0){
			J=j;
			break;
		}
    }
	for(int i=1;i<=J;i++){
		cout<<dig[i];
	}
	return 0;
}
