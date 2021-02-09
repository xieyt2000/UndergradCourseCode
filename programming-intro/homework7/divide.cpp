#include<iostream>
using namespace std;
int pro[420]={0},COUNT[410][10]={0};
int count(int num, int times){
	if(num<times) return 0;          			//number:figure left
	if(times==num) return 1;
	if(times==1){
		if(num>pro[num+200]) return 0;
		if(num<=pro[num+200]) return 1;
	}
	if(COUNT[num+200][times]>0){
		return COUNT[num+200][times];
	}
	int ret=0;
	for(int i=pro[num+200];i>=num/times;i--){      	// i:current divide cell
		pro[num-i+200]=i;
		ret=ret+count(num-i,times-1);
		        								//cout<<i<<" "<<count(num-i,times-1)<<" "<<ret<<endl;
	}
	COUNT[num+200][times]=ret;
	return ret;
}
int main(){
	int n,k,result=0;
	cin>>n>>k;
	pro[n+200]=n;
	cout<<count(n,k);
	return 0;
}
