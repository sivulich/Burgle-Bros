#include "../../Header Files/Tiles/Fingerprint.h"

Fingerprint::~Fingerprint()
{
}

void Fingerprint::enterTile(Player p) {
	Tile::enterTile(p);		//do the normal enterTile procedure
	//then activate the alarm
	setAlarm(true);
}