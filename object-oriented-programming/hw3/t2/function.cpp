#include"global_variables.h"
#include"function.h"
#include<iostream>
using std::cout;
using std::get;
using std::endl;
using std::stoi;
void GenPrecedence()
{
	operatorPrecedence[">"] = operatorPrecedence[">="] = operatorPrecedence["<"] = operatorPrecedence["<="] =
	operatorPrecedence["=="] = operatorPrecedence["!="] = 1;
	operatorPrecedence["not"] = 2;
	operatorPrecedence["and"] = 3;
	operatorPrecedence["or"] = 4;
}
void print(int a)
{
	if (a > 0) cout << a << endl;
	if (a == 0) cout << "False" << endl;
	if (a == -1) cout << "True" << endl;
}
int operandsToInt(string op)
{
	if (variants.count(op)) return variants[op];
	else return stoi(op);
}