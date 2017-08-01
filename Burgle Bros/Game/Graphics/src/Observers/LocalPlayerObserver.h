#pragma once
#include "./Observer.h"
#include <Player.h>
#include <Configs.h>

#include "./BoardObserver.h"
#include "../Container.h"

#include "../MoveAnimation.h"
#include "./ActionObserver.h"

class LocalPlayerObserver :public Observer {
public:
	LocalPlayerObserver(Player* p, BoardObserver* bo, Container* pa);
	void update();
private:
	Player* player;
	Container* parent;
	BoardObserver* board;
	ActionObserver* actions;
	Container* hud;
	Image* playerCard;
	Image* token;
};