#pragma once
#include "Loot.h"
class Painting :
	public Loot
{
public:
	Painting(lootType l) : Loot(l) { lootAvailable(true); };
	~Painting();
};

