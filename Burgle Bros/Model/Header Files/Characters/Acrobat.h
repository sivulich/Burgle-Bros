#pragma once
#include "Character.h"
class Acrobat :	public Character
{
public:
	Acrobat() : Character(ACROBAT) {};;
	~Acrobat();
	virtual string getAction(PlayerInterface * player) override;
};

