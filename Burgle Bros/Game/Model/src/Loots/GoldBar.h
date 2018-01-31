#pragma once
#include "Loot.h"
class GoldBar :	public Loot
{
public:
	GoldBar(lootType l) : Loot(l) { lootAvailable(true); };
	~GoldBar();
};

