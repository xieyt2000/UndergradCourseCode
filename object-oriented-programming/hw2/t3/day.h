#pragma once
#include<string>
#include"plan.h"
class Day
{
private:
	int month;
	int day;
	std::string week;
	Plan TodayPlan[100];
protected:
	int plancount = 0;
public:
	Day(int a, int b, std::string c) : month(a), day(b), week(c) {};
	virtual ~Day() {};
	bool insert(Plan t);
	virtual void print();
};