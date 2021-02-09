// ConsoleApplication1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include<iostream>
#include<cstring>
#include<cmath>
using namespace std;
int Change[100];
bool volumn[100][2000];//after song n volumn possibility
int main() {
	int n, begin, max;
	cin >> n >> begin >> max;
	for (int i = 0;i < 100;i++) {
		for (int j = 0;j < 2000;j++) volumn[i][j] = 0;
	}
	volumn[0][begin] = 1;
	for (int i = 1;i <= n;i++) {
		cin >> Change[i];
		for (int j = 0;j <= max;j++) {
			if (volumn[i - 1][j]) {
				if (((j + Change[i]) >= 0) && ((j + Change[i]) <= max))
					volumn[i][j + Change[i]] = 1;
				if (((j - Change[i]) >= 0) && ((j - Change[i]) <= max))
					volumn[i][j - Change[i]] = 1;
			}
		}
	}
	bool flag = 1;
	for (int i = max;i >= 0;i--) {
		if (volumn[n][i]) {
			cout << i << endl;
			flag = 0;
			break;
		}
	}
	if (flag) cout << -1 << endl;
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

