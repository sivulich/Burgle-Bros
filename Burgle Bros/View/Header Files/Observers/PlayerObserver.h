#pragma once

#include "Observer.h"
#include "../../../Model/Header Files/Player.h"
#include "BoardObserver.h"
#include "../Button.h"

class PlayerObserver :public Observer {
public:
	//PlayerObserver( BoardObserver* po, Player* p, Container* pa);
	void update();
private:
	Player* player;
	BoardObserver* playOn;
	Container* parent;	
	Container* toDraw;
	Container* moveB;
	Container* peekB;
	Container* pow1;
	Container* pow2;
	Container* pow3;
	Button* offerLoot;
	Button* requestLoot;
	Container* Player;

};