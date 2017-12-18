#pragma once
#include <Board.h>
#include "../Graphic Objects/Container.h"
#include "./FloorObserver.h"
#include "./observer.h"


// Observer for the board of the game 
class BoardObserver:public Observer
{
public:
	// Construct the observer with a board pointer and a parent container
	BoardObserver(Board* b, Container* c);
	
	FloorObserver& operator[](size_t i) { return *(floors[i]); };
	//
	void update();

private:
	// Three floor observers
	FloorObserver* floors[3];

	// One container for each floor
	//Container* floorContainer[3];
	Container * boardContainer;
	// Pointer to the board of the game
	Board* board;

	// Parent Container
	Container* parent;
};