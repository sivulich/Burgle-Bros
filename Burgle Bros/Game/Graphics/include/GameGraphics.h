#pragma once
#include <GameModel.h>
#include <GraphicsDefs.h>
#include <alx.hpp>

#include "../Graphic Objects/Screen.h"
#include "../Graphic Objects/Container.h"
#include "../Graphic Objects/Textbox.h"
#include "../Observers/Observer.h"
#include "../Observers/BoardObserver.h"
#include "../Observers/HudObserver.h"


class GameGraphics : public Observer
{
public:
	GameGraphics(GameModel * model);
	~GameGraphics();

	// Check Allegro initialization
	bool initOK() { return initOK_; };

	// Render objects on screen
	void render();

	// Called by Game Model when something is modified
	//IMPLEMENTAR
	void update();

	// Interacts upon a mouse movement, returns objet name
	bool hover(int y, int x);

	// Interacts upon a click down, returns objet name
	string click(int y, int x);

	// Interacts upon a click up, returns objet name
	void unclick(int y, int x);

	// Pop up a message to answer yes or no
	void askQuestion(string question);

	// When answered, call this function
	void closeQuestion();
	// Set as clickable the given tiles (and illuminate them), and not clickable the other ones.
	void setTilesClickable(vector<Coord> tiles);

	// Set as clickable all the tiles
	void setAllClickable();

	// Set visible the border of all grafic objects
	void setBorderVisible(bool b);

	// Return screen event source (for controller)
	EventSource getScreenEventSource() { return screen->getDisplay()->getEventSource(); }

	// Return true if guard is moving
	bool guardIsMoving() { if (showingGameScreen) return board->guardIsMoving(); };
	// Create graphic objects to represent game model on scren


	//
	void showMenuScreen();
	//
	void showCreditsScreen();
	//
	void showRulesScreen();
	//
	void showModeScreen();
	
	void showSetupScreen(int player = 0);

	// Shows the game screen
	void showGameScreen();

	string getPlayerName();

private:
	bool initOK_;
	bool showingGameScreen;
	bool showingSetupScreen;

	// Pointer to the Game Model
	GameModel * model;

	// Graphic objects
	Screen* screen;
	Container* cont;

	Textbox * textBox;
	Image * blur;
	// Observers
	BoardObserver* board;
	HudObserver * hud;

};

