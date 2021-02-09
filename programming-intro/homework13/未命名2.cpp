#include<cstdio>
#include<cstring>
#include<iostream>
#define ll long long
using namespace std;

const int N = 1e7+5;
int n, st = 1, ed, tot = 0;
ll ans = 0;
char c[N];

int main() {
	scanf("%s",c+1), n = strlen(c+1);
	while( st <= n ) {
		ed = st;
		while( ed <= n && c[ed] == c[st] ) ed++;
		if( ed - st >= 2 ) ans++;
		st = ed;
		tot++;
	}
	ans += (ll)(tot - 1) * tot / 2;
	for(int i = 2; i < n; i++) {
		if( c[i] != c[i-1] && c[i+1] != c[i] && c[i+1] == c[i-1] ) ans--;
	}
	ans += tot;
	ans++;
	cout<<ans<<endl;
}
