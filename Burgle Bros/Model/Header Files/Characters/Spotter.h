#pragma once
#include "Character.h"
class Spotter :
	public Character
{
public:
	Spotter() : Character(SPOTTER) {};
	~Spotter();
	virtual string getAction(PlayerInterface * player)override;
private:
};

