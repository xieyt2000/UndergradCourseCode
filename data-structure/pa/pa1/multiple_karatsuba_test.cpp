#define	_CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<string.h>
#include<ctime>
#include<iostream>
//all the numbers are reversed
long long complexCount = 0;
struct BigNum
{
	int* m_num;//reversed
	int m_size;
};
std::clock_t f_start, f_end;
BigNum plus(const BigNum& t_num1, const BigNum& t_num2)
{
	f_start = clock();
	BigNum smallerNum, biggerNum;
	if (t_num1.m_size < t_num2.m_size)
	{
		smallerNum = t_num1;
		biggerNum = t_num2;
	}
	else
	{
		smallerNum = t_num2;
		biggerNum = t_num1;
	}
	BigNum result;
	complexCount += biggerNum.m_size;
	int resultSizeUp = biggerNum.m_size + 1;
	result.m_num = new int[resultSizeUp];
	result.m_size = biggerNum.m_size;
	for (int i = 0; i < resultSizeUp; i++)
	{
		result.m_num[i] = 0;
	}
	for (int i = 0; i < smallerNum.m_size; i++)
	{
		int thisDigitPlus = smallerNum.m_num[i] + biggerNum.m_num[i];
		result.m_num[i] += thisDigitPlus;
		if (result.m_num[i] > 9)
		{
			result.m_num[i] -= 10;
			result.m_num[i + 1]++;
		}
	}
	for (int i = smallerNum.m_size; i < biggerNum.m_size; i++)
	{
		result.m_num[i] += biggerNum.m_num[i];
		if (result.m_num[i] > 9)
		{
			result.m_num[i] -= 10;
			result.m_num[i + 1]++;
		}
	}
	if (result.m_num[resultSizeUp - 1] != 0)
	{
		result.m_size = resultSizeUp;
	}
	f_end = clock();
	if(int(f_end - f_start)>1)
	{
		std::cout << "add:";
		std::cout << int(f_end - f_start) << " " << biggerNum.m_size << std::endl;		
	}
	return result;
}

BigNum subtract(const BigNum& minuend, const BigNum& subtrahend)//ensure the result is positive
{
	f_start = clock();
	BigNum result;
	int resultSizeUp = minuend.m_size;
	result.m_num = new int[resultSizeUp];
	result.m_size = resultSizeUp;
	complexCount += minuend.m_size;
	for (int i = 0; i < resultSizeUp; i++)
	{
		result.m_num[i] = 0;
	}
	for (int i = 0; i < subtrahend.m_size; i++)
	{
		result.m_num[i] += minuend.m_num[i] - subtrahend.m_num[i];
		if (result.m_num[i] < 0)
		{
			result.m_num[i] += 10;
			result.m_num[i + 1]--;
		}
	}
	for (int i = subtrahend.m_size; i < minuend.m_size; i++)
	{
		result.m_num[i] += minuend.m_num[i];
		if (result.m_num[i] < 0)
		{
			result.m_num[i] += 10;
			result.m_num[i + 1]--;
		}
	}
	bool resultIs0 = true;
	for (int i = resultSizeUp; i > 0; i--)
	{
		if (result.m_num[i - 1] != 0)
		{
			result.m_size = i;
			resultIs0 = false;
			break;
		}
	}
	if (resultIs0)
	{
		result.m_size = 1;
	}
	f_end = clock();
	if (int(f_end - f_start)>1)
	{
		std::cout << "sub:";
		std::cout << int(f_end - f_start) << " " << minuend.m_size << std::endl;
	}
	return result;
}

BigNum split(const BigNum& t_ori, int t_lowerBound, int t_upperBound)//left closed right open
{
	BigNum ret;
	ret.m_size = t_upperBound - t_lowerBound;
	ret.m_num = t_ori.m_num + t_lowerBound;
	return ret;
}

BigNum oneDigitMultiply(int t_oneDig, const BigNum& t_bigNum)
{
	f_start = clock();
	BigNum result;
	if (t_oneDig == 0)
	{
		result.m_size = 1;
		result.m_num = new int[1];
		result.m_num[0] = 0;
		return result;
	}
	result.m_num = new int[t_bigNum.m_size + 1];
	result.m_size = t_bigNum.m_size + 1;
	for (int i = 0; i < t_bigNum.m_size + 1; i++)
	{
		result.m_num[i] = 0;
	}
	for (int i = 0; i < t_bigNum.m_size; i++)
	{
		result.m_num[i] += t_bigNum.m_num[i] * t_oneDig;
		if (result.m_num[i] > 9)
		{
			result.m_num[i + 1] += result.m_num[i] / 10;
			result.m_num[i] = result.m_num[i] % 10;
		}
	}
	if (result.m_num[t_bigNum.m_size] == 0)
	{
		result.m_size = t_bigNum.m_size;
	}
	complexCount += result.m_size;
	f_end = clock();
	if (int(f_end - f_start)>1)
	{
		std::cout << "multi:";
		std::cout << int(f_end - f_start) << " " << result.m_size << std::endl;
	}
	return result;
}

void power10(BigNum& t_base, int t_exponent)	//no return. the ori num will be changed
{
	f_start = clock();
	if (t_exponent == 0) return;
	if (t_base.m_size == 1 && t_base.m_num[0] == 0) return;
	int* newNum = new int[t_base.m_size + t_exponent];
	for (int i = 0; i < t_exponent; i++)
	{
		newNum[i] = 0;
	}
	for (int i = 0; i < t_base.m_size; i++)
	{
		newNum[t_exponent + i] = t_base.m_num[i];
	}
	delete[] t_base.m_num;
	t_base.m_num = newNum;
	t_base.m_size += t_exponent;
	complexCount += t_base.m_size;
	f_end = clock();
	if (int(f_end - f_start)>1)
	{
		std::cout << "power10:";
		std::cout << int(f_end - f_start) << " " << t_base.m_size << std::endl;
	}
}

//karatsuba https://en.wikipedia.org/wiki/Karatsuba_algorithm
BigNum multiply(const BigNum& t_num1, const BigNum& t_num2)
{
	//count++;
	if (t_num1.m_size < 2)
	{
		return oneDigitMultiply(t_num1.m_num[0], t_num2);
	}
	if (t_num2.m_size < 2)
	{
		return oneDigitMultiply(t_num2.m_num[0], t_num1);
	}
	int smallerSize = t_num1.m_size < t_num2.m_size ? t_num1.m_size : t_num2.m_size;
	int splitPoint = smallerSize / 2;	//digit at splitpoint belong to low
	//high and low use the mem of the ori
	BigNum num1High = split(t_num1, splitPoint, t_num1.m_size);
	BigNum num1Low = split(t_num1, 0, splitPoint);
	BigNum num2High = split(t_num2, splitPoint, t_num2.m_size);
	BigNum num2Low = split(t_num2, 0, splitPoint);
	//get zn
	BigNum z0 = multiply(num1Low, num2Low);
	BigNum z2 = multiply(num1High, num2High);
	BigNum z1Part1 = plus(num1Low, num1High);
	BigNum z1Part2 = plus(num2Low, num2High);
	BigNum z1 = multiply(z1Part1, z1Part2);
	delete[] z1Part1.m_num;
	delete[] z1Part2.m_num;
	//get result
	BigNum resPart2Part1 = subtract(z1, z2);
	BigNum resPart2 = subtract(resPart2Part1, z0);
	delete[] resPart2Part1.m_num;
	power10(resPart2, splitPoint);
	BigNum resPart2and3 = plus(resPart2, z0);
	power10(z2, splitPoint * 2);
	BigNum result = plus(z2, resPart2and3);
	delete[] z0.m_num;
	delete[] z1.m_num;
	delete[] z2.m_num;
	delete[] resPart2.m_num;
	delete[] resPart2and3.m_num;
	return result;
}


void initialBigNum(BigNum& t_num, char* t_numStr, int t_numSize)
{
	t_num.m_size = t_numSize;
	int* numPointer = new int[5010];
	t_num.m_num = numPointer;
	for (int i = 0; i < t_numSize; i++)
	{
		numPointer[i] = t_numStr[t_numSize - 1 - i] - '0';
	}
}

void printBigNum(const BigNum& t_num)
{
	char* output = new char[t_num.m_size + 1];
	output[t_num.m_size] = '\0';
	for (int i = 0; i < t_num.m_size; i++)
	{
		output[i] = '0' + t_num.m_num[t_num.m_size - 1 - i];
	}
	printf("%s", output);
	printf("\n");
	delete[] output;
}

int main()
{
	int n;
	scanf("%d", &n);
	char* num1Str; char* num2Str;
	//start = clock();
	std::clock_t start, end;
	for (int i = 0; i < n; i++)
	{
		//start = clock();
		num1Str = new char[5010];
		num2Str = new char[5010];
		scanf("%s%s", num1Str, num2Str);
		//end = clock();
		BigNum num1, num2;
		//start = clock();
		initialBigNum(num1, num1Str, strlen(num1Str));
		initialBigNum(num2, num2Str, strlen(num2Str));
		//end = clock();
		delete[] num1Str;
		delete[] num2Str;
		BigNum result;
		start = clock();
		result = multiply(num1, num2);
		//start = clock();
		end = clock();
		printBigNum(result);
		//end = clock();
		//double time = double(end - start);
		//printf("%f", time);
		//printf("\n");
		std::cout << complexCount << std::endl;
		start = clock();
		for (int i = 0; i < complexCount; i++)
		{
			result.m_num[0] = 0;
		}
		end = clock();
		auto time = double(end - start);
		printf("%f", time);
		printf("\n");
		delete[] result.m_num;
		delete[] num1.m_num;
		delete[] num2.m_num;
	}
	//end = clock();
	//double time = double(end - start);
	//printf("%f", time);
	//printf("\n");
	return 0;
}