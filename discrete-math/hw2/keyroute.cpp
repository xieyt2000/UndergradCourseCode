#include<iostream>
#include<algorithm>
#include<vector>
#include<queue>
using namespace std;
int n;
const int UpperBound = 1100;
vector<vector<int>> ClassPres;//0 is source n+1 is sink
vector<vector<int>> ClassAfters;//0 is source n+1 is sink
int PresCount[UpperBound] = {};
vector<vector<int>> ClassByLength;
int Length[UpperBound];
vector<int> SortedClass;
void TopologicalSort()	//上一次实验第三题
{
	queue<int> oprClass;
	oprClass.push(0);
	SortedClass.push_back(0);
	while (!oprClass.empty())
	{
		int opr = oprClass.front();
		oprClass.pop();
		for (auto i : ClassAfters[opr])
		{
			PresCount[i]--;
			if (PresCount[i] == 0)
			{
				oprClass.push(i);
				SortedClass.push_back(i);
			}
		}
	}
}
int GenerateLength()
{
	Length[0] = 0;
	ClassByLength[0].push_back(0);
	int ret = 0;
	for (auto i = SortedClass.begin() + 1; i != SortedClass.end(); i++)
	{
		int tmpMax = 0;
		for (auto j : ClassPres[*i])
		{
			if (Length[j] > tmpMax) tmpMax = Length[j];
		}
		Length[*i] = tmpMax + 1;
		ClassByLength[tmpMax + 1].push_back(*i);
		if (tmpMax + 1 > ret) ret = tmpMax + 1;
	}
	return ret;
}
int main()
{
	cin >> n;
	ClassAfters.resize(n + 10);
	ClassPres.resize(n + 10);
	ClassByLength.resize(n + 10);
	for (int i = 1; i <= n; i++)
	{
		int c = 0, tmp = 0;
		cin >> c;
		PresCount[i] = c;
		for (int j = 0; j < c; j++)
		{
			cin >> tmp;
			ClassPres[i].push_back(tmp);
			ClassAfters[tmp].push_back(i);
		}
	}
	for (int i = 1; i <= n; i++)
	{
		if (ClassPres[i].empty())
		{
			ClassAfters[0].push_back(i);
			ClassPres[i].push_back(0);
			PresCount[i]++;
		}
		if (ClassAfters[i].empty())
		{
			PresCount[n + 1]++;
			ClassAfters[i].push_back(n + 1);
			ClassPres[n + 1].push_back(i);
		}
	}
	TopologicalSort();
	int ans1 = GenerateLength();
	ans1--;
	int ans2 = UpperBound;
	for (auto i = ClassByLength.begin() + 1; i != ClassByLength.begin() + ans1; i++)
	{
		if ((*i).size() < ans2) ans2 = (*i).size();
	}
	cout << ans1 << " " << ans2 << endl;
	return 0;
}
