#pragma once
#include <GameModel.h>
#include <alx.hpp>
#include "../src/Screen.h"
#include "../Container.h"
#include "../src/Observers/Observer.h"
#include "../src/Observers/BoardObserver.h"
#include "../src/Observers/LocalPlayerObserver.h"
#include "../src/Observers/RemotePlayerObserver.h"

// HEREDA DE OBSERVER??
class GameGraphics : public Observer
{
public:
	GameGraphics(GameModel * model);
	~GameGraphics();

	// Check Allegro initialization
	bool initOK() { return initOK_; };

	// Render objects on screen
	void render();

	// Called by game model when something is modified
	//IMPLEMENTAR
	void update();

	// Interacts upon a mouse movement, returns objet name
	bool hover(int y, int x);

	// Interacts upon a click down, returns objet name
	string click(int y, int x);

	// Interacts upon a click up, returns objet name
	void unclick(int y, int x);

	// Return screen event source (for controller)
	EventSource getScreenEventSource() { return screen->getDisplay()->getEventSource(); }

private:
	bool initOK_;
	GameModel * model;
	Screen* screen;
	Container* cont;
	BoardObserver* board;
	LocalPlayerObserver * pl;
	RemotePlayerObserver* pl2;
};

