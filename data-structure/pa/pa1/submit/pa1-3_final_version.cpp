#define _CRT_SECURE_NO_WARNINGS
#include<cstdio>
#include<cstring>
#include<stdlib.h>

//from https://www.cs.helsinki.fi/u/ukkonen/InfCont85.PDF
//for each line, only calc K near the diagonal

const int MAX_LENGTH = 510000;
const int INFINITY = 1e8;

int N, M, K;	//N columns and M lines dp table
char oriStr[MAX_LENGTH], dstStr[MAX_LENGTH];
int oprCountLine1[MAX_LENGTH], oprCountLine2[MAX_LENGTH];	//opr short for operation
bool nowAtLine1 = false;
bool compressed = false;

int min(int t_a, int t_b)
{
	return t_a < t_b ? t_a : t_b;
}

int min(int t_a, int t_b, int t_c)
{
	if (t_a < t_c)
	{
		return min(t_a, t_b);
	}
	return min(t_c, t_b);
}

int max(int t_a, int t_b)
{
	return t_a > t_b ? t_a : t_b;
}

void calOneOprCount(int t_column, int t_line, bool t_sameChar)
{
	int* curLine, *prevLine;
	curLine = nowAtLine1 ? oprCountLine1 : oprCountLine2;
	prevLine = !nowAtLine1 ? oprCountLine1 : oprCountLine2;
	if (t_column == 0)	//base
	{
		if (t_sameChar)
		{
			curLine[t_column] = t_line;
		}
		else
		{
			curLine[t_column] = prevLine[t_column] + 1;
		}
		return;
	}
	if (t_sameChar)
	{
		curLine[t_column] = min(curLine[t_column - 1] + 1, prevLine[t_column] + 1, prevLine[t_column - 1]);
	}
	else
	{
		curLine[t_column] = min(curLine[t_column - 1] + 1, prevLine[t_column] + 1);
	}
}

int getTranformOperations()
{
	for (int i = 0; i < M; i++)//line
	{
		nowAtLine1 = !nowAtLine1;	//swich line
		int columnUp = N, columnLow = 0;
		if (compressed)
		{
			columnLow = max(0, i - K);
			columnUp = min(N, i + K);
		}
		for (int j = columnLow; j < columnUp; j++)//column
		{
			calOneOprCount(j, i, oriStr[j] == dstStr[i]);
		}
		//curline[columnUp] might be called in the next iter
		if (nowAtLine1)
		{
			oprCountLine1[columnUp] = INFINITY;
		}
		else
		{
			oprCountLine2[columnUp] = INFINITY;
		}
	}
	int* curLine= nowAtLine1 ? oprCountLine1 : oprCountLine2;
	return curLine[N - 1] <= K ? curLine[N - 1] : -1;
}

int main()
{
	memset(oprCountLine1, 0, sizeof(oprCountLine1));
	for (int i = 0; i < MAX_LENGTH; i++)
	{
		oprCountLine2[i] = i + 1;	//base
	}
	scanf("%d%d%d", &N,&M,&K);
	getchar();//\n
	if (2 * K < N - 1)
	{
		compressed = true;
	}
	scanf("%[^\n]", oriStr);
	getchar();//\n
	scanf("%[^\n]", dstStr);
	printf("%d", getTranformOperations());
	return 0;
}
