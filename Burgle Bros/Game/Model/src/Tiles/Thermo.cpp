#include ".././Tiles/Thermo.h"


Thermo::~Thermo()
{
}

void Thermo::enter(PlayerInterface * p)
{
	Tile::enter(p);
	if (p->has(ISOTOPE))
		this->setAlarm(true);
}