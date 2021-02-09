#include<iostream>
using namespace std;
int len, sear, ver[1984], fin[1988], ma, mi, out;
int findmi(int x, int y){
	int min;
	min=ver[mi];
	for(int i=mi+1;i<=ma;i++){
		if(min>ver[i]){
			min=ver[i];
		} 
	}
	return min;
}
int main(){
	cin>>len>>sear;
	for(int i=0;i<len;i++){
		cin>>ver[i];
	}
	for(int i=1;i<=sear;i++){
		cin>>mi>>ma;
		out=findmi(mi,ma);
		cout<<out<<endl;
	}
	return 0;
}
