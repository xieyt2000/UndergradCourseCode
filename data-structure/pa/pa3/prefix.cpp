#define _CRT_SECURE_NO_WARNINGS
#include<cstdio>
#include<cstring>
#include<stdlib.h>

const int MAX_LEN = 2e7 + 100;

char string[MAX_LEN];
int strLen;
int next[MAX_LEN];  //kmp next
int nextCount[MAX_LEN]; //nextCount[i] means how many prefixes appear in suffix of string[0,i). nextCount[0] is 0

//build next from dsacpp
void buildNext() { //构造next表
    unsigned int j = 0; //“主”串指针
    int t = next[0] = -1; //模式串指针
    while (j < strLen)  //因为本题算法需要，next表算到strLen
    {
        if (0 > t || string[j] == string[t]) //匹配
        { 
            j++; t++;
            next[j] = t;
        }
        else //失配
            t = next[t];
    }
}

//simple dp to build nextcount
void buildNextCount()
{
    nextCount[0] = 0;
    for (int i = 1; i <= strLen; i++)
    {
        nextCount[i] = nextCount[next[i]] + 1;
    }
}

int main()
{
	scanf("%s", string);
	strLen = strlen(string);
    buildNext();
    buildNextCount();
    unsigned long long result = 0;
    //for this algorithm, plz refer to the report
    for (int i = 1; i <= strLen; i++)
    {
        result += nextCount[i];
    }
    printf("%llu\n", result);
	return 0;
}