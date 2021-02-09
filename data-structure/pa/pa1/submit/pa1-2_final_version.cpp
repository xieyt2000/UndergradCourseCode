#define _CRT_SECURE_NO_WARNINGS
#include<cstdio>
#include<cstring>
#include<stdlib.h>

const int MAX_POINTS = 210000;

enum side
{
	left,right,on
};

long long pointsX[MAX_POINTS], pointsY[MAX_POINTS];
long long queryX, queryY;
int n, m;

int compareLongLong(const void* a, const void* b)
{
	return (*(long long*)a - *(long long*)b);
}

//P is the point to test. RQ is the line.
//from https://blog.csdn.net/qq_27161673/article/details/80024564
side toLeftTest(long long t_PX, long long t_PY, long long t_QX, long long t_QY, long long t_RX, long long t_RY)
{
	long long crossProductLength =
		(t_QX * t_RY + t_PX * t_QY + t_PY * t_RX - t_PX * t_RY - t_QY * t_RX - t_PY * t_QX);
	if (crossProductLength > 0)
	{
		return left;
	}
	else if (crossProductLength < 0)
	{
		return right;
	}
	return on;
}

int binarySearchTest(long long t_queryX, long long t_queryY)
{
	//interval left close right open
	int low = 0, high = n;
	while (high - low > 0)
	{
		int middle = (high + low) / 2;
		side queryToThisLine = toLeftTest(t_queryX, t_queryY, pointsX[middle], 0, 0, pointsY[middle]);
		if (queryToThisLine == on)
		{
			return (middle + 1);
		}
		else if (queryToThisLine == left)
		{
			high = middle;
		}
		else
		{
			low = middle + 1;
		}
	}
	return low;
}

int main()
{
	scanf("%d", &n);
	for (int i = 0; i < n; i++)
	{
		scanf("%lld", &pointsX[i]);
	}
	for (int i = 0; i < n; i++)
	{
		scanf("%lld", &pointsY[i]);
	}
	qsort(pointsX, n, sizeof(long long), compareLongLong);
	qsort(pointsY, n, sizeof(long long), compareLongLong);

	scanf("%d", &m);
	for (int i = 0; i < m; i++)
	{
		scanf("%lld%lld", &queryX, &queryY);
		printf("%d\n", binarySearchTest(queryX, queryY));
	}
	
	return 0;
}
