#include<iostream>
using namespace std;
int main() {
	int N, pos[100000];
	cin >> N;
	for (int i = 1;i <= N;i++) 
		cin >> pos[i];
	int res = 0, low = 1, high = 1;
	while (high < N) {
		int max = high;
		for (int i = low;i <= high;i++) {
			int tempt = i + pos[i];
			if (tempt > max) max = tempt;
		}
		low = high;
		high = max;
		res++;
	} 
	cout << res << endl ;
	return 0;
}
