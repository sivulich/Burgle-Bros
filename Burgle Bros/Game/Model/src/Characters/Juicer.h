#pragma once
#include "Character.h"
class Juicer :
	public Character
{
public:
	Juicer() : Character(JUICER) {};
	~Juicer();
	virtual string getAction(PlayerInterface * player) override;
};

