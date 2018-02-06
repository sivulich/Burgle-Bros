#pragma once
#include <boost/shared_ptr.hpp>

#include <GameModel.h>
#include <GameGraphics.h>
//#include <BurgleNetwork.h>
#include <alx.hpp>

using namespace alx;


class GameController
{
public:
	GameController(GameModel * m, GameGraphics * g/*, BurgleNetwork * n*/);
	virtual ~GameController() {}
	void start();
	void stop();
	bool isRunning();
	void getInput();
	void processEvent();
private:
	int throwDice();
	shared_ptr<void> stateMachine;
	// String name obtained from graphics 
	string s;
	bool connectedFlag;
	bool tileZoomMode;
	// Pointers to model and graphic classes
	GameModel * model;
	GameGraphics * graphics;
	//BurgleNetwork * network;
	// 
	EventQueue eventQueue;
	Timer renderTimer;
	Timer guardTimer;

};


