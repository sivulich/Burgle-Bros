#pragma once

#include "Observer.h"
#include "../Model/Header Files/Player.h"
#include "BoardObserver.h"
class PlayerObserver :public Observer {
public:
	PlayerObserver(Player* p,BoardObserver* po, Container* parent);
	void update();
private:
	Player* player;
	BoardObserver* playOn;
	Container* parent;	
};