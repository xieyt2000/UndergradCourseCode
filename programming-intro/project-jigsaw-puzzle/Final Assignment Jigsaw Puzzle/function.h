#pragma once
int up(int space);
int down(int space);
int left(int space);
int right(int space);
int GenerateRandomBoard();
void SwapPiece(piece* a, piece* b);
bool JudgeFeasibility(int space);
void PrintBoard();
bool JudgeRecover();
int* GetPosition(int No);
int ReplaceBoard(piece a[]);
void SaveBoard(char a[], int space);
int LoadBoard(char a[]);
void AutomaticaRecover(int space);
void MoveFromToWithoutPrinting(int space, int to);
void MoveFromToWithPrinting(int space, int to);
int TargetUp(int space);
int TargetDown(int space);
int TargetRight(int space);
int TargetLeft(int space);
void ReadBmp();
void CutCornerPiece();
void WriteBmp();
void UnsignegcharStrcpy(unsigned char* dest, unsigned char* source, int ArrayLength);
void BoardToPicture();