#include "./PatrolCard.h"



PatrolCard::PatrolCard(Coord c)
{
	 coord = c; 
	 description = string("A") + to_string(c.row + 1) + string("F") + to_string(c.floor);
	 description[0] += coord.col;

}

