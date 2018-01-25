#pragma once
#include "Loot.h"
class Isotope :
	public Loot
{
public:
	Isotope(lootType l) : Loot(l) { lootAvailable(true); };
	~Isotope();
};

