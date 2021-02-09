#include"pch.h"
using namespace std;
void AutomaticaRecover(int space) {
	//recover row 0 to m-3
	int up1 = (m - 3)*n + n - 1;
	for (int i = 0;i <= up1;i++) {
		if (board[i].index == i) continue;
		int* SpaceTwoDPos = GetPosition(space);
		int FromOneDPos;
		for (int j = i;j <= UpperBound;j++) {
			if (board[j].index == i) FromOneDPos = j;
		}
		int* FromTwoDPos = GetPosition(FromOneDPos);
		int ToOneDPos = i;
		int* ToTwoDPos = GetPosition(i);
		//recover column 0 to n-2
		if (ToTwoDPos[1] != n - 1) {//the from postion might be at n-1 column
			if (SpaceTwoDPos[0] == FromTwoDPos[0]) {//to make space and from not at the same row
				if (SpaceTwoDPos[0] == m - 1) {
					space = up(space);
					cout << "W ";
				}
				else {
					space = down(space);
					cout << "S ";
				}
			}
			SpaceTwoDPos = GetPosition(space);
			if (FromTwoDPos[1] != ToTwoDPos[1]) {//to make from and to at the same column
				if (FromTwoDPos[1] < ToTwoDPos[1]) {//from[1]<n-2&from cant be at the to row
					if (SpaceTwoDPos[0] == ToTwoDPos[0]) {//remove space from row To
						space = down(space); cout << "S ";
						if (SpaceTwoDPos[1] == FromTwoDPos[1] && SpaceTwoDPos[0] == FromTwoDPos[0] - 1) FromTwoDPos[0]--;
						if (SpaceTwoDPos[0] + 1 == FromTwoDPos[0]) {
							space = down(space); cout << "S ";
						}
					}
					FromOneDPos = FromTwoDPos[0] * n + FromTwoDPos[1];
					SpaceTwoDPos = GetPosition(space);
					MoveFromToWithPrinting(space, n*SpaceTwoDPos[0] + FromTwoDPos[1] + 1);
					space = n * SpaceTwoDPos[0] + FromTwoDPos[1] + 1;
					MoveFromToWithPrinting(space, FromOneDPos + 1);
					space = FromOneDPos + 1;
					while (FromTwoDPos[1] < ToTwoDPos[1]) {
						space = TargetRight(space);
						FromTwoDPos[1]++;
					}
					space = up(space);space = left(space);
					cout << "W A ";
				}
				if (FromTwoDPos[1] > ToTwoDPos[1]) {//from[1]>0&from[1]>already arranged column+1
					if (SpaceTwoDPos[0] == ToTwoDPos[0]) {//remove space from row To
						space = down(space); cout << "S ";
						if (SpaceTwoDPos[1] == FromTwoDPos[1] && SpaceTwoDPos[0] == FromTwoDPos[0] - 1) FromTwoDPos[0]--;
						if (SpaceTwoDPos[0] + 1 == FromTwoDPos[0]) {
							space = down(space); cout << "S ";
						}
					}
					FromOneDPos = FromTwoDPos[0] * n + FromTwoDPos[1];
					SpaceTwoDPos = GetPosition(space);
					MoveFromToWithPrinting(space, n*SpaceTwoDPos[0] + FromTwoDPos[1] - 1);
					space = n * SpaceTwoDPos[0] + FromTwoDPos[1] - 1;
					MoveFromToWithPrinting(space, FromOneDPos - 1);
					space = FromOneDPos - 1;
					while (FromTwoDPos[1] > ToTwoDPos[1]+1) {
						space = TargetLeft(space);
						FromTwoDPos[1]--;
					}
					space = right(space); cout << "D ";
					if (FromTwoDPos[0] == ToTwoDPos[0]) continue;
					space = up(space);space = left(space);
					cout << "W A ";
				}
			}
			else {
				MoveFromToWithPrinting(space, n*SpaceTwoDPos[0] + n - 1);
				space = n * SpaceTwoDPos[0] + n - 1;
				MoveFromToWithPrinting(space, n*(FromTwoDPos[0]-1) + FromTwoDPos[1]);
				space = n * (FromTwoDPos[0] - 1) + FromTwoDPos[1];
			}
			//space just above from
			while (FromTwoDPos[0]!=ToTwoDPos[0] + 1) {
				space = TargetUp(space);
				FromTwoDPos[0]--;
			}
			space = down(space); cout << "S ";
		}
		//recover column n-1. from cant be at row to
		if (ToTwoDPos[1] == n - 1) {
			if (SpaceTwoDPos[0] == ToTwoDPos[0]) {//make space not at row to     if from recover , continue
				space = down(space); cout << "S ";
				if (FromTwoDPos[0] == ToTwoDPos[0] + 1 && FromTwoDPos[1] == n - 1) continue;
				SpaceTwoDPos = GetPosition(space);
			}
			if (SpaceTwoDPos[0] == FromTwoDPos[0]) {//to make space and from not at the same row
				if (SpaceTwoDPos[0] == m - 1) {
					space = up(space);
					cout << "W ";
				}
				else {
					space = down(space);
					cout << "S ";
				}
				SpaceTwoDPos = GetPosition(space);
			}			
			//move from to row to+2, column n-1 
			//move from to column n-1
			if (FromTwoDPos[1] != n - 1) {//below row n-1
				MoveFromToWithPrinting(space, n * SpaceTwoDPos[0] + FromTwoDPos[1] + 1);
				space = n * SpaceTwoDPos[0] + FromTwoDPos[1] + 1;
				MoveFromToWithPrinting(space, FromOneDPos + 1);
				space = FromOneDPos + 1;
				while (FromTwoDPos[1] < n - 2) {
					space = TargetRight(space);
					FromTwoDPos[1]++;
				}
				space = left(space); cout << "A ";
			}
			else {
				MoveFromToWithPrinting(space, n*SpaceTwoDPos[0] + n - 2);
				space = n * SpaceTwoDPos[0] + n - 2;
				MoveFromToWithPrinting(space, FromOneDPos - 1);
				space = FromOneDPos - 1;
			}
			//move from to row  to+2 and finally space just above From
			if (FromTwoDPos[0] > ToTwoDPos[0] + 1) {//already at row to+2 included
				space = up(space);space = right(space);
				cout << "W D ";
				while (FromTwoDPos[0] > ToTwoDPos[0] + 2) {
					space = TargetUp(space);
					FromTwoDPos[0]--;
				}
			}
			if(FromTwoDPos[0] == ToTwoDPos[0] + 1) {
				space = down(space);space = right(space);space = up(space);
				cout << "S D W ";
			}
			space = up(space);space = left(space);space = down(space);space = right(space);space = down(space);
			cout << "W A S D S ";
			space = left(space);space = up(space);space = right(space);space = up(space);space = left(space);space = down(space);space = right(space);space = up(space);space = left(space);space = down(space);
			cout << "A W D W A S D W A S ";
		}
		//cout << endl;
		//PrintBoard();
	}
	//cout << endl;
	//PrintBoard();
	//recover row m-2 and m-1 column by column(i)
	//recovr column 0 to n-3
	for (int i = 0;i < n - 2;i++) {
		int* SpaceTwoDPos = GetPosition(space);
		int To1OneDPos = (m - 2)*n + i;//row m-2
		int To2OneDpos = (m - 1)*n + i;//row m-1
		int From2OneDpos;
		for (int j = To1OneDPos; j <= UpperBound;j++) {
			if (board[j].index == To2OneDpos) {
				From2OneDpos = j;
				break;
			}
		}
		//From2 to To1(prepare for next)
		if (From2OneDpos != To1OneDPos) {
			int* To1TwoDpos = GetPosition(To1OneDPos);
			int *From2TwoDpos = GetPosition(From2OneDpos);
			//move to the column i
			if (From2TwoDpos[1] != i) {
				if (SpaceTwoDPos[0] == From2TwoDpos[0]) {//make space, from not at same row
					if (SpaceTwoDPos[0] == m - 1) {
						space = up(space); cout << "W ";
					}
					else {
						space = down(space);cout << "S ";
					}
				}
				SpaceTwoDPos = GetPosition(space);
				MoveFromToWithPrinting(space, From2TwoDpos[1] + n * SpaceTwoDPos[0] - 1);
				space = From2TwoDpos[1] + n * SpaceTwoDPos[0] - 1;
				MoveFromToWithPrinting(space, From2OneDpos - 1);
				space = From2OneDpos - 1;
				while (From2TwoDpos[1] > i + 1) {
					space = TargetLeft(space);
					From2TwoDpos[1]--;
				}
				space = right(space); cout << "D ";
				//move to row n-2
				if (From2TwoDpos[0] != m - 2) {
					space = up(space);space = left(space);space = down(space);
					cout << "W A S ";
				}
			}
			else {
				MoveFromToWithPrinting(space, To1OneDPos);
				space = To1OneDPos;
				space = down(space);
				cout << "S ";
			}
		}
		//space at To2+1
		MoveFromToWithPrinting(space, To2OneDpos + 1);
		space = To2OneDpos + 1;		
		//From1 to To1+1(prepare for final)
		int From1OneDpos;
		//cout << endl;
		//PrintBoard();
		for (int j = To1OneDPos; j <= UpperBound;j++) {
			if (board[j].index == To1OneDPos) {
				From1OneDpos = j;
				break;
			}
		}
		if (From1OneDpos != To1OneDPos +1) {
			int* From1TwoDPos = GetPosition(From1OneDpos);
			//special case from1 at to2 
			if (From1OneDpos == To2OneDpos ) {
				space = left(space);space = up(space);space = right(space);space = down(space);
				cout << "A W D S ";
				space = right(space);space = up(space);space = left(space);space = left(space);space = down(space);space = right(space);space = up(space);space = right(space);
				cout << "D W A A S D W D ";
			}
			//common case
			else {
				MoveFromToWithPrinting(space, From1OneDpos - 1);
				space = From1OneDpos - 1;
				//column
				while (From1TwoDPos[1] > i + 2) {
					space = TargetLeft(space);
					From1TwoDPos[1]--;
				}
				space = right(space); cout << "D ";
				//row
				if (From1TwoDPos[0] != m - 2) {
					space = up(space);space = left(space);space = down(space);
					cout << "W A S ";
				}
			}
		}
		//cout << endl;
		//PrintBoard();
		//space at To2
		MoveFromToWithPrinting(space, To2OneDpos);
		space = To2OneDpos;
		space = up(space);space = right(space);
		cout << "W D ";
		//cout << endl;
		//PrintBoard();
	}
	//cout << endl;
	//PrintBoard();
	//the last four
	int To1D = (m - 2) * n + n - 2;
	int From1D;
	for (int i = To1D;i <= UpperBound;i++) {
		if (board[i].index == To1D) From1D = i;
	}
	int* Space2D = GetPosition(space);
	//move from
	if (From1D != To1D) {
		int *From2D = GetPosition(From1D);
		if (From2D[0] == m - 1 && From2D[1] == n - 1) {
			MoveFromToWithPrinting(space, (m - 2)*n + n - 1);
			space = (m - 2)*n + n - 1;
			space = down(space); cout << "S ";
			space = left(space);space = up(space);space = right(space);
			cout << "A W D ";
		}
		if (From2D[0] == m - 2 && From2D[1] == n - 1) {
			MoveFromToWithPrinting(space, m*n - 2);
			space = m * n - 2;
			space = up(space); cout << "W ";
			space = right(space); cout << "D ";
		}
		if (From2D[0] == m - 1 && From2D[1] == n - 2) {
			MoveFromToWithPrinting(space, (m - 2)*n + n - 1);
			space = (m - 2)*n + n - 1;
			space = left(space); space = down(space);
			cout << "A S ";
		}
	}
	MoveFromToWithPrinting(space, UpperBound);
	space = UpperBound;
	cout << endl;
}