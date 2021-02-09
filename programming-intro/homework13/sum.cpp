#include<iostream>
using namespace std;
long long Left[100000] = { 0 }, Right[100000] = { 0 };
int main() {
	int N, num[100000] = { 0 };
	cin >> N;
	long long min1 = 0, ind1 = 0, ind2 = 0, min2=0;
	for (int i = 1;i <= N;i++) {
		cin >> num[i];
		Left[i] = Left[i - 1] + num[i];
		if(Left[i]<min1){
			min1=Left[i];
			ind1=i;
		}
	}
	for (int i = N;i >= 1;i--) {
		Right[i] = Right[i + 1] + num[i];
		if(Right[i]<min2){
			min2=Right[i];
			ind2=i;
		}
	}
	
	/*for (int i = 1;i <= N;i++) {
		for (int j = N;j > i;j--) {
			if (Right[j] + Left[i] < min) {
				min = Right[j] + Left[i];
				ind1 = i;
				ind2 = j;
			}
		}
	}*/	
	if(ind1<ind2) cout << Left[N] - min1 - min2<< endl;
	else{
		int max=0,
		sum1=0;
		for(int i=ind1+1;i<=N;i++){
			sum1=sum1+num[i];
			if(sum1>max) max=sum1;
		}
		sum1=0;
		for(int i=ind2-1;i>=0;i--){
			sum1=sum1+num[i];
			if(sum1>max) max=sum1;
		}
		cout<<max<<endl;
	}
	return 0;
}
