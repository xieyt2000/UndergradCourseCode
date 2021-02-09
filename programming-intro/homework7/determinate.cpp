#include<iostream>
#include<iomanip>
using namespace std;
int main(){
	double det[10][10],N,tempt[10],res=1;
	cin>>N;
	for(int i=1;i<=N;i++){           //row first column second
		for(int j=1;j<=N;j++){
			cin>>det[i][j];
		}
	}
	for(int i=1;i<N;i++){
		if(det[i][i]==0){
			bool flag2=1;
			for(int j=i+1;j<=N;j++){
				if(det[j][i]!=0){
					flag2=0;
					res=res*(-1);
					for(int t=1;t<=N;t++){
						tempt[t]=det[i][t];
						det[i][t]=det[j][t];
						det[j][t]=tempt[t];						
					}
					break;
				}				
			}
			if(flag2) break;			
		}
		for(int j=i+1;j<=N;j++){
			if(det[j][i]!=0){
				double mul1=det[i][i];
				double mul2=det[j][i];
				for(int t=1;t<=N;t++){
					det[i][t]=mul2*det[i][t];
					det[j][t]=mul1*det[j][t];
				}			
				for(int t=1;t<=N;t++){
					det[j][t]=det[j][t]-det[i][t];
				}
				for(int t=1;t<=N;t++){
					det[i][t]=det[i][t]/mul2;
					det[j][t]=det[j][t]/mul1;
				}
			}
	}
	}
	for(int i=1;i<=N;i++){
		res=res*det[i][i];
	}
	cout<<res<<endl;
	return 0;
}
