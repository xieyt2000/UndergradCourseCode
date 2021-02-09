#include<iostream>
#include<vector>
#include<set>
#include<algorithm>
#include<map>
#define MostVer 20;
using namespace std;
int n, m;
struct vertex
{
	int index;
	//vector<int> linkingEdge;
	vector<int> linkingVertices;
};
//vertex notFound = { -1,{} };
struct edge
{
	int index;
	int v1;
	int v2;
};
vector<vertex> vertices;//1 to n
//vector<edge> edges;//1 to m
vector<vector<vertex>> Graphs;
int indicator = 0;
vector<int> res;
int findVertex(int tarInd, const vector<vertex>& graph)
{
	int count = 0;
	for (auto i : graph)
	{
		if (i.index == tarInd) return count;
		count++;
	}
	return -1;
}
void colors()
{
	while (Graphs.begin() + indicator != Graphs.end())
	{
		bool completeGraph = 1;
		int count = -1;
		for (auto i : Graphs[indicator])
		{
			count++;
			if (i.linkingVertices.size() == Graphs[indicator].size() - 1) continue;
			completeGraph = 0;
			vector<vertex> addEdge;
			vector<vertex> mergeVertex;
			int j = 1;
			int v1 = count;//pos in vector graph, not index
			int v1Ind = Graphs[indicator][v1].index;
			int v2;
			for (;; j++)
			{
				if (j == v1Ind) continue;
				if (find(i.linkingVertices.begin(), i.linkingVertices.end(), j) == i.linkingVertices.end())
				{
					v2 = findVertex(j, Graphs[indicator]);
					if (v2 == -1) continue;
					else break;
				}
			}

			int v2Ind = Graphs[indicator][v2].index;
			//v1v2 not adjsent
			addEdge = Graphs[indicator];
			addEdge[v1].linkingVertices.push_back(v2Ind);
			addEdge[v2].linkingVertices.push_back(v1Ind);
			Graphs.push_back(addEdge);
			//merge v1v2 to v1
			mergeVertex = Graphs[indicator];
			for (auto k : mergeVertex[v2].linkingVertices)
			{
				if (find(mergeVertex[v1].linkingVertices.begin(), mergeVertex[v1].linkingVertices.end(), k) == mergeVertex[v1].linkingVertices.end())
					mergeVertex[v1].linkingVertices.push_back(k);
			}
			mergeVertex.erase(mergeVertex.begin() + v2);
			for (int k = 0; k < mergeVertex.size(); k++)
			{
				for (int t = 0; t < mergeVertex[k].linkingVertices.size(); t++)
				{
					if (mergeVertex[k].linkingVertices[t] == v2Ind)
					{
						if (find(mergeVertex[k].linkingVertices.begin(), mergeVertex[k].linkingVertices.end(), v1Ind) == mergeVertex[k].linkingVertices.end())
						{
							mergeVertex[k].linkingVertices[t] = v1Ind;
						}
						else
						{
							mergeVertex[k].linkingVertices.erase(mergeVertex[k].linkingVertices.begin() + t);
						}
						break;
					}
					
				}
			}
			Graphs.push_back(mergeVertex);
			break;
		}
		if (completeGraph)
		{
			res.push_back(Graphs[indicator].size());
		}
		indicator++;
	}
}
int main()
{
	cin >> n >> m;
	if (m == 0)
	{
		cout << 1 << endl;
		return 0;
	}
	//edges.resize(1);
	vertices.resize(n);
	for (int i = 0; i < m; i++)
		vertices[i].index = i + 1;
	for (int i = 0; i < m; i++)
	{
		int v1, v2;
		cin >> v1 >> v2;
		//edge forInser = { i,v1,v2 };
		//edges.push_back(forInser);
		//vertices[v1].linkingEdge.push_back(i);
		//vertices[v2].linkingEdge.push_back(i);
		vertices[v1-1].linkingVertices.push_back(v2);
		vertices[v2-1].linkingVertices.push_back(v1);
	}
	if (m == n - 1)
	{
		vector<int> nodes;
		bool isTree = 1;
		for (auto i : vertices)
		{
			if (i.linkingVertices.empty()) isTree = 0;
		}
		//if (nodes.size() != n) isTree = 0;
		if (isTree)
		{
			cout << 2 << endl;
			return 0;
		}
	}
	/*for (int i = 1; i <= n; i++)
	{
		sort(vertices[i].linkingVertices.begin(), vertices[i].linkingVertices.end());
	}*/
	Graphs.push_back(vertices);
	colors();
	int Ans = MostVer;
	for (auto i : res)
	{
		if (i < Ans) Ans = i;
	}
	cout << Ans << endl;
	return 0;
}
