#pragma once
#include <string>
using std::string;
class Animal
{
public:
	Animal(string in)
	{
		name = in;
	}
	virtual void speak() = 0;
	virtual void swim() = 0;
	void action()
	{
		speak();
		swim();
	}
	string name;
	virtual ~Animal(){}
};