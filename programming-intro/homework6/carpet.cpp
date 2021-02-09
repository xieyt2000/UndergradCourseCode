#include<iostream>
using namespace std;
int n, result=-1, car[10001][4], x, y;
int main(){
	cin>>n;
	for(int i=0;i<n;i++){
		for(int j=0;j<4;j++) cin>>car[i][j];
	}	
	cin>>x>>y;
	for(int i=0;i<n;i++){
		int a=car[i][0], b=car[i][1], xlen=car[i][2], ylen=car[i][3];
		if((x>=a)&&(x<=(a+xlen))&&(y>=b)&&(y<=(b+ylen))) result=i+1;
	}
	cout<<result<<endl;
	return 0;
}
