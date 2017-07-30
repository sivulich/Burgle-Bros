#pragma once
#pragma once

#include <boost/shared_ptr.hpp>


#include "../Model/Header Files/GameModel.h"

//----------------------- EVENTS -----------------------------//
struct BaseEvent {};

struct movee : BaseEvent {};
struct peek : BaseEvent {};
struct throwDice : BaseEvent {};
struct useToken : BaseEvent {};
struct addToken : BaseEvent {};
struct pass : BaseEvent {};
struct pause : BaseEvent {};
struct resume : BaseEvent {};
struct gameOver : BaseEvent {};
struct burglarsWin : BaseEvent {};
struct playAgain : BaseEvent {};
struct close : BaseEvent {};
struct errorReceived : BaseEvent {};
struct errorHandled : BaseEvent {};
struct offerLoot : BaseEvent {};
struct requestLoot : BaseEvent {};
struct createAlarm : BaseEvent {};
struct spyPatrol : BaseEvent {};
struct placeCrow : BaseEvent {};
struct pickUpLoot : BaseEvent {};
struct yes : BaseEvent {};
struct no : BaseEvent {};
struct render : BaseEvent {};
struct coord : BaseEvent
{
	coord(Coord p) :c(p) {};
	Coord c;
};


class GameController
{
public:
	GameController(GameModel * m);
	virtual ~GameController() {}
	void start();
	void stop();
	bool isRunning();
	void getInput();
	void processEvent();
private:
	shared_ptr<void> FSM;
	string s;

};


