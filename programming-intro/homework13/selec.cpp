#include<iostream>
using namespace std;
long long num[200000] = { 0 };
long long OccOpt[200000] = {}, SpaOpt[200000] = {};// optimal when []is occupied or space
long long max(long long a, long long b) {
	if (a > b) return a;
	else return b;
}
int main() {
	int N;
	cin >> N;
	for (int i = 1;i <= N;i++) {
		cin >> num[i];
	}

	//num 1 in the sum
	OccOpt[1] = num[1];
	OccOpt[2] = 0;
	SpaOpt[1] = 0;
	SpaOpt[2] = num[1];
	OccOpt[3] = num[1] + num[3];
	SpaOpt[3] = num[1];
	for (int i = 4;i <= N - 1;i++) {
		OccOpt[i] = SpaOpt[i - 1] + num[i];
		SpaOpt[i] = max(OccOpt[i - 1], SpaOpt[i - 1]);
	}
	long long max1 = 0;
	if (N == 1) max1 = num[1];
	else max1 = max(OccOpt[N - 1], SpaOpt[N - 1]);

	//num1 not in the sum
	OccOpt[1] = 0;
	OccOpt[2] = num[2];
	SpaOpt[1] = 0;
	SpaOpt[2] = 0;
	OccOpt[3] = num[3];
	SpaOpt[3] = num[2];
	for (int i = 4;i <= N;i++) {
		OccOpt[i] = SpaOpt[i - 1] + num[i];
		SpaOpt[i] = max(OccOpt[i - 1], SpaOpt[i - 1]);
	}
	long long max2 = 0;
	max2 = max(OccOpt[N], SpaOpt[N]);
	cout << max(max1, max2) << endl;
	return 0;
}
