#pragma once
#include "Tile.h"
/*
Safes are the goal. Roll the combination to open them. When opened, draw a Loot, and increase the Guard's 
movement die by one on this floor and all those below it.
*/
class Safe : public Tile
{
public:
	Safe();
	~Safe();
};

