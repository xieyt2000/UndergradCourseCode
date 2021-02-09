#include<iostream>
#include<cstring>
using namespace std;
int main() {
	char in[300], out[300], ex[200];
	cin >> in;
	int len = strlen(in);
	int i = 0;
	while ((2*i + 1 )< len) {
		ex[i] = in[2 * i + 1];
		i++;
	}
	i--;
	for (int j = 0;j <= i / 2;j++) {
		int t = ex[j];
		ex[j] = ex[i - j];
		ex[i - j] = t;
	}	
	i = 0;
	while ((2 * i + 1) < len) {
		in[2 * i + 1] = ex[i];
		i++;
	}
	cout << in << endl;
	return 0;
}
