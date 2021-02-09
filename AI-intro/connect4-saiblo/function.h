#pragma once
#include "Array.h"
#include "Point.h"
#include <algorithm>

inline int max(int a, int b, int c)
{
    return std::max(a, std::max(b, c));
}

inline int anotherPlayer(int p)	//no exception check
{
	if (p == 1)
	{
		return 2;
	}
	return 1;
}

//return result score (1, 0, -1) of the player with winner
inline int winnerToResult(int player, int winner)
{
	if (winner == 0)
	{
		return 0;
	}
	if (player == winner)
	{
		return 1;
	}
	return -1;
}

inline void getAvaiMoveFromTop(const int top[], int N, Array<Point>& avaiMoves)
{
	avaiMoves.clear();
	for (int i = 0; i < N; i++)
	{
		if (top[i] > 0)
		{
			avaiMoves.push(Point(top[i] - 1, i));
		}
	}
}

inline int aCount2Score(int count) //convert a consecutive line to score
{
    switch (count)
    {
    case 0:
        return 0;
    case 1:
        return 1;
    case 2:
        return 4;
    default:
        return 10;
    }
}

inline int allCounts2Score(int count, int sCount, int bCount)
{
    if (count >= 4) //win
    {
        return BIG_INT;
    }
    return aCount2Score(max(count, sCount, bCount));
}

//get score a move. Code structure form judgeWin function in Judge.cpp. Refer to report for detailed info
inline int getMoveScore(const int x, const int y, const int M, const int N, int board[][MAX_N], int player)
{
    //横向检测
    int i, j;
    int score = 0;
    bool breakBy0 = false;
    int count = 1, sCount = 1, bCount = 1;
    for (i = y - 1; i >= 0; i--)
        if (board[x][i] != player)
        {
            if (board[x][i] == 0)
                breakBy0 = true;
            break;
        }
    count += (y - i - 1);
    bCount += (y - i - 1);
    sCount += (y - i - 1);
    if (breakBy0)
    {
        for (i = i - 1; i >= 0; i--)
            if (board[x][i] != player)
            {
                break;
            }
        sCount += (y - i - 2);
    }
    breakBy0 = false;
    for (i = y + 1; i < N; i++)
        if (board[x][i] != player)
        {
            if (board[x][i] == 0)
                breakBy0 = true;
            break;
        }
    count += (i - y - 1);
    sCount += (i - y - 1);
    bCount += (i - y - 1);
    if (breakBy0)
    {
        for (i = i + 1; i < N; ++i)
            if (board[x][i] != player)
            {
                break;
            }
        bCount += (i - y - 2);
    }
    score += allCounts2Score(count, sCount, bCount);

    //纵向检测
    count = 1;
    for (i = x + 1; i < M; i++)
        if (board[i][y] != player)
            break;
    count += (i - x - 1);
    score += allCounts2Score(count, count, 0);

    //左下-右上
    count = 1, sCount = 1, bCount = 1;
    breakBy0 = false;
    for (i = x + 1, j = y - 1; i < M && j >= 0; i++, j--)
        if (board[i][j] != player)
        {
            if (board[i][j] == 0)
                breakBy0 = true;
            break;
        }
    count += (y - j - 1);
    bCount += (y - j - 1);
    sCount += (y - j - 1);
    if (breakBy0)
    {
        for (i = i + 1, j = j - 1; i < M && j >= 0; i++, j--)
        {
            if (board[i][j] != player)
                break;
        }
        sCount += (y - j - 2);
    }
    breakBy0 = false;
    for (i = x - 1, j = y + 1; i >= 0 && j < N; i--, j++)
        if (board[i][j] != player)
        {
            if (board[i][j] == 0)
                breakBy0 = true;
            break;
        }
    count += (j - y - 1);
    sCount += (j - y - 1);
    bCount += (j - y - 1);
    if (breakBy0)
    {
        for (i = i - 1, j = j + 1; i >= 0 && j < N; i--, j++)
        {
            if (board[i][j] != player)
                break;
        }
        bCount += (j - y - 2);
    }
    score += allCounts2Score(count, sCount, bCount);

    //左上-右下
    count = 1, sCount = 1, bCount = 1;
    breakBy0 = false;
    for (i = x - 1, j = y - 1; i >= 0 && j >= 0; i--, j--)
        if (board[i][j] != player)
        {
            if (board[i][j] == 0)
                breakBy0 = true;
            break;
        }
    count += (y - j - 1);
    bCount += (y - j - 1);
    sCount += (y - j - 1);
    if (breakBy0)
    {
        for (i = i - 1, j = j - 1; i >= 0 && j >= 0; i--, j--)
        {
            if (board[i][j] != player)
                break;
        }
        sCount += (y - j - 2);
    }
    breakBy0 = false;
    for (i = x + 1, j = y + 1; i < M && j < N; i++, j++)
        if (board[i][j] != player)
        {
            if (board[i][j] == 0)
                breakBy0 = true;
            break;
        }
    count += (j - y - 1);
    sCount += (j - y - 1);
    bCount += (j - y - 1);
    if (breakBy0)
    {
        for (i = i + 1, j = j + 1; i < M && j < N; i++, j++)
        {
            if (board[i][j] != player)
                break;
        }
        bCount += (j - y - 2);
    }
    score += allCounts2Score(count, sCount, bCount);

    return score;
}