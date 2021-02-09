#include<iostream>
//#include <ctime>
using namespace std;

int n, k;
int cntr = 0;

void rpt(int prev, int uBdr, int dpth) {
	if (dpth == k) {
		if (prev <= uBdr) cntr++;
		return;
	}
	for (int i = prev; i <= uBdr; i++) {
		rpt(i, uBdr - i, dpth + 1);
	}
	return;
}

int main() {
	cin >> n >> k;
	//time_t st = clock();
	rpt(1, n, 1);
	cout << cntr << endl;
	//time_t ed = clock();
	//cout << "Time " << ed - st << endl;
	return 0;
}
