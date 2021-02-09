#include<iostream>
using namespace std;
int main() {
	int N;
	cin >> N;
	int money[20];
	money[0] = N / 10000;
	N = N - money[0] * 10000;
	money[1] = N / 5000;
	N = N - money[1] * 5000;
	money[2] = N / 1000;
	N = N - money[2] * 1000;
	money[3] = N / 500;
	N = N - money[3] * 500;
	money[4] = N / 200;
	N = N - money[4] * 200;
	money[5] = N / 100;
	N = N - money[5] * 100;
	money[6] = N / 50;
	N = N - money[6] * 50;
	money[7] = N / 20;
	N = N - money[7] * 20;
	money[8] = N / 10;
	N=N-money[8]*10;
	if(N>=5) money[8]++;
	for (int i = 0;i < 8;i++) {
		cout << money[i] << " ";
	}
	cout << money[8] << endl;
	return 0;
}
