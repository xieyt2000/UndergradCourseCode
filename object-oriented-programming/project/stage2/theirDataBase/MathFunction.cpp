#include<cmath>
#include<string>
#include<vector>
#include <iostream>
#include "DateTime.h"
#define PI 3.141593
using std::string;
using std::vector;
using std::cout;
using std::stod;
using std::stoi;
using std::endl;

//1 ABS
double AbsoluteValue(double ori) 
{
	return abs(ori);
}

//2 CEIL
int CeilInt(double ori)
{
	return ceil(ori);
}

//3 FLOOR
int FloorInt(double ori)
{
	return floor(ori);
}

//4 PI
double GetPI()
{
	return PI;
}

//5 POW
double Power(double x, double y)
{
	return pow(x, y);
}

//6 MOD
int ModRem(int x, int y)
{
	return (x % y);
}

//7 SIGN
int Singnal(double x)
{
	if (x < 0) return -1;
	if (x > 0) return 1;
	return 0;
}

//8 SQRT
double SqureRoot(double x)
{
	return sqrt(x);
}

//9 RADIANS
double degreeToradians(double degree)
{
	return degree / 180.0 * PI;
}

//10 LOG10
double lg(int x)
{
	return log10(x);
}


void PrintMathFunction(vector<string> sentence)
{
	string cmd = sentence[1];
	if (cmd == "PI")
	{
		cout << GetPI() << endl;
		return;
	}
	if (cmd == "ADDTIME")
	{
		Time t(sentence[3]);
		string date = sentence[5].substr(0, 10);
		string time = sentence[5].substr(11, 8);
		DateTime n(date, time);
		n.addTime(t);
		cout << n << endl;
		return;
	}
	if (cmd == "ADDDAY")
	{
		int x = stoi(sentence[3]);
		string date = sentence[5].substr(0, 10);
		string time = sentence[5].substr(11, 8);
		DateTime n(date, time);
		n.addDate(x);
		cout << n << endl;
		return;
	}
	double x = stod(sentence[3]);
	double y;
	if (sentence.size() > 6)  y = stod(sentence[5]);
	if (cmd == "ABS")
	{
		cout << AbsoluteValue(x);
	}
	else if (cmd == "CEIL")
	{
		cout << CeilInt(x);
	}
	else if (cmd == "FLOOR")
	{
		cout << FloorInt(x);
	}
	else if (cmd == "POW")
	{
		cout << Power(x, y);
	}
	else if (cmd == "MOD")
	{
		cout << ModRem(x, y);
	}
	else if (cmd == "SIGN")
	{
		cout << Singnal(x);
	}
	else if (cmd == "SQRT")
	{
		cout << SqureRoot(x);
	}
	else if (cmd == "RADIANS")
	{
		cout << degreeToradians(x);
	}
	else if (cmd == "LOG10")
	{
		cout << lg(x);
	}
	cout << endl;
}