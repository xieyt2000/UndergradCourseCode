#include<iostream>
using namespace std;
int main(){
	int n=0;
	bool q=true;
	cin>>n;
	for(int i=2;i*i<=n;i++){
		if(n%i==0) {
			q=0;
			break;
		}		
	}
	cout<<q;	
	return 0;
}
