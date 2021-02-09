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
void buildNext() { //����next��
    unsigned int j = 0; //��������ָ��
    int t = next[0] = -1; //ģʽ��ָ��
    while (j < strLen)  //��Ϊ�����㷨��Ҫ��next���㵽strLen
    {
        if (0 > t || string[j] == string[t]) //ƥ��
        { 
            j++; t++;
            next[j] = t;
        }
        else //ʧ��
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