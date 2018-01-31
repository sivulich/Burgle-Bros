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
	Image * yesButton;// ESTOS SON DE PRUEBA PORQ NO SE USAR LA QUESTION BOX
	Image * noButton; // ESTOS SON DE PRUEBA PORQ NO SE USAR LA QUESTION BOX	

	PlayerObserver * player1;
	PlayerObserver * player2;
};

