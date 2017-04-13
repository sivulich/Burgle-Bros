#pragma once
#include "Observer.h"
#include "../Container.h"
#include "../../../Model/Header Files/Player.h"
#include "../Image.h"
#include "../Button.h"
#include "../../../Model/Header Files/Configs.h"

class ActionObserver :public Observer {
public:
	/** Creates the action observer for the player
		@p Player to be observed
		@separation of the actions in the grid
		@max actions that can be added to this observer
		@pa Parent container to draw itself in
	*/
	ActionObserver(Player* p,int separation,int max, Container* pa);
	
	/** Updates the observer
	*/

	void update();

	~ActionObserver();
private:
	Container* parent,*actionBox;
	Player* player;
	int max,separation;
	map<string, Image> actions;
	map<string, Button> buttons;

};