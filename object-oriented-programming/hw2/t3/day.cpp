#include"day.h"
#include<iostream>
#include<string>
bool Day::insert(Plan t)
{
	bool flag1= (t.day == day &&
		t.month == month);
	if (flag1)
	{
		TodayPlan[plancount] = t;
		plancount++;
	}
	return flag1;
}
void Day::print()
{
	std::cout << month << "/" << day << " " << week;
	if (plancount == 0) std::cout << " Today is Free" << std::endl;
	else
	{
		std::cout << " Today's Plan:" << std::endl;
		for (int i = 0; i < plancount; i++)
		{
			std::cout << TodayPlan[i].todo << std::endl;
		}
	}
}