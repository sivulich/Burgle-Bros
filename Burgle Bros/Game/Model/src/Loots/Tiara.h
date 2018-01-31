#pragma once
#include "Loot.h"
class Tiara :
	public Loot
{
public:
	Tiara(lootType l) : Loot(l) { lootAvailable(true); };
	~Tiara();
};

