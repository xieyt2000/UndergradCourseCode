#pragma once
#include<string>
#include<vector>
#include"global_variables.h"
using std::string;
using std::vector;
class logic
{
private:
	vector<string> ori;
	vector<string> rPol;
public:
	logic(string exp);
	~logic() = default;
	void convert();
	int compute();
};

