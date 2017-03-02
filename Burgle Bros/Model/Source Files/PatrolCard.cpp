#include "../Header Files/PatrolCard.h"



PatrolCard::PatrolCard(Coord c)
{
	 coord = c; 
	 description = string("A") + to_string(c.row+1);
	 description[0] += coord.col;
}

