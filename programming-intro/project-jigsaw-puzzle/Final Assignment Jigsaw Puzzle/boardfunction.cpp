#include"pch.h"
#include <stdlib.h>
#include <time.h>
using namespace std;
int GenerateRandomBoard() {//array from 0 to max
	int ran;
	srand(time(0));
	for (int i = 0; i <= UpperBound; i++){
		ran = rand() % UpperBound;
		if (ran != i) SwapPiece(&board[i], &board[ran]);
	}
	for (int i = 0;i <= UpperBound;i++) oriboard[i] = board[i];	
	for (int i = 0;i <= UpperBound;i++) {
		if (board[i].index == -1) return i;
	}
}
bool JudgeFeasibility(int space) {
	MoveFromToWithoutPrinting(space, m*n - 1);
	int InverseNumber = 0;
	for (int i = 0;i < UpperBound;i++) {
		for (int j = i + 1;j < UpperBound;j++) {
			if (board[i].index > board[j].index) InverseNumber++;
		}
	}
	int a = ReplaceBoard(oriboard);
	if (InverseNumber % 2 == 0) return true;
	else return false;
}
void PrintBoard() {
	for (int i = 0;i < m;i++) {
		for (int j = 0;j < n;j++) cout << board[i*n + j].index << '\t';
		cout << endl;
	}
}
bool JudgeRecover() {
	for (int i = 0;i < UpperBound;i++) {
		if (board[i].index != i) return false;
	}
	return true;
}
int ReplaceBoard(piece a[]) {//replace board with a
	int ret = -1;
	for (int i = 0;i <= UpperBound;i++) {
		board[i] = a[i];
		if (board[i].index == -1) ret = i;
	}	
	return ret;
}
