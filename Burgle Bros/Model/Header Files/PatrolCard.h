#pragma once
#include "BaseModel.h"
#include "BaseCard.h"
#include "Configs.h"

class PatrolCard : public BaseCard, public BaseModel
{
public:

	PatrolCard(Coord c);
	
	Coord getCoord() { return coord; };

private:
	Coord coord;
};

