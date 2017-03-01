#include "../../Header Files/Observers/PlayerObserver.h"

PlayerObserver::PlayerObserver(Player* p, BoardObserver* po, Container* parent)
{
	this->parent = parent;
	player = p;
	playOn = po;
}