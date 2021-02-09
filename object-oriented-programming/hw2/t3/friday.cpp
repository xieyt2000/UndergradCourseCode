#include"friday.h"
#include<iostream>
#include<string>
void Friday::print()
{
	Day::print();
	if (plancount == 0) std::cout << "Friday is Free :)" << std::endl;
	else std::cout << "Friday is Busy :(" << std::endl;;
}