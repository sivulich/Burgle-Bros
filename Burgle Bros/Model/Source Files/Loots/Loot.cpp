#include "Loot.h"

Loot::Loot()
{

}


Loot::~Loot()
{
}


void Loot::drop()
{
	taken = false;
	owner = nullptr;
};

void Loot::pick(Player* p)
{
	taken = true;
	owner = p;
	p->addLoot(this);
};