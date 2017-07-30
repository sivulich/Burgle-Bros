#pragma once
#include "Character.h"
class Peterman :
	public Character
{
public:
	Peterman() : Character(PETERMAN) {};
	~Peterman();
	virtual string getAction(PlayerInterface * player) override;
};

