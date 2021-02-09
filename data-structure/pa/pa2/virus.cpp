#define _CRT_SECURE_NO_WARNINGS
#include<cstdio>
#include<cstring>
#include<stdlib.h>

const int MAX_LENGTH = 1100;

int n, m;
int timeMatrix[MAX_LENGTH][MAX_LENGTH];	//[row][column]  [1,n][1,m]

struct Position
{
	int x = -1;
	int y = -1;
	Position(int t_x, int t_y) :x(t_x), y(t_y) {}
	Position() {};
};

class Queue
{
private:
	Position data[MAX_LENGTH * MAX_LENGTH];	//[head,tail)
	int head = 0;
	int tail = 0;
public:
	void push(Position t_data)
	{
		data[tail] = t_data;
		tail++;
	}
	Position pop()
	{
		head++;
		return data[head - 1];
	}
	bool empty()
	{
		return (tail - head <= 0);
	}
};

Queue queue;
void update(const Position& t_pos, int t_time)
{
	if (timeMatrix[t_pos.x][t_pos.y] > -1)
	{
		return;
	}
	timeMatrix[t_pos.x][t_pos.y] = t_time;
	queue.push(t_pos);
}
void bfs()
{
	while (!queue.empty())
	{
		Position iterPos = queue.pop();
		int iterx = iterPos.x, itery = iterPos.y;
		int nextTime = timeMatrix[iterx][itery] + 1;
		if (iterx > 1)	//up
		{
			update(Position(iterx - 1, itery), nextTime);
		}
		if (iterx < n)	//down
		{
			update(Position(iterx + 1, itery), nextTime);
		}
		if (itery > 1)	//left
		{
			update(Position(iterx, itery - 1), nextTime);
		}
		if (itery < m)	//right
		{
			update(Position(iterx, itery + 1), nextTime);
		}
	}
}

int main()
{
	for (int i = 0; i < MAX_LENGTH; i++)
	{
		for (int j = 0; j < MAX_LENGTH; j++)
		{
			timeMatrix[i][j] = -1;
		}
	}
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; i++)
	{
		for (int j = 1; j <= m; j++)
		{
			char thisInput;
			scanf(" %c", &thisInput);
			if (thisInput == '0')
			{
				timeMatrix[i][j] = 0;
				queue.push(Position(i, j));
			}
		}
	}
	bfs();
	long long result = 0;
	for (int i = 1; i <= n; i++)
	{
		for (int j = 1; j <= m; j++)
		{
			result += timeMatrix[i][j];
		}
	}
	printf("%lld\n", result);
	return 0;
}