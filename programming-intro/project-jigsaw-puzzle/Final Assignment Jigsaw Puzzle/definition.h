#pragma once
#pragma pack (1)
struct pixel {
	char blue;
	char green;
	char red;
};
struct piece {
	int index;//the space one's index should be -1
};
struct save {
	piece board[12000];
	char name[250];
};
struct BmpFileHeeader {
	unsigned short type;//bm
	unsigned int  SizeofFile;
	unsigned short con1;//00
	unsigned short con2;//00
	unsigned int HeaderLengnth;
};
struct BmpInfoHeader {
	unsigned int SizeeOfInfoHeader;
	unsigned int width;
	unsigned int height;
	unsigned short plane;//1
	unsigned short BitsPerPixel;
	unsigned int compression;
	unsigned int SizeofImage;
	unsigned int XResolutionRatio;
	unsigned int YResolutionRatio;
	unsigned int PaletNumber;
	unsigned int PaletImportance;
};