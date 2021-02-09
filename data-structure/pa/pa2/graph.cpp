#define _CRT_SECURE_NO_WARNINGS
#include<cstdio>
#include<cstring>
#include<stdlib.h>

const int MAX_NODES = 1e5 + 100;
const int MAX_EDGES = 2e5 + 100;

struct Edge
{
	int point1 = -1;
	int point2 = -1;
};

class Vector
{
private:
	int* data = nullptr;
	int capacity = 0;
public:
	int size = 0;
	~Vector()
	{
		if (data)
		{
			delete[] data;
		}
	}
	void push_back(int t_data)
	{
		if (!data)
		{
			capacity = 1;
			size = 0;
			data = new int[capacity];
		}
		if (size == capacity)
		{
			capacity *= 2;
			int* newSpace = new int[capacity];
			memcpy(newSpace, data, size * sizeof(int));
			delete[] data;
			data = newSpace;
		}
		data[size] = t_data;
		size++;
	}
	int& operator[](int index)
	{
		return data[index];
	}
};

class Stack
{
private:
	int data[MAX_EDGES];
	int topIndex = -1;	//data[topIndex] is top
public:
	void push(int t_data)
	{
		topIndex++;
		data[topIndex] = t_data;
	}
	bool empty()
	{
		return topIndex < 0;
	}
	int pop()
	{
		topIndex--;
		return data[topIndex + 1];
	}
	int top()
	{
		return data[topIndex];
	}
	void clear()
	{
		topIndex = -1;
	}
};

int n, m, q;
// nodes index start from 1(same as the text)
Edge oriEdges[MAX_EDGES];
int nodesNeighborListIndex[MAX_NODES];	//adjNodesListIndex[n+1] is the lfirst invalid data 
int nodesNeighborsList[2 * MAX_EDGES];	//adj of node i begains at [adjNodesListIndex[i]].
bool nodeIsCut[MAX_NODES];
int bccCount = 0;
Vector cutNodeNeighbors[MAX_NODES];	//neighbor bcc of the cutnode. if it's not cutnode, then vec is empty.
int nodeToBcc[MAX_NODES];	//if 0, then this node is cutnode
Vector bcc[MAX_NODES];	//all the bcc and nodes in them
Vector cutNodeInBcc[MAX_NODES];	//cut node in each bcc

int min(int t_a, int t_b)
{
	return (t_a < t_b ? t_a : t_b);
}
bool noNeighbor(int t_node)
{
	return nodesNeighborListIndex[t_node] == nodesNeighborListIndex[t_node + 1];
}

//from https://www.cnblogs.com/Al-Ca/p/11181829.html and dsacpp.graph.bcc
//find bcc
//variables only used in tarjan
int dTime[MAX_EDGES], fTime[MAX_EDGES], totalTime, root;
Stack tarjanStack;
void tarjan(int t_node)
{
	totalTime++;
	fTime[t_node] = totalTime; dTime[t_node] = totalTime;
	tarjanStack.push(t_node);
	if (t_node == root && noNeighbor(t_node))
	{
		bccCount++;
		bcc[bccCount].push_back(t_node);
		return;
	}
	int flag = 0;
	for (int neighborIndex = nodesNeighborListIndex[t_node]; neighborIndex < nodesNeighborListIndex[t_node + 1]; neighborIndex++)
	{
		int curNeighbor = nodesNeighborsList[neighborIndex];
		if (!dTime[curNeighbor])
		{
			tarjan(curNeighbor);
			fTime[t_node] = min(fTime[t_node], fTime[curNeighbor]);
			if (fTime[curNeighbor] >= dTime[t_node])
			{
				flag++;
				if (t_node != root || flag > 1)
				{
					nodeIsCut[t_node] = true;
				}
				bccCount++;
				int iterNodeInBcc;
				do
				{
					iterNodeInBcc = tarjanStack.pop();
					bcc[bccCount].push_back(iterNodeInBcc);
				} while (iterNodeInBcc != curNeighbor);
				bcc[bccCount].push_back(t_node);
			}
		}
		else
		{
			fTime[t_node] = min(fTime[t_node], dTime[curNeighbor]);
		}
	}
}

//search function
//variable only used in search
bool visitedBCC[MAX_NODES];
bool visitedCutNode[MAX_NODES];
int result[MAX_NODES];
Stack dfsStack;	//cutnode and ccb. if cutnode, the index is negtive. if bottom is cutnode, that means pt1 is cutnode.
bool searchFinish = false;
void dfs(int t_curIndex, int t_targetPt)
{
	if (searchFinish)
	{
		return;
	}
	dfsStack.push(t_curIndex);
	bool curIsCutNode = (t_curIndex < 0);
	(curIsCutNode ? visitedCutNode[-t_curIndex] : visitedBCC[t_curIndex]) = true;
	Vector& travVec =
		(curIsCutNode ? cutNodeNeighbors[-t_curIndex] : cutNodeInBcc[t_curIndex]);
	for (int i = 0; i < travVec.size; i++)
	{
		if (searchFinish)
		{
			return;
		}
		int iTravIndex = travVec[i];
		if (curIsCutNode)	//visit bcc
		{
			if (visitedBCC[iTravIndex])
			{
				continue;
			}
			for (int j = 0; j < bcc[iTravIndex].size; j++)
			{
				if (bcc[iTravIndex][j] == t_targetPt)
				{
					searchFinish = true;
					return;
				}
			}
			dfs(iTravIndex, t_targetPt);
		}
		else	//visit cutnode
		{
			if (visitedCutNode[iTravIndex])
			{
				continue;
			}
			if (iTravIndex == t_targetPt)
			{
				searchFinish = true;
				return;
			}
			dfs(-iTravIndex, t_targetPt);
		}
	}
	if (searchFinish)
	{
		return;
	}
	dfsStack.pop();
}

int cmp(const void* _a, const void* _b)
{
	int* a = (int*)_a;
	int* b = (int*)_b;
	return *a - *b;
}

void query(int t_pt1, int t_pt2)
{
	memset(visitedBCC, 0, sizeof(visitedBCC));
	memset(visitedCutNode, 0, sizeof(visitedCutNode));
	searchFinish = false;
	dfsStack.clear();
	if (nodeIsCut[t_pt1])
	{
		dfs(-t_pt1, t_pt2);
	}
	else
	{
		int pt1Bcc = nodeToBcc[t_pt1];
		dfs(pt1Bcc, t_pt2);
	}
	int resultLen = 0;
	while (!dfsStack.empty())	
	{
		int stackTop = dfsStack.pop();
		if (stackTop < 0)
		{
			result[resultLen] = -stackTop;
			resultLen++;
		}
	}
	result[resultLen] = t_pt1;	//dont bother about repeated element, they'll be ignored when output
	resultLen++;
	result[resultLen] = t_pt2;
	resultLen++;
	qsort(result, resultLen, sizeof(int), cmp);
	for (int i = 0; i < resultLen - 1; i++)
	{
		if (result[i] != result[i + 1])
		{
			printf("%d ", result[i]);
		}
	}
	printf("%d\n", result[resultLen - 1]);
}

//main function
//variables only for input
int nodesNeiborsCount[MAX_NODES];
int alreadyPutIndex[MAX_NODES];

void initialize()
{
	memset(nodesNeiborsCount, 0, sizeof(nodesNeiborsCount));
	memset(alreadyPutIndex, 0, sizeof(alreadyPutIndex));
	memset(nodesNeighborsList, 0, sizeof(nodesNeighborsList));
	memset(nodesNeighborListIndex, 0, sizeof(nodesNeighborListIndex));
	memset(nodeIsCut, 0, sizeof(nodeIsCut));
	memset(dTime, 0, sizeof(dTime));
	memset(fTime, 0, sizeof(fTime));
	memset(cutNodeNeighbors, 0, sizeof(cutNodeNeighbors));
	memset(nodeToBcc, 0, sizeof(nodeToBcc));
}

int main()
{
	initialize();
	//input
	scanf("%d%d", &n, &m);
	for (int i = 0; i < m; i++)
	{
		int point1, point2;
		scanf("%d%d", &point1, &point2);
		nodesNeiborsCount[point1]++; nodesNeiborsCount[point2]++;
		oriEdges[i].point1 = point1; oriEdges[i].point2 = point2;
	}
	for (int i = 1; i <= n + 1; i++)
	{
		nodesNeighborListIndex[i] = nodesNeiborsCount[i - 1] + nodesNeighborListIndex[i - 1];
		alreadyPutIndex[i] = nodesNeighborListIndex[i];
	}
	for (int i = 0; i < m; i++)
	{
		Edge curEdge = oriEdges[i];
		int point1 = curEdge.point1;
		int point2 = curEdge.point2;
		int& pt1PutIndex = alreadyPutIndex[point1];
		int& pt2PutIndex = alreadyPutIndex[point2];
		nodesNeighborsList[pt1PutIndex] = point2;
		pt1PutIndex++;
		nodesNeighborsList[pt2PutIndex] = point1;
		pt2PutIndex++;
	}
	//rebuild graph tarjan
	for (int i = 1; i <= n; i++)
	{
		if (!dTime[i])
		{
			root = i;
			tarjan(i);
		}
	}
	for (int i = 1; i <= bccCount; i++)
	{
		for (int j = 0; j < bcc[i].size; j++)
		{
			int curId = bcc[i][j];
			if (nodeIsCut[curId])
			{
				cutNodeNeighbors[curId].push_back(i);
				cutNodeInBcc[i].push_back(curId);
			}
			else
			{
				nodeToBcc[bcc[i][j]] = i;
			}
		}
	}
	//query
	scanf("%d", &q);
	for (int i = 0; i < q; i++)
	{
		int pt1, pt2;
		scanf("%d%d", &pt1, &pt2);
		query(pt1, pt2);
	}
	return 0;
}