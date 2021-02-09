#define _CRT_SECURE_NO_WARNINGS
#pragma pack (1)
#include<cstdio>
#include<cstring>
#include<stdlib.h>
#include"crc32.h"

const int CHAR_TYPE = 18;

int n;
char salt[10];
int saltLen;
char charList[20];	//start from 1
char weekPassword[(int)2e6];
int weekPasswordEnd = 0;	//weekPassword[weekPasswordEnd] is invalid


//hashtable from dascpp

struct Entry
{
	unsigned int key;	//crc32
	long long value = 0;	//for legal string, value>0. if duplicate, then value = -2. for empty entry, the value is 0
	inline Entry() {}
	inline Entry(unsigned int k, long long v) : key(k), value(v) {}
	inline bool valid()
	{
		return value != 0;
	}
};


class Hashtable { //符合Dictionary接口的Hashtable模板类
private:
	Entry ht[int(1e7)]; //桶数组，存放词条指针
	int M; //桶数组容量
protected:
	inline int probe4Hit(unsigned int k) //沿关键码k对应的查找链，找到词条匹配的桶
	{
		int r = k % M; //从起始桶（按除余法确定）出发
		while (ht[r].valid() && (k != ht[r].key))
			r = (r + 1) % M; //沿查找链线性试探：跳过所有冲突的桶，以及带懒惰删除标记的桶
		return r; //调用者根据ht[r]是否为空，即可判断查找是否成功
	}
	inline int probe4Free(unsigned int k, long long v) //沿关键码k对应的查找链，找到首个可用空桶
	{
		int r = k % M; //从起始桶（按除余法确定）出发
		while (ht[r].valid()) //沿查找链逐桶试探，直到首个空桶
		{
			if (k == ht[r].key)	//key之前存在
			{
				if (v != ht[r].value)	//value不同，重复情况出现，该entry失效
				{
					ht[r].value = -2;	//标重复
				}
				//否则value也相同，不要重复插入，但是数据保留
				return -1;	//提前终止，返回非法位置
			}
			r = (r + 1) % M;
		}
		return r; //为保证空桶总能找到，装填因子及散列表长需要合理设置
	}
public:
	Hashtable(int c) //创建一个容量不小于c的散列表（为测试暂时选用较小的默认值）
	{
		M = c;
		//ht = new Entry * [M]; //开辟桶数组（还需核对申请成功），初始装填因子为N/M = 0%
		memset(ht, 0, sizeof(Entry*) * M); //初始化各桶
	}
	inline void put(unsigned int k, long long v) //插入（禁止雷同词条，故可能失败）
	{
		int r = probe4Free(k, v); //为新词条找个空桶 修改：如果重复，则在probe过程中自动决定是否标注duplicate，r=-1
		if (r < 0) return;
		ht[r] = Entry(k, v); //插入
	}
	long long get(unsigned int k) //读取
	{
		int r = probe4Hit(k);
		return ht[r].valid() ? ht[r].value : -1;
	}
};
Hashtable crc32Hash((int)1e7);


const int BASE = 19;	//base of the long long
//convert string to long long, the string is stored reversed(str[0] is the lowest digit)
//long long with base 19, each digit is 1-18. the digit start from 1 to tell string like "00"(to 11) and "000"(to 111)

int char2intList[200];
inline int char2int(char t_char)
{
	return char2intList[(int)t_char];
}

inline long long str2longlong(char* t_str, int t_len)
{
	long long ret = 0;
	for (int i = 0; i < t_len; i++)
	{
		long long plus = char2int(t_str[i]);
		for (int j = 0; j < i; j++)
		{
			plus *= BASE;
		}
		ret += plus;
	}
	return ret;
}


//convert long long to string
inline char int2char(int t_int)	//use charlist
{
	return charList[t_int];
}

inline void longlong2str(char* t_dst, long long t_src)	//note that long long is reversed
{
	int strIndex = 0;
	while (t_src > 0)
	{
		t_dst[strIndex] = int2char(t_src % BASE);
		t_src /= BASE;
		strIndex++;
	}
	t_dst[strIndex] = 0;
}


//basic function

inline unsigned int crc32WithSalt(char* t_str, int t_len)
{
	return crc32(crc32(0, (unsigned char*)t_str, t_len), (unsigned char*)salt, saltLen);
}

inline void putStr2hash(char* t_str, int t_len)
{
	crc32Hash.put(crc32WithSalt(t_str, t_len), str2longlong(t_str, t_len));
}


//initialize

char iterStr[10];
inline void iniIter(int t_iterIndex, int t_iterCounter)
{
	iterStr[t_iterCounter - 1] = charList[t_iterIndex];
	iterStr[t_iterCounter] = 0;
	putStr2hash(iterStr, t_iterCounter);
}

void initialize()
{
	saltLen = strlen(salt);
	for (int i = 1; i <= 10; i++)
	{
		charList[i] = (char)('0' + i - 1);
	}
	charList[11] = 't'; charList[12] = 's'; charList[13] = 'i'; charList[14] = 'n';
	charList[15] = 'g'; charList[16] = 'h'; charList[17] = 'u'; charList[18] = 'a';
	for (int i = 1; i <= CHAR_TYPE; i++)
	{
		char2intList[(int)charList[i]] = i;
	}
	//initialize password with lenghth <= 5
	for (int i1 = 1; i1 <= CHAR_TYPE; i1++)
	{
		iniIter(i1, 1);
		for (int i2 = 1; i2 <= CHAR_TYPE; i2++)
		{
			iniIter(i2, 2);
			for (int i3 = 1; i3 <= CHAR_TYPE; i3++)
			{
				iniIter(i3, 3);
				for (int i4 = 1; i4 <= CHAR_TYPE; i4++)
				{
					iniIter(i4, 4);
					for (int i5 = 1; i5 <= CHAR_TYPE; i5++)
					{
						iniIter(i5, 5);
					}
				}
			}
		}
	}
}


int main()
{
	scanf("%d%s", &n, salt);
	initialize();
	for (int i = 0; i < n; i++)
	{
		unsigned int inputCrc32;
		scanf("%x", &inputCrc32);
		long long strll = crc32Hash.get(inputCrc32);
		if (strll == -1)	//search fail
		{
			printf("No\n");
			continue;
		}
		if (strll == -2)	//marked as duplicate before
		{
			printf("Duplicate\n");
			continue;
		}
		char output[10];
		longlong2str(output, strll);
		printf("%s\n", output);
		weekPassword[weekPasswordEnd] = output[0];
		weekPasswordEnd++;
		if (weekPasswordEnd >= 6)
		{
			putStr2hash(weekPassword + weekPasswordEnd - 6, 6);
			if (weekPasswordEnd >= 7)
			{
				putStr2hash(weekPassword + weekPasswordEnd - 7, 7);
				if (weekPasswordEnd >= 8)
				{
					putStr2hash(weekPassword + weekPasswordEnd - 8, 8);
				}
			}
		}
	}
	return 0;
}