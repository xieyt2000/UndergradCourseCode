// Final Assignment Jigsaw Puzzle.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"

using namespace std;
int m, n;//row 0 to m-1  column 0 to n-1   at least 3 times 3
int UpperBound;//empty piece included, start from 0
piece board[12000];//start from 0. row i column j(both start from 0) located at board[i*n+j]
piece oriboard[12000];//the random board generated
save saving[100];
int SaveIndex = 0;
BmpFileHeeader file;
BmpInfoHeader info;
int PicWidth, PicHeight, Biecount, BytePerLine;
int PixelXperPiece, PixelYperPixel;
const int BitPerPixel = 24;
const int ByteperPixel = 3;
unsigned char* oribuffer;
unsigned char* buffer;
int main() {
	for (int i = 0;i <= 10000;i++) board[i].index = i-1;
	board[0].index = -1;
	cout << "Please enter the nubers of rows and lines you want. The two figures should be divided by space." << endl;
	cin >> m >> n;//start from 1 while other start from 0
	UpperBound = m * n - 1;
	ReadBmp();
	CutCornerPiece();
	//WriteBmp();
	int SpacePos = GenerateRandomBoard();
	PrintBoard();
	bool fea = JudgeFeasibility(SpacePos);
	if (fea) cout << "This one can be recoverd. Go ahead!" << endl;
	if (!fea) cout << "This one can't be recoverd. Enter B to generate another, or you can go ahead XD. You can also Enter F to see why it can't be recoverd." << endl;
	char input;
	while (true) {
		cin >> input;
		if (input == 'P') return 0;
		if (input == 'B') {
			SpacePos = GenerateRandomBoard();
			PrintBoard();
			bool fea = JudgeFeasibility(SpacePos);
			if (fea) cout << "This one can be recoverd. Go ahead!" << endl;
			if (!fea) cout << "This one can't be recoverd. Enter B to generate another, or you can go ahead XD. You can also Enter F to see why it can't be recoverd." << endl;
		}
		if (input == 'W' || input == 'A' || input == 'S' || input == 'D') {
			if (input == 'W') SpacePos = up(SpacePos);
			if (input == 'A') SpacePos = left(SpacePos);
			if (input == 'D') SpacePos = right(SpacePos);
			if (input == 'S') SpacePos = down(SpacePos);
			PrintBoard();
			if (JudgeRecover()) cout << "Mission Complete! Enter B to play another or enter P to exit game. You can still move this orderd board of course." << endl;
		}
		if (input == 'R') {
			SpacePos = ReplaceBoard(oriboard);
			PrintBoard();
		}
		if (input == 'I') {
			cout << "Enter the name of this saving." << endl;
			char a[250];
			cin >> a;		
			SaveBoard(a, SpacePos);
			cout << "Saving successful!" << endl;
		}
		if (input == 'O') {
			cout << "Enter the name of the saving you want to load." << endl;
			char a[250];
			cin >> a;
			int b = LoadBoard(a);
			if (b!=-1) { 
				PrintBoard();
				cout << "Loading successful!" << endl;
				SpacePos = b;
			}
			else cout << "Error, can't find saving named above." << endl;
		}
		if (input == 'F') {
			cout << endl;
			AutomaticaRecover(SpacePos);
			cout << endl;
			PrintBoard();
			SpacePos = m * n - 1;
			if (board[m*n - 2].index != m * n - 2) cout << "The recover can be completed if you swap the piece at row m column n-1 with the one at row m-1 column n. However, we can't swap a pair without changing the postion of the others." << endl;
		}
		if (input == 'G') {
			BoardToPicture();
			WriteBmp();
			cout << "Output successful!" << endl;
		}
	}
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
