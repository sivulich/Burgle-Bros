#pragma once
#include "Observer.h"
#include "../Image.h"
#include "../Container.h"
#include "../Model/Header Files/Player.h"
#include "BoardObserver.h"
#include "../Model/Header Files/Configs.h"
#include "../MoveAnimation.h"



class RemotePlayerObserver :public Observer {
public:
	RemotePlayerObserver(Player* p, BoardObserver* bo, Container* pa);
	void update();
private:
	Player* player;
	Image* token;
	BoardObserver* board;
	Container* parent;
};
