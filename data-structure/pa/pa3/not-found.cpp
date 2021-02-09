#define _CRT_SECURE_NO_WARNINGS
#include<cstdio>
#include<cstring>
#include<stdlib.h>
#include <memory.h>

//Bitmap from dsa cpp
typedef int Rank;

class Bitmap { //λͼBitmap��
private:
	char* M; int N; //����ͼ����ŵĿռ�M[]������ΪN*sizeof(char)*8����
protected:
	inline void init(int n) { M = new char[N = (n + 7) / 8]; memset(M, 0, N); }
public:
	inline Bitmap(int n = 8) { init(n); } //��ָ����Ĭ�Ϲ�ģ��������ͼ��Ϊ������ʱѡ�ý�С��Ĭ��ֵ��
	inline ~Bitmap() {  M = NULL; } //����ʱ�ͷű���ͼ�ռ� ����������Ҫ�������������ͷ��ڴ棬�����ͷ��ڴ�ӿ�release
	inline void release() { delete[] M; }
	inline void set(int k) { M[k >> 3] |= (0x80 >> (k & 0x07)); }
	inline void clear(int k) { M[k >> 3] &= ~(0x80 >> (k & 0x07)); }
	inline bool test(int k) { return M[k >> 3] & (0x80 >> (k & 0x07)); }
};

inline int str2int(char* t_str, int t_len)
{
	int ret = 0;
	for (int i = 0; i < t_len; i++)
	{
		int addNum = (t_str[i] == '0' ? 0 : 1);
		ret += addNum << (t_len - i - 1);
	}
	return ret;
}

inline void updateNum(int& t_num, char t_newChar)	//t_num is a 24 bit number. delete the highest bit and update the lowest bit with newchar
{
	const int cmp = 1 << 24;
	t_num <<= 1;
	if (t_num >= cmp)	//delete the highest bit
	{
		t_num -= cmp;
	}
	int addNum = (t_newChar == '0' ? 0 : 1);
	t_num += addNum;
}

inline void int2Str(char* t_str, int t_num, int t_len)
{
	t_str[t_len] = '\0';
	for (int i = 0; i < t_len; i++)
	{
		t_str[t_len - i - 1] = '0' + t_num % 2;
		t_num /= 2;
	}
}

int main()
{
	Bitmap prevbm(1 << 24);
	char inputStr[30];
	char inputChar;
	int inputLen = 0;
	int iterNum = 0;
	while (inputChar = getchar())
	{
		if (inputChar == '\n') break;
		inputLen++;
		if (inputLen > 24)
		{
			updateNum(iterNum, inputChar);
			prevbm.set(iterNum);
		}
		else
		{
			inputStr[inputLen - 1] = inputChar;
			if (inputLen == 24)
			{
				iterNum = str2int(inputStr, 24);
				prevbm.set(iterNum);
			}
		}
		char output[30];
		int2Str(output, iterNum, 24);
	}
	int iterLen = 23;
	if (inputLen < 24)
	{
		prevbm.set(str2int(inputStr, inputLen));
		iterLen = inputLen - 1;
	}
	for (; iterLen > -1; iterLen--)
	{
		Bitmap iterbm(1 << iterLen);
		const int PREV_MAX = 1 << (iterLen + 1);
		bool finished = true;
		for (int i = 0; i < PREV_MAX; i++)
		{
			if (!prevbm.test(i))
			{
				if (finished)	iterNum = i;	//record the first num not in prevbm. potential output
				finished = false;
				continue;
			}
			iterbm.set(i >> 1);
			int cmp = 1 << iterLen;
			if (i >= cmp) iterbm.set(i - cmp);
			else iterbm.set(i);
		}
		if (finished)	//prevbm is full
		{
			char output[30];
			//the length of prevbm is iterLen+1, then the length of output is iterLen+2
			int outputLen = iterLen + 2;
			int2Str(output, iterNum, outputLen);
			printf("%s\n", output);
			prevbm.release();
			iterbm.release();
			return 0;
		}
		prevbm.release();
		prevbm = iterbm;
	}
	//if the output is single digit. then it doesn't finish in loop
	char output[30];
	int2Str(output, iterNum, 1);
	printf("%s\n", output);
	prevbm.release();
	return 0;
}