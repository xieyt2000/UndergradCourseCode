#include<iostream>
#include<cstring>
#include<cmath>
#include<algorithm>
#include<stdio.h>
using namespace std;
struct candi {
	int Tpts;
	int Ppts;
	int index;
	int minus;//T-p
};
struct candigroup {
	int Tpts;
	int Ppts;
	int index[50];
	int minus;//abs
	int sum;
};
candigroup opt = { 0,0,{},10000,0 };
candigroup cur = { 0,0,{},0,0 };
bool used[500] = {};
int n, m;
candi Candis[500];
void Select(int CandiStart, int LeftToSel) {
	//cur.minus = cur.Tpts - cur.Ppts;
	if (cur.minus > opt.minus) return;
	if (LeftToSel == 0) {
		cur.minus = abs(cur.Tpts - cur.Ppts);
		cur.sum = cur.Tpts + cur.Ppts;
		if (cur.minus < opt.minus) {
			opt = cur;
			return;
		}
		if (cur.minus == opt.minus) {
			if (cur.sum > opt.sum) {
				opt = cur;
				return;
			}
		}
		return;
	}
	if (n - CandiStart + 1 < LeftToSel) return;
	for (int i = CandiStart; i <= n;i++) {
		cur.index[m - LeftToSel + 1] = i;
		cur.Tpts += Candis[i].Tpts;
		cur.Ppts += Candis[i].Ppts;
		Select(i + 1, LeftToSel - 1);
		cur.Tpts = cur.Tpts - Candis[i].Tpts;
		cur.Ppts = cur.Ppts - Candis[i].Ppts;
	}
}
int main() {

	scanf("%d%d", &n, &m);

	for (int i = 1;i <= n;i++) {
		Candis[i].index = i;
		scanf("%d%d", &Candis[i].Tpts, &Candis[i].Ppts);
		//Candis[i].minus = Candis[i].Tpts - Candis[i].Ppts;
	}
	Select(1, m);
	cout << opt.Tpts << " " << opt.Ppts << endl;
	for (int i = 1;i <= m;i++) {
		printf("%d ", opt.index[i]);
	}
	return 0;
}
