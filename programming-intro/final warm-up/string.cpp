// ConsoleApplication1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include<iostream>
#include<cstring>
#include<cmath>
using namespace std;
char input[200] = {};
char output[1000000] = {};
bool IsSmallLetter(char a) {
	if (a >= 'a'&&a <= 'z') return true;
	return false;
}
bool Isnum(char a) {
	if (a >= '0'&&a <= '9') return true;
	return false;
}
int main() {
	int p1, p2, p3;
	cin >> p1 >> p2 >> p3;
	cin >> input;
	int OutIndi = 0, InIndi = 0;
	int InLen = strlen(input);
	for (;InIndi <= InLen;InIndi++) {
		if (input[InIndi] != '-') {
			output[OutIndi] = input[InIndi];
			OutIndi++;
			continue;
		}
		char pre = input[InIndi - 1], nex = input[InIndi + 1];
		//in[inindi=-]
		if (InIndi == 0) continue;
		bool flagletter = 0, flagnum = 0;
		if (IsSmallLetter(input[InIndi - 1]) &&
			IsSmallLetter(input[InIndi + 1]) &&
			(input[InIndi - 1] < input[InIndi + 1])) {
			flagletter = 1;
			if (p1 == 1) {
				if (p3 == 1) {
					for (char i = 1;i < (input[InIndi + 1] - input[InIndi - 1]);i++) {
						for (int j = 1;j <= p2;j++) {
							output[OutIndi] = pre + i;
							OutIndi++;
						}
					}
				}
				if (p3 == 2) {
					for (char i = 1;i < (input[InIndi + 1] - input[InIndi - 1]);i++) {
						for (int j = 1;j <= p2;j++) {
							output[OutIndi] = nex - i;
							OutIndi++;
						}
					}
				}
			}
			if (p1 == 2) {
				char minus = 'a' - 'A';
				if (p3 == 1) {
					for (char i = 1;i < (input[InIndi + 1] - input[InIndi - 1]);i++) {
						for (int j = 1;j <= p2;j++) {
							output[OutIndi] = pre - minus + i;
							OutIndi++;
						}
					}
				}
				if (p3 == 2) {
					for (char i = 1;i < (input[InIndi + 1] - input[InIndi - 1]);i++) {
						for (int j = 1;j <= p2;j++) {
							output[OutIndi] = nex - minus - i;
							OutIndi++;
						}
					}
				}
			}
			if (p1 == 3) {
				for (char i = 1;i < (input[InIndi + 1] - input[InIndi - 1]);i++) {
					for (int j = 1;j <= p2;j++) {
						output[OutIndi] = '*';
						OutIndi++;
					}
				}
			}
		}
		if (Isnum(input[InIndi - 1]) &&
			Isnum(input[InIndi + 1]) &&
			(input[InIndi - 1] < input[InIndi + 1])) {
			flagnum = 1;
			if (p1 != 3) {
				if (p3 == 1) {
					for (char i = 1;i < (input[InIndi + 1] - input[InIndi - 1]);i++) {
						for (int j = 1;j <= p2;j++) {
							output[OutIndi] = pre + i;
							OutIndi++;
						}
					}
				}
				if (p3 == 2) {
					for (char i = 1;i < (input[InIndi + 1] - input[InIndi - 1]);i++) {
						for (int j = 1;j <= p2;j++) {
							output[OutIndi] = nex - i;
							OutIndi++;
						}
					}
				}
			}
			if (p1 == 3) {
				for (char i = 1;i < (input[InIndi + 1] - input[InIndi - 1]);i++) {
					for (int j = 1;j <= p2;j++) {
						output[OutIndi] = '*';
						OutIndi++;
					}
				}
			}
		}
		if (!flagletter && !flagnum) {
			output[OutIndi] = input[InIndi];
			OutIndi++;
			continue;
		}
	}
	cout << output << endl;
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

