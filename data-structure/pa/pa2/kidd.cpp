#define _CRT_SECURE_NO_WARNINGS
#include<cstdio>
#include<cstring>
#include<stdlib.h>

//in accordance with the text. all interval(segment) is [left, right)

struct Segment
{
	int lazyPro = 0;	//lazy propagation. this->descendant being turned over how many times while not recorded. checked when query
	long long turnTimes = 0;	//total turntimes in the interval
	int lchild = -1;	//[left, mid]
	int rchild = -1;	//[mid+1, right]
};
int n, m;
Segment segments[(int)1e7];
int usedSegment = 0;
int root = 0;

int newNode()
{
	usedSegment++;
	return usedSegment;
}

void updateLazypro(int& t_segmentID, int t_left, int t_right, int t_lazyPro)
{
	if (t_segmentID == -1)
	{
		t_segmentID = newNode();
	}
	Segment& curSeg = segments[t_segmentID];
	curSeg.lazyPro += t_lazyPro;
	curSeg.turnTimes += ((long long)t_right - (long long)t_left + 1) * (long long)t_lazyPro;
}

void pushLazyPro(Segment& t_segment, int t_left, int t_right)
{
	if (t_segment.lazyPro == 0)
	{
		return;
	}
	long long middle = ((long long)t_left + (long long)t_right) / 2;
	updateLazypro(t_segment.lchild, t_left, middle, t_segment.lazyPro);
	updateLazypro(t_segment.rchild, middle + 1, t_right, t_segment.lazyPro);
	t_segment.lazyPro = 0;
}

//reference: https://www.cnblogs.com/bullshit/p/9660578.html and dsa lecture note
void turnOver(int& t_segmentID, int t_left, int t_right, int t_targetLeft, int t_targetRight)	//assert(t_left<=t_targetLeft&&t_right>=t_targetRight)
{
	if (!(t_left <= t_targetLeft && t_right >= t_targetRight)) throw "?";
	if (t_segmentID == -1)	//new node
	{
		t_segmentID = newNode();
	}
	Segment& curSeg = segments[t_segmentID];
	curSeg.turnTimes += t_targetRight - t_targetLeft + 1;
	if (t_left == t_targetLeft && t_right == t_targetRight)	//finish. lazy propagation++
	{
		curSeg.lazyPro++;
		return;
	}
	//go down
	pushLazyPro(curSeg, t_left, t_right);
	long long middle = ((long long)t_left + (long long)t_right) / 2;
	if (t_targetLeft >= middle + 1)	//only right child
	{
		turnOver(curSeg.rchild, middle + 1, t_right, t_targetLeft, t_targetRight);
	}
	else if (t_targetRight <= middle)	//only left child
	{
		turnOver(curSeg.lchild, t_left, middle, t_targetLeft, t_targetRight);
	}
	else
	{
		turnOver(curSeg.lchild, t_left, middle, t_targetLeft, middle);
		turnOver(curSeg.rchild, middle + 1, t_right, middle + 1, t_targetRight);
	}
}

long long query(int t_segmentID, int t_left, int t_right, int t_targetLeft, int t_targetRight)
{
	if (!(t_left <= t_targetLeft && t_right >= t_targetRight)) throw "?";
	if (t_segmentID == -1)	//not created before
	{
		return 0;
	}
	Segment& curSeg = segments[t_segmentID];
	if (t_left == t_targetLeft && t_right == t_targetRight)	//finish
	{
		return curSeg.turnTimes;
	}
	//go down
	pushLazyPro(curSeg, t_left, t_right);
	long long middle = ((long long)t_left + (long long)t_right) / 2;
	if (t_targetLeft >= middle + 1)	//only right child
	{
		return query(curSeg.rchild, middle + 1, t_right, t_targetLeft, t_targetRight);
	}
	else if (t_targetRight <= middle)	//only left child
	{
		return query(curSeg.lchild, t_left, middle, t_targetLeft, t_targetRight);
	}
	else
	{
		return (query(curSeg.lchild, t_left, middle, t_targetLeft, middle)
			+ query(curSeg.rchild, middle + 1, t_right, middle + 1, t_targetRight));
	}
}

int main()
{
	scanf("%d%d", &n, &m);
	for (int i = 0; i < m; i++)
	{
		int targetLeft, targetRight;
		char command[5];
		scanf("%s", command);
		scanf("%d%d", &targetLeft, &targetRight);
		if (command[0] == 'H')
		{
			turnOver(root, 1, n, targetLeft, targetRight);
		}
		else
		{
			printf("%lld\n", query(root, 1, n, targetLeft, targetRight));
		}
	}
	return 0;
}