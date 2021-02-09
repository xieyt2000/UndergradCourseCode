#include<iostream>
using namespace std;
unsigned long long pos[200][200];//row[m] column[n]
int main() {
	int n, m;
	cin >> m >> n;
	pos[1][1] = 1;
	for (int i = 1;i <= m;i++) {
		for (int j = 1;j <= n;j++) {
			if( i == 1 && j == 1 ) continue;
			pos[i][j] = pos[i][j - 1] + pos[i - 1][j];
		}
	}
	cout << 1 << endl;
	return 0;
}
