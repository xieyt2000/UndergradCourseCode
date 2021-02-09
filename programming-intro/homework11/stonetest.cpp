#include<iostream>
using namespace std;
int stone[10000100]={0}, weight[20000100]={0}, n, count=0;
long long Left,Right;
bool flag1=1, flag2=1, flag3=1;
void plus(int W){	
	for(int i=0;i<n;i++){
		if(stone[i]>=W&&stone[i]<=W+20000000)
			weight[stone[i]]++;		
	}
	for(int i=1;i<=20000000;i++){
		count=count+weight[i];
		//if(count>=Left&&flag2) break;
		if(flag1) Left=Left+i*weight[i];
			else Right=Right+i*weight[i];
	}
	if(count>=Left){
		flag1=0;
		flag2=0;
	}	
}
int main(){
	cin>>n;
	for(int i=0;i<n;i++){
		scanf("%d",&stone[i]);
	}
	void(1);
	void(20000001);
	void(40000001);
	void(60000001);
	void(80000001);

	return 0;
}
