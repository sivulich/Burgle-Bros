#pragma once
#include "Loot.h"
#include <Player.h>
class Chihuahua :
	public Loot
{
public:
	Chihuahua(lootType l) : Loot(l) { lootAvailable(true); };
	~Chihuahua();
};

