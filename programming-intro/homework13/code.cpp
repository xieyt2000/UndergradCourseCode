#include<iostream>
#include<cstring>
using namespace std;
char ori[1100000] = {};
long long Delt1[1100000] = {}, Delt2[1100000] = {};
int main() {
	cin >> ori;
	int len = strlen(ori);
	Delt1[len - 1] = 1; Delt2[len - 2] = 1;
	for (int i = len - 2;i >= 0;i--) {
		if (ori[i] == ori[i + 1]) Delt1[i] = Delt1[i + 1];
		else Delt1[i] = Delt1[i + 1] + 1;
	}
	for (int i = len - 3;i >= 0;i--) {
		if (ori[i] == ori[i + 1]) {
			if (ori[i] == ori[i + 2]) Delt2[i] = Delt2[i + 1];
			else Delt2[i] = Delt2[i + 1] + 1;
		}
		else {
			if (ori[i] != ori[i+2]) Delt2[i] = Delt2[i + 1] + Delt1[i + 1];
			else Delt2[i] = Delt2[i + 1] + Delt1[i + 1] - 1;
		}
	}
	//long long res = delt2(ori, len) + delt1(ori, len) + 1;
	//cout<<Delt1[1];
	cout << Delt2[0] + Delt1[0] + 1 << endl;
	return 0;
}
