#include<iostream>
using namespace std;
int stone[10000100], L=0, N=0;
bool flag=1;
long long Left = 0, Right = 0;
void QuickSort(int *a, int n) {
	//cout<<a[0]<<n<<a[n-1]<<endl;
	if (n <= 1) return;
	int l = 0, r = n - 2, t = a[n - 1];
	while (l <= r) {
		for (;r >= l;l++) {
			if (a[l] > t) break;
		}		
		for (;r >= l;r--) {
			if (a[r] < t) break;
		}
		if (r > l) {
			int tempt = a[l];
			a[l] = a[r];
			a[r] = tempt;
		}
	}
	int tempt = a[n - 1];
	a[n - 1] = a[l];
	a[l] = tempt;
	if(flag) L=L+l+1;
	else L=L-n+l;
	//cout<<L<<"fuck"<<l<<r<<"fuck"<<a[l]<<endl;
	if (L <= N / 2) {
		flag=1;	
		QuickSort(&a[l + 1], n - l - 1);		
	}		
	else {
		flag=0;
		QuickSort(&a[0], l);		
	}
	
	
}
int main() {
	cin >> N;
	for (int i = 0;i < N;i++) {
		scanf("%d", &stone[i]);
	}
	QuickSort(&stone[0], N);
	for (int i = 0;i < N / 2;i++) {
		Left = Left + stone[i];
		//cout<<stone[i];
	}
	for (int i = N / 2;i < N;i++) {
		Right = Right + stone[i];
		//cout<<stone[i];
	}	
	long long res=Right-Left;
	cout << res <<endl;
	return 0;
}
