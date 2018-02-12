#include ".././Tiles/Lavatory.h"

Lavatory::~Lavatory()
{
}

bool Lavatory::tryToHide() {
	if (stealthTokens > 0) {
		stealthTokens--;
		notify();
		DEBUG_MSG("You managed to hide in the stalls.");
		return true;
	}
	else {
		DEBUG_MSG("No more stealth tokens.");
		return false;
	}
}
