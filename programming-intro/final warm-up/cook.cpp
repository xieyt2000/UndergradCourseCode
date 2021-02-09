// ConsoleApplication1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include<iostream>
#include<cstring>
#include<cmath>
using namespace std;
int main() {
	int resquant[10];
	for (int i = 0;i < 4;i++) cin >> resquant[i];
	int dish[10][10] = {
	{ 2,1,0,2 },
	{ 1,1,1,1 },
	{ 0,0,2,1 },
	{ 0,3,0,0 },
	{ 1,0,0,1 }
	};
	int disquant[10] = {};
	for (int i = 0;i < 5;i++) {//dish
		int consume[10] = {};
		int min = 1000;
		for (int j = 0;j < 4;j++) {//res
			if (dish[i][j] != 0) consume[j] = resquant[j] / dish[i][j];
			else continue;
			if (consume[j] < min) min = consume[j];
		}
		disquant[i] += min;
		for (int j = 0;j < 4;j++) {
			resquant[j] = resquant[j] - min * dish[i][j];
		}
	}
	for (int i = 0;i < 5;i++) cout << disquant[i] << endl;
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

