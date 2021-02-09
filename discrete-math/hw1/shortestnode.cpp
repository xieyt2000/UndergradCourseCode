#include<iostream>
#include<algorithm>
using namespace std;
int m, n;	//v and e
int road[500][500];
const int infinity = (int)1e8;
int main()
{
	for (int i = 0; i < 500; i++)
	{
		for (int j = 0; j < 500; j++)
			road[i][j] = infinity;
	}
	cin >> n >> m;
	int u, v, t;
	for (int i = 1; i <= m; i++)
	{
		cin >> u >> v >> t;
		road[u][v] = t;
		road[v][u] = t;
	}
	for (int i = 1; i <= n; i++)
	{
		for (int j = 1; j <= n; j++)
		{
			for (int k = 1; k <= n; k++)
			{
				road[j][k] = min(road[j][k], road[i][k] + road[j][i]);
			}
		}
	}
	int Min = infinity;
	for (int i = 1; i <= n; i++)
	{
		int temmax = 0;
		for (int j = 1; j <= n; j++)
		{
			temmax = max(temmax, road[i][j]);
		}
		Min = min(temmax, Min);
	}
	cout << Min << endl;
	return 0;
}
