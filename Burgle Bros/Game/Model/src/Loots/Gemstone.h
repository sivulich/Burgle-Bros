#pragma once
#include "Loot.h"
class Gemstone :
	public Loot
{
public:
	Gemstone(lootType l) : Loot(l) {};
	~Gemstone();
};

