#include "Computer.h"
#include "ComputerCollection.h"
#include <iostream>
#include <string>
using namespace std;
bool Computer::operator<(Computer &a) 
{
	if (stock < a.stock) return true;
	if (stock == a.stock) 
	{
		if (price < a.price) return true;
		else return false;
	}
	if (stock > a.stock) return false;
}
ostream& operator<<(ostream& out, const Computer& src)
{
	out << src.name << "-num-" << src.stock << "-price-" << src.price;
	return out;
}
void Computer::operator--()
{
	if (stock != 0)--stock;
}
void Computer::operator++()
{
	++stock;
}
void Computer::setPrice(int a)
{
	price = a;
}