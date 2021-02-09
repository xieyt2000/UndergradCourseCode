// ConsoleApplication1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include<iostream>
#include<cstring>
#include<cmath>
using namespace std;
bool judge[60000][30];
int possibility[2000000] = {};
int min(int a, int b) {
	if (a < b) return a;
	return b;
}
int main() {
	int m, n;
	cin >> n >> m;
	for (int i = 0;i < n;i++) {
		int tempt = 0;
		for (int j = 0;j < m;j++) {
			cin >> judge[i][j];
			if (judge[i][j]) tempt = (int)pow(2, m - j - 1) + tempt;
		}
		possibility[tempt]++;
	}
	long long ans = 0;
	int UpBound = pow(2, m) - 1;
	for (int i = 0;i < (int)pow(2, m-1); i++) {
		ans += possibility[i]* possibility[UpBound - i];
	}
	cout << ans << endl;
	return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file

