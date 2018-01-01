#pragma once
#include <boost/shared_ptr.hpp>

#include <GameModel.h>
#include <GameGraphics.h>
#include <alx.hpp>

using namespace alx;

class GameController
{
public:
	GameController(GameModel * m, GameGraphics * g );
	virtual ~GameController() {}
	void start();
	void stop();
	bool isRunning();
	void getInput();
	void processEvent();
private:
	shared_ptr<void> stateMachine;
	// String name obtained from graphics 
	string s;

	// Pointers to model and graphic classes
	GameModel * model;
	GameGraphics * graphics;

	// 
	EventQueue eventQueue;
	Timer renderTimer;
	Timer guardTimer;

};


