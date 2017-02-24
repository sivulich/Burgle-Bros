#include "../../Header Files/Tiles/Scanner.h"



Scanner::~Scanner()
{
}

void Scanner::enterTile(void * player) {
	Player * p = (Player*)player;

	if (p->hasLoot())	// if the player has any loots
		setAlarm(true);
}
