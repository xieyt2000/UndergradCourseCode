#include<iostream>
using namespace std;
int N;
int dig[10]={0};
int count(int n){
	if(n==6174){
		return 0;
	}
	else{
	dig[4]=n/1000, dig[3]=n/100%10, dig[2]=n/10%10, dig[1]=n%10;		
	for(int i=4;i>=1;i--){
		for(int j=1;j<i;j++){
			if(dig[j]>dig[j+1]){
				int t=dig[j];
				dig[j]=dig[j+1];
				dig[j+1]=t;
			}
		}
	}
	int n_=1000*(dig[4]-dig[1])+100*(dig[3]-dig[2])+10*(dig[2]-dig[3])+dig[1]-dig[4];
	return (count(n_)+1);
	}
}
int main(){
	cin>>N;

	cout<<count(N);
	return 0;
}
