#include "Computer.h"
#include "ComputerCollection.h"
#include <iostream>
#include <string>
#include <algorithm>
#include <cstring>
using namespace std;
istream& operator>>(istream& in, ComputerCollection& dst) 
{
	dst.inindicator++;
	char nam[20], a[50], sto[10], pri[10];
	in >> a;
	int len = strlen(a);
	int i = 0;
	for (; a[i] != '-'; i++)
	{
		nam[i] = a[i];
	}
	nam[i] = 0;
	dst.market[dst.inindicator].name = nam;
	i++;
	int indi1 = i;
	for (; a[i] != '-'; i++)
	{
		sto[i - indi1] = a[i];
	}
	sto[i - indi1] = 0;
	dst.market[dst.inindicator].stock = atoi(sto);
	
	i++;
	int indi2 = i;
	for (; i<len; i++)
	{
		pri[i - indi2] = a[i];
	}
	pri[i - indi2] = 0;
	dst.market[dst.inindicator].price = atoi(pri);
	
	return in;
}
Computer& ComputerCollection::operator[](string src)
{
	for (int i = 0; i <= inindicator; i++)
	{
		if (market[i].name == src) return market[i];
	}
}
void ComputerCollection::sortByScore()
{
	for (int i = inindicator; i > 0; i--)
	{
		for (int j = 0; j < i; j++)
		{
			if (market[j] < market[j + 1])
			{
				Computer t = market[j];
				market[j] = market[j + 1];
				market[j + 1] = t;
			}
		}
	}
}
ostream& operator<<(ostream& out, const ComputerCollection& src)
{
	for (int i = 0; i <= src.inindicator; i++)
	{
		cout << src.market[i];
		cout << endl;
	}
	return out;
}
