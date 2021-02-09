#pragma once
#include "SkilledHero.h"

class BladestormHero : public SkilledHero {
	// TODO
public:
	BladestormHero(Hero* input) : SkilledHero(input)
	{
		skillName = "Bladestorm";
		SkilledHero* tmp = dynamic_cast<SkilledHero*>(prev);
		if (tmp != nullptr)
		{
			avLevel = tmp->avLevel;
			bsLevel = tmp->bsLevel + 1;
		}
		else bsLevel = 1;
		
	}
};