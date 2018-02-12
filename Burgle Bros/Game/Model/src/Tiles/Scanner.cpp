#include ".././Tiles/Scanner.h"



Scanner::~Scanner()
{
}

void Scanner::enter(PlayerInterface * player) 
{
	Tile::enter(player);
	if (player->hasLoot() && !player->has(MIRROR))
		setAlarm(true);
}
