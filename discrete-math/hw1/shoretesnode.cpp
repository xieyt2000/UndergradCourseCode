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
			int l = road[i][j];
			int smallerMaxNode, biggerMaxNode;
			if (maxForInter[i].Max <= maxForInter[j].Max)
			{
				smallerMaxNode = i;
				biggerMaxNode = j;
			}
			else
			{
				smallerMaxNode = j;
				biggerMaxNode = i;
			}
			if (maxForInter[smallerMaxNode].Max <= InterTrack[biggerMaxNode][maxForInter[smallerMaxNode].WhickInter]) 
				continue;
			bool ConsiBig[500];		//mean only consider the smallermax side
			int SmallMax = 0;
			int BigMax = InterTrack[biggerMaxNode][maxForInter[smallerMaxNode].WhickInter];
			for (int k = 1; k <= n; k++)
			{
				
				if (InterTrack[biggerMaxNode][k] >= maxForInter[smallerMaxNode].Max)
				{
					ConsiBig[k] = 0;
					SmallMax = max(SmallMax, InterTrack[smallerMaxNode][k]);
				}
				else ConsiBig[k] = 1;
			}
			bool ConsiSmall[500];		//mean not to consider this node at all
			for (int k = 1; k <= n; k++)
			{

				if (InterTrack[smallerMaxNode][k] <= SmallMax)
					ConsiSmall[k] = 0;
				else ConsiSmall[k] = 1;				
			}
			ConsiSmall[maxForInter[smallerMaxNode].WhickInter] = 0;
			bool flag1 = 1;
			int Left[500];
			int leftcount = -1;
			for (int k = 1; k <= n; k++)
			{
				if (ConsiBig[k] && ConsiSmall[k])
				{
					flag1 = 0;
					leftcount++;
					Left[leftcount] = k;
				}
			}
			double x = 0.5;
			if (flag1)
			{
				x = 0.5*(BigMax - SmallMax + l);
				if (x > 0 && x < l)
				{
					Min = min(Min, SmallMax + x);
				}
				continue;
			}
			
		}
	}
	cout << Min << endl;
	return 0;
}
