#pragma once
#include "./Observer.h"
#include "../src/Graphic Objects/Container.h"
#include "../GameModel.h"
#include "../src/Observers/PlayerObserver.h"


// Creates the hud and updates the posible actions the current player can do
class HudObserver : public Observer
{
public:
	HudObserver(GameModel * m,BoardObserver* boardObs, Container * c);
	virtual void update()override;
	void disableActions();
	void loadPlayerToken(string s);
	~HudObserver();
private:
	GameModel * model;
	BoardObserver * boardObs;

	// Graphic objects
	Container * hudCont;
	Container * topHudCont;
	map<string, Image*> actions;

	Image * pauseButton;
	Image * exitButton;

	PlayerObserver * player1;
	PlayerObserver * player2;
};

