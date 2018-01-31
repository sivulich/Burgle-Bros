#pragma once
#include "Loot.h"
class CursedGoblet :
	public Loot
{
public:
	CursedGoblet(lootType l) : Loot(l) { lootAvailable(true); };
	~CursedGoblet();
};

