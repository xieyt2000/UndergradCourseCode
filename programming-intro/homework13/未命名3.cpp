#include<cstring>
#include<map>
#include<string>
#include<iostream>
using namespace std;

map<string,bool> g;
int ans = 0;

int main() {
	int n = 9;
	string a;
	for(int i = 1; i <= n; i++) {
		for(int j = i + 1; j <= n; j++) {
			a = "";
			for(int k = 1; k <= n; k++) {
				if( k != i && k != j ) a += ((char)(k&1));
			}
			if( !g[a] ) g[a] = 1, ans++;
		}
	}	
	cout<<ans<<endl;
}
