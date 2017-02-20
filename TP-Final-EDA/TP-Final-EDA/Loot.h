#pragma once
#include "Configs.h"
class Loot
{
public:
	Loot();
	~Loot();
	lootID randomLoot() {};
	
private:
	lootID ID;
	Coord pos; 
	bool iAmFree;

};

