#include<iostream>
using namespace std;
bool out(int n){
	for(int i=1;i<n;i++){
		cout<<i<<" ";
	}
	cout<<n<<endl;
	return 0;
}
int main(){
	int n;
	cin>>n;
	out(n);
	return 0;
}
