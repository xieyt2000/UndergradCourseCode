#include"pch.h"
#include<cstring>
using namespace std;
void SwapPiece(piece* a, piece* b) {
	piece t = *a;
	*a = *b;
	*b = t;
}
int* GetPosition(int No){//row a[0] column a[1]
	int *a = new int[5];
	a[0] = No / n;
	a[1] = No % n;
	return a;
}
void SaveBoard(char a[], int space) {
	for (int i = 0;i <= UpperBound;i++) saving[SaveIndex].board[i] = board[i];
	strcpy(saving[SaveIndex].name, a);
	SaveIndex++;
}
int LoadBoard(char a[]) {
	for (int i = 0;i <= SaveIndex;i++) {
		if (strcmp(saving[i].name, a) == 0) return (ReplaceBoard(saving[i].board));		
	}
	return -1;
}
void UnsignegcharStrcpy(unsigned char* dest, unsigned char* source, int ArrayLength) {
	for (int i = 0;i < ArrayLength;i++) dest[i] = source[i];
}