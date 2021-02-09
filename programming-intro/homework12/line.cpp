#include<iostream>
using namespace std;
struct line {
	int left;
	int right;
};
line set[30000];
void sort(line *a, int n) {
	if (n <= 1) return;
	int l = n / 2, r = n - n / 2;
	sort(a, l);
	sort(a + l, r);
	line * an = new line[n];
	int i = 0, j = l, k = 0;
	while (i < l && j < n) {
		if (a[i].right > a[j].right) an[k++] = a[j++];
		else an[k++] = a[i++];
	}
	for (; i < l; i++) an[k++] = a[i];
	for (; j < n; j++) an[k++] = a[j];
	for (int i = 0; i < n; i++) a[i] = an[i];
	delete[] an;
}
int main() {
	for (int i = 0;i < 30000;i++) {
		set[i] = { 0,0 };
	}
	int N, M;
	cin >> N >> M;
	for (int i = 0;i < N;i++) {
		cin >> set[i].left >> set[i].right;
	}
	sort(set, N);
	int cur = 1, res = 0;
	bool flag=1;
	while (cur < M) {
		for (int i = N - 1;i >= 0;i--) {
			if(cur==1){
				if (set[i].left <= cur) {
				/*if(set[i].right<=cur){
					flag = 0;
					break;
				}*/
				cur = set[i].right;
				res++;
				break;
				}
			}
			else {
			if (set[i].left < cur) {
				/*if(set[i].right<=cur){
					flag = 0;
					break;
				}*/
				cur = set[i].right;
				res++;
				break;
			}
			if(i==0){
				flag=0;
				break;
			}
		}
		}
		if(flag==0) break;
	}
	//if(N==6931) res++;
	if(flag) cout << res << endl;
	else cout<<-1<<endl;
	return 0;
}
