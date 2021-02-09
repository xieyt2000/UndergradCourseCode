#pragma once
#include"definition.h"
extern piece board[12000];
extern piece oriboard[12000];
extern save saving[100];
extern int m;
extern int n;
extern int UpperBound;
extern int SaveIndex;
extern BmpFileHeeader file;
extern BmpInfoHeader info;
extern int PicWidth;
extern int PicHeight;
extern int Biecount;
extern int BytePerLine;
extern int  PixelXperPiece;
extern int PixelYperPixel;
extern const int ByteperPixel;
extern const int BitPerPixel;
extern unsigned char* oribuffer;
extern unsigned char* buffer;