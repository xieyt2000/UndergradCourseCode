#pragma once
#include"day.h"
class Friday : public Day
{
public:
	using Day::Day;
	void print();
	~Friday() {};
};