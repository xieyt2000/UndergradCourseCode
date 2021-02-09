#pragma once
#include "SkilledHero.h"

class AvatarHero : public SkilledHero {
	// TODO
public:
	AvatarHero(Hero* input) : SkilledHero(input)
	{
		skillName = "Avatar";
		SkilledHero* tmp = dynamic_cast<SkilledHero*>(prev);
		if (tmp != nullptr)
		{
			avLevel = tmp->avLevel + 1;
			bsLevel = tmp->bsLevel;
		}
		else avLevel = 1;
	}
};