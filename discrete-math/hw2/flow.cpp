#include<iostream>
#include<vector>
#include<set>
#include<algorithm>
#include<map>
#define capacity 5100
#define infinity 1e9;
using namespace std;
int c, q;
int Ans = 0;
int Distance[capacity][capacity];
int opDistance;
struct computer
{
	int x;
	int y;
	int index;
};
vector<computer> computers;
//int smallestTreeMatrix[capacity][capacity];//which pt to which pt (set of edges)
vector<int> smallestTreeList;//record fathers
int depth[capacity] = {};
struct shortestPa
{
	int dis;
	int fromWhich;
};
void GenDis()
{
	for (int i = 0; i < c; i++)
	{
		for (int j = 0; j < i; j++)
		{
			Distance[i][j] =
				(computers[i].x - computers[j].x)
				* (computers[i].x - computers[j].x)
				+ (computers[i].y - computers[j].y)
				* (computers[i].y - computers[j].y);
		}
	}
	for (int i = 0; i < c; i++)
		for (int j = 0; j < i; j++)
			Distance[j][i] = Distance[i][j];
}
void Prim()
{
	//for (int i = 0; i < capacity; i++)
		//for (int j = 0; j < capacity; j++) smallestTreeMatrix[i][j] = 0;
	smallestTreeList.resize(c);
	set<int> intree;
	set<int> rest;
	intree.insert(0);
	depth[0] = 1;//root
	for (int i = 1; i < c; i++) rest.insert(i);
	map<int, shortestPa> shortest;
	for (int i = 1; i < c; i++)
	{
		shortest[i].dis = Distance[0][i];
		shortest[i].fromWhich = 0;
	}
	for (int i = 1; i < c; i++)
	{
		int tmpMin = infinity;
		int from = -1;
		int to = -1;
		for (auto j = shortest.begin(); j != shortest.end(); j++)
		{
			if (j->second.dis < tmpMin)
			{
				tmpMin = j->second.dis;
				to = j->first;
				from = j->second.fromWhich;
			}
		}
		intree.insert(to);
		rest.erase(to);
		shortest.erase(to);
		smallestTreeList[to] = from;
		depth[to] = depth[from] + 1;
		//smallestTreeMatrix[from][to] = 1; smallestTreeMatrix[to][from] = 1;
		for (auto j = shortest.begin(); j != shortest.end(); j++)
		{
			if (Distance[to][j->first] < j->second.dis)
			{
				j->second.dis = Distance[to][j->first];
				j->second.fromWhich = to;
			}
		}
	}
	/*for (int i = 0; i < c; i++)
	{
		vector<int> tmp;
		for (int j = 0; j < c; j++)
		{
			if (smallestTreeMatrix[i][j] == 1) tmp.push_back(j);
		}
		smallestTreeList.push_back(tmp);
	}*/
}
vector<int> route;
/*set<int> alreadyFound;
int Target;
bool finish = 0;
void findFlow(int from, int to)
{
	if (alreadyFound.size() == c) return;
	if (from == Target)
	{
		route.push_back(from);
		finish = 1;
		return;
	}
	if (finish) return;
	route.push_back(from);
	alreadyFound.insert(from);
	bool hasSon = 0;
	for (auto i = smallestTreeList[from].begin(); i != smallestTreeList[from].end(); i++)
	{
		if (finish) return;
		if (alreadyFound.find(*i) == alreadyFound.end())
		{
			hasSon = 1;
			findFlow(*i, to);
		}
	}
	if (!finish) route.pop_back();
}*/
/*vector<int> Found;
vector<int> From;
void findFlow(int from, int to)
{
	bool finish = 0;
	int indicator = 0;
	Found.push_back(from);
	From.push_back(-1);
	while (!finish)
	{
		for (auto i =Found.begin()+indicator;i!=Found.end();i++)
		{
			int ii = *i;
			if (finish) break;
			for (auto j = smallestTreeList[ii].begin();j!=smallestTreeList[ii].end();j++)
			{
				int jj = *j;
				if (jj == to)
				{
					From.push_back(ii);
					Found.push_back(to);
					finish = 1;
					break;
				}
				if (find(Found.begin(), Found.end(), jj) != Found.end())
				{
					From.push_back(ii);
					Found.push_back(jj);
				}
			}
			indicator++;
		}
	}
	int j = to, i = 0;
	while (true)
	{
		route.push_back(j);
		if (j == from) break;
		auto it = find(Found.begin(), Found.end(), j);
		int sub = distance(Found.begin(), it) ;
		j = From[sub];
	}
}*/
int FindFlow(int from, int to)
{
	int ret = 0;
	int dp1 = depth[from];
	int dp2 = depth[to];
	while (dp1 > dp2)
	{
		ret = max(ret, Distance[from][smallestTreeList[from]]);
		from = smallestTreeList[from];
		dp1--;
	}
	while (dp1 < dp2)
	{
		ret = max(ret, Distance[to][smallestTreeList[to]]);
		to = smallestTreeList[to];
		dp2--;
	}
	while (from != to)
	{
		ret = max(ret, Distance[from][smallestTreeList[from]]);
		from = smallestTreeList[from];
		dp1--;
		ret = max(ret, Distance[to][smallestTreeList[to]]);
		to = smallestTreeList[to];
		dp2--;
	}
	return ret;
}
int main()
{
	cin >> c;
	computer tmp;
	for (int i = 0; i < c; i++)
	{
		tmp.index = i;
		cin >> tmp.x;
		cin >> tmp.y;
		computers.push_back(tmp);
	}
	GenDis();
	Prim();
	cin >> q;
	for (int i = 0; i < q; i++)
	{
		int from, to;
		cin >> from >> to;
		from--; to--;
		//Target = to;
		Ans = FindFlow(from, to);
		cout << Ans << endl;
		Ans = 0;
		//finish = 0;
		//alreadyFound.clear();
		//Found.clear();
		//From.clear();
		route.clear();
	}
	return 0;
}
