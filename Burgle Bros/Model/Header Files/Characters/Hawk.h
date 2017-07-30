#pragma once
#include "Character.h"
class Hawk :public Character
{
public:
	Hawk() : Character(HAWK) {};
	~Hawk();
	virtual string getAction(PlayerInterface * player) override;
};

