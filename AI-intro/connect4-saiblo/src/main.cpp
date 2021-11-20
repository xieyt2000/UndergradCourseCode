/*
This file simulates two machine (with the same strategy) compete with each other.
This file is for local debug without Compete project.
Ignore in performance testing.
*/

#include <iostream>
#include <ctime>
#include <cstdlib>
#include "constants.h"
#include "Judge.h"
#include "function.h"
#include "UCT.h"

using namespace std;

//void board21D(const int board[][MAX_N], int M, int N, int board1D[])
//{
//	for (int i = 0; i < M; i++)
//	{
//		for (int j = 0; j < N; j++)
//		{
//			board1D[i * N + j] = board[i][j];
//		}
//	}
//}

void printBoard(int** board, int M, int N, int noX, int noY)
{
	for (int i = 0; i < M; i++)
	{
		for (int j = 0; j < N; j++)
		{
			if (i == noX && j == noY)
			{
				cout << "X";
			}
			else
			{
				cout << board[i][j];
			}
			cout << "\t";
		}
		cout << endl;
	}
	cout << endl;
}

int main()
{
	srand(time(nullptr));
	int M = 12, N = 12;
	int noX = rand() % M, noY = rand() % N;
	int** board = new int* [MAX_M];
	int top[MAX_N];
	for (int i = 0; i < MAX_M; i++)
	{
		if (noY == i && noX == M - 1)
		{
			top[i] = M - 1;
		}
		else
		{
			top[i] = M;
		}
		board[i] = new int [MAX_N];
		for (int j = 0; j < MAX_N; j++)
		{
			board[i][j] = 0;
		}
	}
	int player = 1;
	for (int i = 0; i < M * N; i++)
	{
		printBoard(board, M, N, noX, noY);
		UCT uct(M, N, Point(noX, noY), player, board, top);
		Point move = uct.main();
		cout << move.x << move.y << endl;
		board[move.x][move.y] = player;
		top[move.y] -= 1;
		if (move.y == noY && (top[move.y] - 1 == noX))
		{
			top[move.y] -= 1;
		}
		player = anotherPlayer(player);
	}
	return 0;
}