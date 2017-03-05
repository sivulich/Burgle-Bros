#pragma once
#include "Observer.h"
#include "../Model/Header Files/Player.h"
#include "BoardObserver.h"
#include "../Container.h"
#include "../Model/Header Files/Configs.h"
#include "../MoveAnimation.h"
class LocalPlayerObserver :public Observer {
public:
	LocalPlayerObserver(Player* p, BoardObserver* bo, Container* pa);
	void update();
private:
	Player* player;
	Container* parent;
	BoardObserver* board;
	Container* hud;
	Image* playerCard;
	Image* token;
};