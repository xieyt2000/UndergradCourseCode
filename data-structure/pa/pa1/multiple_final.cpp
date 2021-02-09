#define _CRT_SECURE_NO_WARNINGS
#include<cstdio>
#include<cstring>

//digits are reversed
//1e8 per digit

const int MAX_DIGIT = 2000;
const int NUM_PER_DIGIT = 8;
const int MAX_VALUE_PER_DIGIT = 99999999;
const unsigned long long MAX_UNSIGNED_LONG_LONG = 10000000000000000000;

char input1Str[5010], input2Str[5010];
unsigned long long input1[MAX_DIGIT], input2[MAX_DIGIT], output[MAX_DIGIT];
int input1Len, input2Len, outputLen;

void getNum()	//??????????
{
	for (int i = 0; i < MAX_DIGIT; i++)
	{
		input1[i] = 0;
		input2[i] = 0;
	}
	int input1StrLen = strlen(input1Str);
	int input2StrLen = strlen(input2Str);
	input1Len = (input1StrLen - 1) / NUM_PER_DIGIT + 1;
	input2Len = (input2StrLen - 1) / NUM_PER_DIGIT + 1;
	bool input1Finished = false;
	for (int i = 0; i < input1Len; i++)
	{
		for (int j = 0; j < NUM_PER_DIGIT; j++)
		{
			int strIndex = input1StrLen - 1 - i * NUM_PER_DIGIT - j;
			if (strIndex < 0)
			{
				input1Finished = true;
				break;
			}
			int plus = input1Str[strIndex] - '0';
			for (int k = 0; k < j; k++)
			{
				plus *= 10;
			}
			input1[i] += plus;
		}
		if (input1Finished) break;
	}
	bool input2Finished = false;
	for (int i = 0; i < input2Len; i++)
	{
		for (int j = 0; j < NUM_PER_DIGIT; j++)
		{
			int strIndex = input2StrLen - 1 - i * NUM_PER_DIGIT - j;
			if (strIndex < 0)
			{
				input2Finished = true;
				break;
			}
			int plus = input2Str[strIndex] - '0';
			for (int k = 0; k < j; k++)
			{
				plus *= 10;
			}
			input2[i] += plus;
		}
		if (input2Finished) break;
	}
}

void multiply()
{
	for (int i = 0; i < MAX_DIGIT; i++)
	{
		output[i] = 0;
	}
	for (int i = 0; i < input1Len; i++)
	{
		for (int j = 0; j < input2Len; j++)
		{
			output[i + j] += input1[i] * input2[j];
			if (output[i + j] > MAX_UNSIGNED_LONG_LONG)
			{
				output[i + j + 1] += output[i + j] / (MAX_VALUE_PER_DIGIT + 1);
				output[i + j] %= MAX_VALUE_PER_DIGIT + 1;
			}
		}
	}
	for (int i = 0; i < MAX_DIGIT; i++)
	{
		if (output[i] > MAX_VALUE_PER_DIGIT)
		{
			output[i + 1] += output[i] / (MAX_VALUE_PER_DIGIT + 1);
			output[i] %= MAX_VALUE_PER_DIGIT + 1;
		}
	}
}

void printResult()
{
	int outputLen;
	for (int i = 0; i < MAX_DIGIT; i++)
	{
		if (output[i] != 0)
		{
			outputLen = i;
		}
	}
	printf("%llu", output[outputLen]);
	for (int i = outputLen - 1; i >= 0; i--)
	{
		char oneDigitOutputStr[10];
		oneDigitOutputStr[8] = '\0';
		for (int j = 0; j < NUM_PER_DIGIT; j++)
		{
			oneDigitOutputStr[7 - j] = '0' + output[i] % 10;
			output[i] /= 10;
		}
		printf("%s", oneDigitOutputStr);
	}
	printf("\n");
}

int main()
{
	int n;
	scanf("%d", &n);
	for (int i = 0; i < n; i++)
	{
		scanf("%s%s", input1Str, input2Str);
		if (input1Str[0] == '0' || input2Str[0] == '0')
		{
			printf("0\n");
			continue;
		}
		getNum();
		multiply();
		printResult();
	}
	return 0;
}
