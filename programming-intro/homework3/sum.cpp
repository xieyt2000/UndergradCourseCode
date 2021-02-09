#include<iostream>
using namespace std;
int main(){
	int n=0,sum=0,j=0,k=0;
	cin>>n;
	for(int i=1;i<=n/2+1;i++){
		for(j=i;j<=n/2+2;j++){
			sum=sum+j;
			if(sum==n){
				cout<<i<<" "<<j<<" "<<endl;
				break;
			}
			if(sum>n){
				break;
			}
		}
		sum=0;
	}
	return 0;
}
