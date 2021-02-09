#include"logic.h"
#include"function.h"
#include<sstream>
#include<stack>
using std::stack;
using std::stringstream;
using std::to_string;
using std::stoi;
logic::logic(string exp)
{
	stringstream ss;
	ss << exp;
	string tmp;
	while (ss >> tmp) ori.push_back(tmp);
}
void logic::convert()
{
	stack<string> opr;
	opr.push("#");//bottom
	for (auto x : ori)
	{
		string tmp = x;
		if (operatorPrecedence.count(tmp))	//tmp is a operator
		{
			if (opr.top() == "#")
			{
				opr.push(tmp);
				continue;
			}
			if (operatorPrecedence[opr.top()] <= operatorPrecedence[tmp])
			{
				string toAddOpr;
				while (true)
				{
					toAddOpr = opr.top();
					rPol.push_back(toAddOpr);
					opr.pop();
					if (operatorPrecedence[tmp] < operatorPrecedence[opr.top()])
						break;
					if (opr.top() == "#")
						break;
				}
				opr.push(tmp);
			}
			else
			{
				opr.push(tmp);
			}
		}
		else								//tmp is a var or const
		{
			rPol.push_back(tmp);
		}
	}
	while (opr.top() != "#")
	{
		rPol.push_back(opr.top());
		opr.pop();
	}
}
int logic::compute()
{
	if (rPol.size() == 1)
	{
		if (rPol[0] == "True") return -1;
		if (rPol[0] == "False") return 0;
		if (variants.count(rPol[0])) return variants[rPol[0]];
		return std::stoi(rPol[0]);
	}
	string res;
	stack<string> operand;
	for (auto x : rPol)
	{
		string tmp = x;
		if (operatorPrecedence.count(tmp))	//tmp is a operator
		{
			if (tmp == ">=") 
			{
				string second = operand.top();
				int s = operandsToInt(second);
				operand.pop();
				string first = operand.top();
				int f = operandsToInt(first);
				operand.pop();
				if (f >= s) operand.push("True");
				else operand.push("False");
			}
			if (tmp == ">")
			{
				string second = operand.top();
				int s = operandsToInt(second);
				operand.pop();
				string first = operand.top();
				int f = operandsToInt(first);
				operand.pop();
				if (f > s) operand.push("True");
				else operand.push("False");
			}
			if (tmp == "<=")
			{
				string second = operand.top();
				int s = operandsToInt(second);
				operand.pop();
				string first = operand.top();
				int f = operandsToInt(first);
				operand.pop();
				if (f <= s) operand.push("True");
				else operand.push("False");
			}
			if (tmp == "<")
			{
				string second = operand.top();
				int s = operandsToInt(second);
				operand.pop();
				string first = operand.top();
				int f = operandsToInt(first);
				operand.pop();
				if (f < s) operand.push("True");
				else operand.push("False");
			}
			if (tmp == "!=")
			{
				string second = operand.top();
				if (variants.count(second)) second = to_string(variants[second]);
				operand.pop();
				string first = operand.top();
				if (variants.count(first)) first = to_string(variants[first]);
				operand.pop();
				if (first != second) operand.push("True");
				else operand.push("False");
			}
			if (tmp == "==")
			{
				string second = operand.top();
				if (variants.count(second)) second = to_string(variants[second]);
				operand.pop();
				string first = operand.top();
				if (variants.count(first)) first = to_string(variants[first]);
				operand.pop();
				if (first == second) operand.push("True");
				else operand.push("False");
			}
			if (tmp == "not")
			{
				string first = operand.top();
				if (variants.count(first))
				{
					if (variants[first] == -1) first = "True";
					else first = "False";
				}
				operand.pop();
				if (first == "True") operand.push("False");
				else operand.push("True");
			}
			if (tmp == "and")
			{
				string second = operand.top();
				operand.pop();
				if (variants.count(second))
				{
					if (variants[second] == -1) second = "True";
					else second = "False";
				}
				string first = operand.top();
				operand.pop();
				if (variants.count(first))
				{
					if (variants[first] == -1) first = "True";
					else first = "False";
				}
				if (first == "True" && second == "True") operand.push("True");
				else operand.push("False");
			}
			if (tmp == "or")
			{
				string second = operand.top();
				operand.pop();
				if (variants.count(second))
				{
					if (variants[second] == -1) second = "True";
					else second = "False";
				}
				string first = operand.top();
				operand.pop();
				if (variants.count(first))
				{
					if (variants[first] == -1) first = "True";
					else first = "False";
				}
				if (first == "True" || second == "True") operand.push("True");
				else operand.push("False");
			}
		}
		else                                 //tmp is a var or const
		{
			operand.push(x);
		}
	}
	res = operand.top();
	if (res=="False") return 0;
	else return -1;
}
