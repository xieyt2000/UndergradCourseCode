#include"pch.h"
using namespace std;
//up down left right all from the perspective of space
int up(int space) {
	int* pos = GetPosition(space);
	if (pos[0] == 0) {
		cout << "Error, illegal operation." << endl;
		return space;
	}
	SwapPiece(&board[space], &board[(pos[0] - 1)*n + pos[1]]);
	return (pos[0] - 1)*n + pos[1];
}
int down(int space) {
	int* pos = GetPosition(space);
	if (pos[0] == m-1) {
		cout << "Error, illegal operation." << endl;
		return space;
	}
	SwapPiece(&board[space], &board[(pos[0] + 1)*n + pos[1]]);
	return (pos[0] + 1)*n + pos[1];
}
int left(int space) {
	int* pos = GetPosition(space);
	if (pos[1] == 0) {
		cout << "Error, illegal operation." << endl;
		return space;
	}
	SwapPiece(&board[space], &board[pos[0]*n + pos[1]-1]);
	return pos[0] * n + pos[1] - 1;
}
int right(int space) {
	int* pos = GetPosition(space);
	if (pos[1] == n - 1) {
		cout << "Error, illegal operation." << endl;
		return space;
	}
	SwapPiece(&board[space], &board[pos[0] *n + pos[1]+1]);
	return pos[0] * n + pos[1] + 1;
}
void MoveFromToWithoutPrinting(int space, int to) {
	int* spacepos, *topos;
	spacepos = GetPosition(space);
	topos = GetPosition(to);
	if (spacepos[0] > topos[0]) {
		for (int i = topos[0];i < spacepos[0];i++) space=up(space);
	}
	if (spacepos[0] < topos[0]) {
		for (int i = spacepos[0];i < topos[0];i++) space=down(space);
	}
	if (spacepos[1] < topos[1]) {
		for (int i = spacepos[1];i < topos[1];i++) space = right(space);
	}
	if (spacepos[1] > topos[1]) {
		for (int i = topos[1];i < spacepos[1];i++) space = left(space);
	}
}
void MoveFromToWithPrinting(int space, int to) {
	int* spacepos, *topos;
	spacepos = GetPosition(space);
	topos = GetPosition(to);
	if (spacepos[0] > topos[0]) {
		for (int i = topos[0];i < spacepos[0];i++) {
			space = up(space);
			cout << "W ";
		}
	}
	if (spacepos[0] < topos[0]) {
		for (int i = spacepos[0];i < topos[0];i++) {
			space = down(space);
			cout << "S ";
		}
	}
	if (spacepos[1] < topos[1]) {
		for (int i = spacepos[1];i < topos[1];i++) {
			space = right(space);
			cout << "D ";
		}
	}
	if (spacepos[1] > topos[1]) {
		for (int i = topos[1];i < spacepos[1];i++) {
			space = left(space);
			cout << "A ";
		}
	}
}
int TargetUp(int space) {//space just above target and after moving space still just above target
	int* pos = GetPosition(space);
	space = down(space);
	cout << "S ";
	if (pos[1] != n - 1) {
		space = right(space); space = up(space);space = up(space);space = left(space);
		cout << "D W W A ";
	}
	else {
		space = left(space); space = up(space);space = up(space);space = right(space);
		cout << "L W W R ";
	}
	return space;
}
int TargetRight(int space) {
	int* pos = GetPosition(space);
	space = left(space);
	cout << "A ";
	if (pos[0] != m - 1) {
		space = down(space); space = right(space);space = right(space);space = up(space);
		cout << "S D D W ";
	}
	else {
		space = up(space); space = right(space);space = right(space);space = down(space);
		cout << "W D D S ";
	}
	return space;
}
int TargetLeft(int space) {
	int* pos = GetPosition(space);
	space = right(space);
	cout << "D ";
	if (pos[0] != m - 1) {
		space = down(space); space = left(space);space = left(space);space = up(space);
		cout << "S A A W ";
	}
	else {
		space = up(space); space = left(space);space = left(space);space = down(space);
		cout<<"W A A S ";
	}
	return space;
}
int TargetDown(int space) {
	int* pos = GetPosition(space);
	space = up(space);
	cout << "W ";
	if (pos[1] != n - 1) {
		space = right(space); space = down(space);space = down(space);space = left(space);
		cout << "D S S A ";
	}
	else {
		space = left(space); space = down(space);space = down(space);space = right(space);
		cout << "A S S D ";
	}
	return space;
}