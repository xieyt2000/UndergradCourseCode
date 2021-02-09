#include"function.h"
#include<iostream>
#include<map>
#include<sstream>
#include"logic.h"
//postive stands for int, 0 for false -1 for true. apply to the whole project
using std::map;
using std::getline;
using std::cin;
using std::stringstream;
map<string, int> operatorPrecedence;	//less take the precedence
map<string, int> variants;  
int main()
{
	GenPrecedence();
	string sentence;
	stringstream ss;
	string FirstWord;
	while (getline(cin, sentence))
	{
		if (sentence.length() == 0) break;
		ss.str("");
		ss.clear();
		ss << sentence;
		ss >> FirstWord;
		if (FirstWord.size() == 0) return 0;
		if (FirstWord == "print")
		{
			ss.get(); //skip" "
			string expression;
			getline(ss, expression);
			logic op(expression);
			op.convert();
			int out = op.compute();
			print(out);
		}
		else
		{
			for (int i = 0; i < 3; i++) ss.get(); //skip" = "
			string expression;
			getline(ss, expression);
			logic op(expression);
			op.convert();
			int res = op.compute();
			variants[FirstWord] = res;
		}
	}
	return 0;
}


