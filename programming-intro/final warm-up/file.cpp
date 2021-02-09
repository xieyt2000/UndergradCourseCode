// ConsoleApplication1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include<iostream>
#include<cstring>
#include<cmath>
using namespace std;
struct file {
	char name[100];
	int type;
	char info[100];
	int pointer;
};
int main() {
	char order[100], filename[100], fileinfo[100];
	int filetype;
	file Files[2000];
	for (int i = 0;i < 2000;i++) Files[i] = { {0},-1,{0},-1 };
	int FilesIndi = 0;//files[indi] is empty
	do{
		cin >> order;
		if (order[0] == 'c') {
			cin >> filename >> filetype >> fileinfo;
			int rename = -1;
			for (int i = 0;i < FilesIndi;i++) {
				if (strcmp(Files[i].name, filename)==0) {
					rename=i;
					break;
				}
			}
			int CurFilesIndi = rename;
			if (rename == -1)  CurFilesIndi = FilesIndi;
			strcpy(Files[CurFilesIndi].name, filename);
			Files[CurFilesIndi].type = filetype;
			strcpy(Files[CurFilesIndi].info, fileinfo);
			if (filetype != 0) {
				for (int i = 0;i < FilesIndi;i++) {
					if (strcmp(Files[i].name, fileinfo) == 0) {
						Files[CurFilesIndi].pointer = i;
						break;
					}
				}
			}
			if(rename==-1) FilesIndi++;
		}
		if (order[0] == 'o') {
			cin >> filename;
			file newfile = { {0},-1,{0},-1 };
			int target;
			for (int i = 0;i < FilesIndi;i++) {
				if (strcmp(Files[i].name, filename) == 0) {
					target = i;
					newfile = Files[i];
					break;
				}
			}
			while (newfile.type == 1) {
				newfile = Files[newfile.pointer];
			}
			cout << newfile.info << endl;
		}
	} while (order[0]!='e');
	return 0;
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

