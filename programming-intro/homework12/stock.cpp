#include<iostream>
using namespace std;
int price[200000] = { 0 }, HoPro[200000] = { 0 }, EmPro[200000] = { 0 };
int max(int n, int m) {
	if (n > m) return n;
	else return m;
}
int main() {
	int day;
	cin >> day;
	for (int i = 1;i <= day;i++)
		cin >> price[i];
	HoPro[1] = -1 * price[1];
	for (int i = 2;i <= day;i++) {
		HoPro[i] = max(HoPro[i - 1], EmPro[i - 1] - price[i]);
		EmPro[i] = max(EmPro[i - 1], HoPro[i - 1] + price[i]);
	}
	cout << EmPro[day] << endl;
	return 0;
}
