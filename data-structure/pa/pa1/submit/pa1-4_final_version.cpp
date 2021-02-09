#define _CRT_SECURE_NO_WARNINGS
#include<cstdio>
#include<cstring>
#include<stdlib.h>

//index start from 1

const int MAX_POINTS = 1e6 + 100;
const int INFINITY = 1e9;

class MonoQueue
{
	
private:
	int data[MAX_POINTS];	//ascending order by minTime. left open right closed. only store the index
	int left = 0;	//data[left]:min
	int right = 0;	//data[right-1]:max

public:
	unsigned long long minTime[MAX_POINTS];	//min time from poiont i to n. minTime[n]==0 and minTime[1]==result
	void push(int t_index)	//ensure that the queue is monotonous
	{
		if (size() > 0)
		{
			while (minTime[data[right - 1]] >= minTime[t_index] && size() > 0)
			{
				right--;
			}
		}
		data[right] = t_index;
		right++;
	}
	int size()
	{
		return (right - left);
	}
	void pop()
	{
		if (size() == 0)
		{
			return;
		}
		left++;
	}
	int head()	//if size =0 return -1
	{
		if (size() == 0)
		{
			return -1;
		}
		return data[left];
	}
	MonoQueue()
	{
		memset(minTime, 0, sizeof(minTime));
	}
};

int t[MAX_POINTS], l[MAX_POINTS], r[MAX_POINTS];	//same to the text. start from 1
MonoQueue queue;
int n;

int min(int t_a, int t_b)
{
	return t_a < t_b ? t_a : t_b;
}

int main()
{
	scanf("%d", &n);
	for (int i = 1; i < n; i++)
	{
		scanf("%d%d%d", &l[i], &r[i], &t[i]);
	}
	queue.push(n); l[n] = n; r[n] = n;	//iter base
	for (int i = n - 1; i > 0; i--)
	{
		//queue sotres index in [l[i+1], r[i+1]]
		while (queue.head() > r[i])
		{
			queue.pop();
		}
		for (int j = min(l[i + 1] - 1,r[i]); j >= l[i]; j--)
		{
			queue.push(j);
		}
		queue.minTime[i] = queue.minTime[queue.head()] + t[i];
	}
	printf("%llu\n", queue.minTime[1]);
	return 0;
}
