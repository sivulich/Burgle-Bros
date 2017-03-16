#pragma once
#include "../Screen.h"
#include "../Container.h"
#include "../Model/Header Files/GameModel.h"
#include "Observer.h"
#include "BoardObserver.h"
#include "LocalPlayerObserver.h"
#include "RemotePlayerObserver.h"

class GameObserver :public Observer {
public:
	GameObserver(GameModel* g,int sHeight);
	void update();
	bool isEmpty() { return events.isEmpty(); };
	string input();
	~GameObserver();
private:
	Screen* screen;
	GameModel* game;
	Container* cont;
	BoardObserver* board;
	LocalPlayerObserver * pl;
	RemotePlayerObserver* pl2;
	EventQueue events;
};

