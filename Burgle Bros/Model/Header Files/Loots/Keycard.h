#pragma once
#include "Loot.h"
class Keycard :
	public Loot
{
public:
	Keycard(lootType l) : Loot(l) {};
	~Keycard();
};

