#pragma once
#include "Loot.h"
class Mirror :
	public Loot
{
public:
	Mirror(lootType l) : Loot(l) { lootAvailable(true); };
	~Mirror();
};

