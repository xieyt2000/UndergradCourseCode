#pragma once
#include<string>
class Plan
{
public:
	Plan(int a, int b, std::string s);
	Plan();
	int day, month;
	std::string todo;
};