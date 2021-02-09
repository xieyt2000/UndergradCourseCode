#include<iostream>
#include<algorithm>
using namespace std;
int n;
struct After
{
	int index;
	After* nextAfter;
};
struct LongestPre
{
	int index;
	LongestPre* next;
};
const int UpperBound = (int)1e6 + 10000;
int ClassLenth[UpperBound] = {};//start from 1
int ClassPres[UpperBound] = {};//start from 1
int ClassAfters[UpperBound] = {};//start from 1
After* ClassAFtersIndex[UpperBound]; //start from 1
int* ClassPresIndex[UpperBound];//start from 1, but all members start from 0
int SortedNode[UpperBound] = {};//from 1 to n
int LongestPath[UpperBound] = {};//from 1 to n
int EarlyFinish[UpperBound] = {};
LongestPre* LongestPathPreIndex[UpperBound];
bool KeyRoute[UpperBound] = {};
struct queue 
{//right open left closed right in left out
	int left;
	int right;
	LongestPre* oqueue[UpperBound];
};
void inqueue(queue* Q, LongestPre* p)
{
	Q->oqueue[Q->right] = p;
	Q->right++;
}
LongestPre* outqueue(queue* Q)
{
	Q->left++;
	return Q->oqueue[Q->left -1];
}
bool isempty(queue* Q) 
{
	if (Q->left >= Q->right) return true;
	else return false;
}
queue bfs = { 0,0,nullptr };
int main()
{
	//inital
	for (int i = 0; i < UpperBound; i++)
	{
		ClassPresIndex[i] = nullptr;
		ClassAFtersIndex[i] = nullptr;
		LongestPathPreIndex[i] = nullptr;
		KeyRoute[i] = false;
		bfs.oqueue[i] = nullptr;
	}
	//input
	cin >> n;
	int* ZeroDNode = new int[n + 1];
	int ZeroCount = 0;//no data at the zercount pos
	for (int i = 1; i <= n; i++)
	{
		scanf("%d%d", &ClassLenth[i],&ClassPres[i]);
		if (ClassPres[i] == 0)
		{
			ZeroDNode[ZeroCount] = i;
			ZeroCount++;
			continue;
		}
		int* ipres = new int[ClassPres[i]];
		ClassPresIndex[i] = ipres;
		for (int j = 0; j < ClassPres[i]; j++)
		{
			scanf("%d", &ipres[j]);
			After* temAfter = new After { i, nullptr };
			if (ClassAfters[ipres[j]] == 0)
			{
				ClassAFtersIndex[ipres[j]] = temAfter;
				ClassAfters[ipres[j]]++;
			}
			else
			{
				After* tem = ClassAFtersIndex[ipres[j]];
				for (int k = 1; k < ClassAfters[ipres[j]]; k++)
					tem = tem->nextAfter;
				tem->nextAfter = temAfter;
				ClassAfters[ipres[j]]++;
			}
		}
	}
	//topological sort
	int SortedCount = 1;
	int* PreNumberWhileSorting = new int[n + 10];
	for (int i = 1; i <= n; i++) PreNumberWhileSorting[i] = ClassPres[i];
	while (ZeroCount != 0)
	{
		SortedNode[SortedCount] = ZeroDNode[ZeroCount-1];
		int intoSortedIndex = ZeroDNode[ZeroCount-1];
		ZeroCount--;
		if (ClassAfters[intoSortedIndex] == 0) continue;
		After* tem = ClassAFtersIndex[intoSortedIndex];
		for (int i = 0; i < ClassAfters[intoSortedIndex]; i++)
		{
			PreNumberWhileSorting[tem->index]--;
			if(PreNumberWhileSorting[tem->index]==0)
			{
				ZeroDNode[ZeroCount] = tem->index;
				ZeroCount++;
			}
			tem = tem->nextAfter;
		}
		SortedCount++;
	}
	delete[] PreNumberWhileSorting;
	delete[] ZeroDNode;
	//finding longest
	for (int i = 1; i < n; i++)
	{
		int curindex = SortedNode[i];
		After* temAfter = ClassAFtersIndex[curindex];
		while (temAfter != nullptr)
		{
			LongestPath[temAfter->index] = max(LongestPath[temAfter->index], LongestPath[curindex] + ClassLenth[curindex]);
			temAfter = temAfter->nextAfter;
		}
		
	}
	//recording key
	for (int i = 1; i < n; i++)
	{
		int curindex = SortedNode[i];
		After* temAfter = ClassAFtersIndex[curindex];
		while (temAfter != nullptr)
		{
			if (LongestPath[curindex] + ClassLenth[curindex] == LongestPath[temAfter->index])
			{
				LongestPre* AssiganPre = new LongestPre;
				*AssiganPre = { curindex,nullptr };
				LongestPre* temPre = LongestPathPreIndex[temAfter->index];
				if (temPre == nullptr) LongestPathPreIndex[temAfter->index] = AssiganPre;
				else
				{
					while (temPre->next != nullptr) temPre = temPre->next;
					temPre->next = AssiganPre;
				}
			}

			temAfter = temAfter->nextAfter;
		}
	}
	
	//opearte keyroute
	int max = 0;
	int maxindex = -1;
	for (int i = 1; i <= n; i++)
	{
		EarlyFinish[i] = LongestPath[i] + ClassLenth[i];
		if (EarlyFinish[i] > max)
		{
			maxindex = i;
			max = EarlyFinish[i];
		}
	}
	KeyRoute[maxindex] = true;
	LongestPre* Opearting =LongestPathPreIndex[maxindex];
	while (Opearting!=nullptr)
	{
		inqueue(&bfs, Opearting);
		KeyRoute[Opearting->index] = true;
		Opearting = Opearting->next;
	}
	while (!isempty(&bfs))
	{
		Opearting = outqueue(&bfs);
		KeyRoute[Opearting->index] = true;
		Opearting = LongestPathPreIndex[Opearting->index];
		while (Opearting!=nullptr)
		{
			inqueue(&bfs, Opearting);
			Opearting = Opearting->next;
		}
	}
	//output
	for (int i = 1; i <= n; i++) cout << EarlyFinish[i] << " " << KeyRoute[i] << endl;
	return 0;
}

