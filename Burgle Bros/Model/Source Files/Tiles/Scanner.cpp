#include "../../Header Files/Tiles/Scanner.h"



Scanner::~Scanner()
{
}

void Scanner::enterTile(PlayerInterface * player) 
{
	Tile::enterTile(player);
	if (player->hasLoot())
		setAlarm(true);
}
