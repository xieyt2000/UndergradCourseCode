#include<iostream>
#include<algorithm>
using namespace std;
int m, n;	//v and e
int road[500][500];
int InterTrack[500][500];
const int infinity = (int)1e8;
struct MaxforInter
{
	int Max;
	int WhickInter;
};
MaxforInter maxForInter[500];
int main()
{
	for (int i = 0; i < 500; i++)
	{
		for (int j = 0; j < 500; j++)
		{
			if (i == j)
			{
				road[i][j] = 0;
				InterTrack[i][j] = 0;
				continue;
			}
			road[i][j] = infinity;
			InterTrack[i][j] = infinity;
		}
	}
	cin >> n >> m;
	int u, v, t;
	for (int i = 1; i <= m; i++)
	{
		cin >> u >> v >> t;
		road[u][v] = t;
		road[v][u] = t;
		InterTrack[u][v] = t;
		InterTrack[v][u] = t;
	}
	for (int i = 1; i <= n; i++)
	{
		for (int j = 1; j <= n; j++)
		{
			for (int k = 1; k <= n; k++)
			{
				InterTrack[j][k] = min(InterTrack[j][k], InterTrack[i][k] + InterTrack[j][i]);
			}
		}
	}

	double Min = infinity;
	for (int i = 1; i <= n; i++)
	{
		double temmax = 0;
		for (int j = 1; j <= n; j++)
		{
			if (InterTrack[i][j] > temmax)
			{
				temmax = InterTrack[i][j];
				maxForInter[i].Max = temmax;
				maxForInter[i].WhickInter = j;
			}
		}
		Min = min(Min, temmax);
	}
	for (int i = 1; i <= n; i++)
	{
		for (int j = 1; j < i; j++)
		{
			if (road[i][j] == infinity) continue;
			int iMax = 0;
			int jMax = 0;
			for (int k = 1; k <= n; k++)
			{
				if (InterTrack[i][k] < InterTrack[j][k])
					iMax = max(iMax, InterTrack[i][k]);
				else jMax = max(jMax, InterTrack[j][k]);
			}
			double x = (0.0 + road[i][j] + jMax - iMax) / 2;
			if (x >= road[i][j]) continue;
			if (x <= 0) continue;
			Min = min(Min, iMax + x);
		}
	}
	cout << Min << endl;
	return 0;
}

