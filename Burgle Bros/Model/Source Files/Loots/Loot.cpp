#include "../../Header Files/Loots/Loot.h"

Loot::Loot(lootType l)
{
	type = l;
}


Loot::~Loot()
{
}

void Loot::update()
{
	if (owner != nullptr)
	{
		pos = owner->getPosition();
	}
}
