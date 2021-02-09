#include"pch.h"
#include<cstdlib>
#include<ctime>
#include<cmath>
using namespace std;
void ReadBmp() {
	char FilePath[250];
	cout << "Enter the path of the picture." << endl;
	cin >> FilePath;
	FILE* bmp;
	bmp = fopen(FilePath, "rb");;
	while(bmp==0) {
		cout << "Input failed. Retry Please." << endl;
		cin >> FilePath;
		bmp = fopen(FilePath, "rb");
	}	
	cout << "Input succeeded!" << endl;
	fread(&file, 1, sizeof(BmpFileHeeader), bmp);
	fread(&info, 1, sizeof(BmpInfoHeader), bmp);
	//cout << sizeof(BmpFileHeeader) << endl << sizeof(BmpInfoHeader) << endl;
	PicWidth = info.width;
	PicHeight = info.height;
	PixelXperPiece = PicWidth / n;
	PixelYperPixel = PicHeight / m;
	BytePerLine = (ByteperPixel*PicWidth + 3) / 4 * 4; //auto completement formula
	oribuffer = new unsigned char[2 * BytePerLine*PicHeight];
	fread(oribuffer, 1, BytePerLine*PicHeight, bmp);
	//cout << oribuffer;	
	fclose(bmp);
}
void CutCornerPiece() {//the data of the bottom right corner located at top right corner
	for (int i = 0;i < PixelYperPixel;i++) {
		for (int j = 0;j < PixelXperPiece*ByteperPixel;j++)
			oribuffer[(n - 1)*PixelXperPiece*ByteperPixel + j + i * BytePerLine] = 255;
		}
	buffer = new unsigned char[2 * BytePerLine*PicHeight];
	UnsignegcharStrcpy(buffer, oribuffer, 2 * BytePerLine*PicHeight);
}
void BoardToPicture() {//from bottom left to top right row first
	for (int k = 0;k < m;k++) {//row k we see row m-1-k stored
		for (int l = 0;l < n;l++) {//column l we see and stored
			int Out1DPos = board[n*k + l].index;
			if (Out1DPos == -1) {
				for (int i = 0;i < PixelYperPixel;i++) {
					for (int j = 0;j < PixelXperPiece*ByteperPixel;j++)
						buffer[(m-1-k) * BytePerLine *PixelYperPixel + l * PixelXperPiece * ByteperPixel + j + i * BytePerLine] = 255;
				}
				continue;
			}
			int* Out2Dpos = GetPosition(Out1DPos);
			for (int i = 0;i < PixelYperPixel;i++) {//put to row m-1-k column  l
				for (int j = 0;j < PixelXperPiece*ByteperPixel;j++)
					buffer[(m - 1 - k) * BytePerLine *PixelYperPixel + l * PixelXperPiece * ByteperPixel + j + i * BytePerLine] =
					oribuffer[(m - 1 - Out2Dpos[0]) * BytePerLine *PixelYperPixel + Out2Dpos[1] * PixelXperPiece * ByteperPixel + j + i * BytePerLine];
			}
		}
	}
}
void WriteBmp() {
	cout << "Enter the path." << endl;
	char path[250];
	cin >> path;
	FILE* bmp;
	bmp = fopen(path, "wb");
	fwrite(&file, 1, sizeof(BmpFileHeeader), bmp);
	fwrite(&info, 1, sizeof(BmpInfoHeader), bmp);
	fwrite(buffer, PicHeight*BytePerLine, 1, bmp);
	fclose(bmp);
}
