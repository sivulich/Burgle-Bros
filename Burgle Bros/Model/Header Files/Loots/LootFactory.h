#pragma once
#include "./Loot.h"

class LootFactory
{
public:

	static Loot * newTile(lootType type);
};

