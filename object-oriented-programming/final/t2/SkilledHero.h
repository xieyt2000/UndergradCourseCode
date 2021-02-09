#pragma once
#include "Hero.h"
#include<string>
using namespace std;
class SkilledHero : public Hero {
	// TODO
public:
	string skillName = "";
	Hero* prev = nullptr;
	int bsLevel;
	int avLevel;
	void getSkill(name2Level& skillMap)
	{
		
		if (skillMap.find(skillName) == skillMap.end())
		{
			if (skillName == "Bladestorm") skillMap[skillName] = bsLevel;
			else skillMap[skillName] = avLevel;
		}
		prev->getSkill(skillMap);
	}
	SkilledHero() {}
	SkilledHero(Hero* input)
	{
		prev = input;
		SkilledHero* tmp = dynamic_cast<SkilledHero*>(input);
		if (tmp == nullptr)
		{
			bsLevel = 0;
			avLevel = 0;
		}
		else
		{
		}
	}
};