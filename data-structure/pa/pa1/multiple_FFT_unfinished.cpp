#define _CRT_SECURE_NO_WARNINGS
#include<cstdio>
#include<cstring>
#include<cmath>

//numbers are reversed

class Complex
{
public:
	double m_real;
	double m_imaginary;
	Complex(double t_real, double t_imaginary) :m_real(t_real), m_imaginary(t_imaginary) {}
	Complex operator+ (const Complex t_cp)
	{
		return Complex(m_real + t_cp.m_real, m_imaginary + t_cp.m_imaginary);
	}
	Complex operator- (const Complex t_cp)
	{
		return Complex(m_real - t_cp.m_real, m_imaginary - t_cp.m_imaginary);
	}
	Complex operator* (const Complex t_cp)
	{
		double real = m_real * t_cp.m_real - m_imaginary * t_cp.m_imaginary;
		double imaginary = m_real * t_cp.m_imaginary + m_imaginary * t_cp.m_real;
		return Complex(real, imaginary);
	}
};

const int MAX_DIGIT = 20010;
const int PI = 3.141592653589793;

char inputStr1[5010], inputStr2[5010];
Complex input1[MAX_DIGIT], input2[MAX_DIGIT];
int result[MAX_DIGIT];
int input1Len, input2Len, biggerInputLen, oprLen;


void fastFourierTransform(Complex* t_complexNums, int t_length, bool inverse)
{
	if (t_length == 1) return;
	int middle = t_length / 2;
}

void getNum()
{
	input1Len = strlen(inputStr1); input2Len = strlen(inputStr2);
	if (input1Len > input2Len)
	{
		biggerInputLen = input1Len;
	}
	else
	{
		biggerInputLen = input2Len;
	}
	oprLen = 1;
	while (oprLen < biggerInputLen)
	{
		oprLen *= 2;
	}
	oprLen *= 2;
	for (int i = 0; i < input1Len; i++)
	{
		input1[i].m_real = 0.0 + inputStr1[input1Len - i - 1] - '0';
		input1[i].m_imaginary = 0.0;
	}
	for (int i = 0; i < input2Len; i++)
	{
		input2[i].m_real = 0.0 + inputStr1[input2Len - i - 1] - '0';
		input2[i].m_imaginary = 0.0;
	}
}

int main()
{
	int n;
	scanf("%d", &n);
	for (int i = 0; i < n; i++)
	{
		for (int i = 0; i < 5010; i++)
		{
			inputStr1[i] = '\0';
			inputStr2[i] = '\0';
		}
		scanf("%s%s", inputStr1, inputStr2);
		getNum();
		fastFourierTransform(input1, oprLen, false); fastFourierTransform(input2, oprLen, false);
		
	}
	return 0;
}