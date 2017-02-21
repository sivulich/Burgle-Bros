#include "PatrolCard.h"



PatrolCard::PatrolCard(Coord c)
{
	 coord = c; 
	 description = to_string(c.col + 'A') + to_string(c.row);
}

PatrolCard::~PatrolCard()
{
}

