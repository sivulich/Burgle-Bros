#include "../../Header Files/Loots/Loot.h"

Loot::Loot()
{

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
