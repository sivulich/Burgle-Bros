#pragma once
#include "./Loot.h"

class LootFactory
{
public:

	static Loot * newLoot(lootType type);
};

