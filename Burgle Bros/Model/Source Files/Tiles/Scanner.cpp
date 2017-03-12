#include "../../Header Files/Tiles/Scanner.h"



Scanner::~Scanner()
{
}

void Scanner::enter(PlayerInterface * player) 
{
	Tile::enter(player);
	if (player->hasLoot())
		setAlarm(true);
}
