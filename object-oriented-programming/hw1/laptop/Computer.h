#pragma once
#include<iostream>
using namespace std;
class Computer
{
public:
	string name;
	int stock;
	int price;
	bool operator<(Computer& a);
	friend ostream& operator<<(ostream& out, const Computer& src);
	void operator--();
	void operator++();
	void setPrice(int a);
};