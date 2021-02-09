//#include"pch.h"
#include<iostream>
#include<cstring>
using namespace std;
int main() {
	int n, a[2000] = {}, inc[2000] = {};//increasing array start form inc[]
	cin >> n;
	inc[n] = 1;
	for (int i = 1;i <= n;i++) cin >> a[i];
	for (int i = n-1;i >=1;i--) {
		int max = 0;
		for (int j = n;j >i;j--) {
			int t = 1;
			if (a[j] <= a[i]) t = 0;
			else t = inc[j] + 1;
			if (t > max) max = t;
		}
		inc[i] = max;
	}
	int res = 0;
	for (int i = 1;i <= n;i++) {
		if (inc[i] > res) res = inc[i];
	}
	cout << res << endl;
	return 0;
}
