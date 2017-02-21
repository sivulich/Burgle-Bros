#pragma once

#include "BaseCard.h"
#include "Configs.h"
class PatrolCard : public BaseCard
{
public:

	PatrolCard(Coord c);
	
	Coord getCoord() { return coord; };

private:
	Coord coord;
};

