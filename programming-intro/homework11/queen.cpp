#include<iostream>
using namespace std;
int board[20][20];//0 wont be used row first
int count=0, N;
void queen(int n){//positon queen n in row n
	//cout<<"fuck"<<n<<count<<endl;
	for(int i=1;i<=N;i++){
		if(board[n][i]==1){//on coulumn i
			//cout<<i<<" ";
			for(int j=1;j<n;j++){
				board[j][i]--;
				if((i-j)>0) board[n-j][i-j]--;
				if((i+j)<=N) board[n-j][i+j]--;
			}
			queen(n-1);
			//recall
			for(int j=1;j<n;j++){
				board[j][i]++;
				if((i-j)>0) board[n-j][i-j]++;
				if((i+j)<=N) board[n-j][i+j]++;
			}
			//cout<<endl;
			if(n==1){
				count++;
				return;
			}
		}
	}

}
int main(){
	for(int i=0;i<20;i++){
		for(int j=0;j<20;j++)
		board[i][j]=1;
	}
	cin>>N;
	queen(N);
	cout<<count<<endl;
	return 0;
}
