#pragma once
#include <Board.h>
#include "../Graphic Objects/Container.h"
#include "./FloorObserver.h"
#include "./observer.h"
#include "./GameModel.h"


// Observer for the board of the game 
class BoardObserver :public Observer
{
public:
	// Construct the observer with a board pointer and a parent container
	BoardObserver(GameModel* model, Container* c);
	bool guardIsMoving() { return floors[0]->guardIsMoving() || floors[1]->guardIsMoving() || floors[2]->guardIsMoving(); };
	void showTopPatrol(int floorNumber) { floors[floorNumber]->showTopPatrol(); };
	void hideTopPatrol(int floorNumber) { floors[floorNumber]->hideTopPatrol(); };
	// Zoom the selected tile
	void zoomTile(Coord c);
	// Unzoom the tile
	void unZoomTile();
	FloorObserver& operator[](size_t i) { return *(floors[i]); };
	//
	void update();

private:
	// Pointer to the board of the game
	Board* board;

	Container * boardContainer;

	// Parent Container
	Container* parent;

	// Three floor observers
	FloorObserver* floors[3];



};