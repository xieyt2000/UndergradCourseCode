#include<iostream>
using namespace std;
int main(){
	int L=0, R=0,sum=0;
	cin>>L>>R;
	for(int i=L;i<=R;i++){
		if(i/1000!=0){
			if(i/1000==2) sum++;
			if(i/100%10==2) sum++;
			if(i/10%10==2) sum++;
			if(i%10==2) sum++;	
		}else if(i/100!=0){
			if(i/100==2) sum++;
			if(i/10%10==2) sum++;
			if(i%10==2) sum++;
		}else if(i/10!=0){
			if(i%10==2) sum++;		
			if(i/10==2)sum++;
		}else if(i==2) sum++;			
		
	}
	cout<<sum;	
	return 0;
}
