#pragma once
#include "./Observer.h"
#include "../Graphic Objects/Image.h"
#include "../Graphic Objects/Container.h"
#include <Player.h>
#include "BoardObserver.h"
#include <Configs.h>
#include "../Animations/MoveAnimation.h"


// Observs the player token position, and stealth and action tokens
class RemotePlayerObserver :public Observer
{
public:
	RemotePlayerObserver(Player* p, BoardObserver* bo, Container* pa);
	void update();

private:
	// Pointer to the player
	Player* player;
	Coord pos;
	Image* token;
	BoardObserver* board;
	Container* parent;
};
