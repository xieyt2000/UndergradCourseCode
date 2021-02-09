#pragma once
#include<iostream>
using namespace std;
class ComputerCollection
{
public:
	Computer market[100];
	int inindicator = -1;
	friend istream& operator>>(istream& in, ComputerCollection& dst);
	Computer& operator[](string src);
	void sortByScore();
	friend ostream& operator<<(ostream& out, const ComputerCollection& src);
};