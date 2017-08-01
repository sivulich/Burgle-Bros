#include ".././Loots/Loot.h"

Loot::Loot()
{

}
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
