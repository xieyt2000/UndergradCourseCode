//#include"pch.h"
#include<iostream>
#include<cstring>
using namespace std;
unsigned long long MergeCost[2000][2000];//opt cost of merge stone i to j
unsigned long long stone[2000] = {};//start from 1
unsigned long long merge(int low, int up) {
	if (MergeCost[low][up] > 0) return MergeCost[low][up];
	if (low >= up) return 0;
	if (up == low + 1) {
		MergeCost[low][up] = stone[low] + stone[up];
		return (MergeCost[low][up]);
	}
	unsigned long long sum = 0;
	for (int i = low;i <= up;i++) sum = sum + stone[i];
	unsigned long long min = merge(low + 1, up) + sum;
	for (int i = low + 1;i <= up-1 ;i++) {
		long long a = merge(low, i) + merge(i+1, up) + sum;
		if (a < min) min = a;
	}
	MergeCost[low][up] = min;
	return (MergeCost[low][up]);
}
int main() {
	for (int i = 0;i < 1999;i++) {
		for (int j = 0;j < 1999;j++) MergeCost[i][j] = 0;
	}
	int n;
	cin >> n;
	for (int i = 1;i <= n;i++) cin >> stone[i];
	unsigned long long cost = merge(1, n);
	cout << cost << endl;
	return 0;
}
