#include<iostream>
#include<cstring>
using namespace std;
int main() {
	long long n, stone[2000] = {};//start from 1
	long long cost = 0;
	cin >> n;
	for (int i = 1;i <= n;i++) {
		cin >> stone[i];
	}
	int indicator = 1;
	for (int i = 1; i <= n - 1; i++) {
		long long min = stone[i] + stone[i + 1];
		indicator = i;
		for (int j = i; j < n; j++) {
			long long a = stone[j] + stone[j + 1];
			if (a < min) {
				min = a;
				indicator = j;
			}
		}
		stone[indicator + 1] = stone[indicator] + stone[indicator + 1];
		for (int j = indicator;j > i;j--) {
			stone[j] = stone[j - 1];
		}
		cost = min + cost;
	}
	cout << cost << endl;
	return 0;
}
