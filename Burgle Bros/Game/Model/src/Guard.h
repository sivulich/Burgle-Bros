#pragma once
#include "./Configs.h"
#include "../src/PlayerInterface.h"
#include "../src/PatrolCardDeck.h"

class Guard: public BaseModel
{
public:
	//@addparams Receives a pointer to the guard deck.
	Guard(unsigned n, PatrolCardDeck*p, PlayerInterface * p1, PlayerInterface* p2) : pos(NPOS), movedOnce(false), floorNumber(n), player1(p1), player2(p2), patroldeck(p)
	{
		pos = NPOS;
		speed = 2 + n;
	};

	//
	~Guard();

	//Add the map of the floor.
	void setFloorMap(vector<Coord> floor[4][4]);
	
	//Sets the list of alarms that the guard has to pay attention to.
	void setAlarms(vector<Coord> * alarms) { this->alarms = alarms; };

	//Adds triggered alarm to alarm list, receives the coords of a triggered alarm.
	void AddNextAlarm(Coord coord) { DEBUG_MSG("alarm set in:"<<coord); alarms->push_back(coord); }

	//Receives coordinate of alarm to turn off returns boolean value, true if alarm was succesfully turned off, else false is returned.
	bool removeAlarm(Coord coord);
	
	//Call to refresh guard destination during player turn
	void updateDestination() { this->FindPath(this->pos); notify(); };

	//Moves the guard one position, if the guard steps on the current target a new one is added (if the patrol deck has to be reseted guard base speed increases)
	//if the guard steps over an alarm it is turned off
	bool move();

	//Checks if guard sees any PlayerInterface. if it is the case a stealth token is removed from the PlayerInterface
	void GuardCheck();

	//Checks if guard sees a specific PlayerInterface. if it is the case a stealth token is removed from the PlayerInterface
	void checkPlayer(PlayerInterface * p);

	//Prints guard current guard position and active patrol card
	void print();

	//Sets amount of steps the guard has during his turn
	void SetCurrSteps() { currsteps = speed + alarms->size(); if (currsteps > 6)currsteps = 6; };

	//If possible decreases guard´s step for current turn
	bool decSteps() {if (currsteps > 0) { currsteps--; return true; } else return false;  };

	//Guard initialization for the start of his turn
	void locateGuard();

	//Positions Guard for his first Turn
	void positionGuard();

	//Finds a path to a specific tile, modifying guards current path. If the coordinate is reachable true is returned.
	bool FindPath(Coord const coord);

	//Returns Guard's current Position
	Coord getPos() { return pos; };

	//Sets Guard's current Position
	void setPos(Coord coord) { pos = coord; };

	//Returns guard current Speed (Base movements per turn)
	unsigned getSpeed() { return speed; };

	//
	void increaseSpeed() { this->speed++; notify(); };

	// Returns guard current target
	Coord getTarget() { return target; };

	// Returns guard remaining movements for the remainder of his turn
	unsigned getCurrSteps() { return currsteps; };

	// Returns true if it's the guard's turn
	void isMyTurn(bool b) { myturn = b;};

	//Returns true if the guard moved at least one during the turn, else returns false
	bool alreadyMoved() { return movedOnce; };

	// Sets bool that determines if guard moved at least once in his current Turn
	void moved(bool b) { movedOnce = b; };

private:
	unsigned speed, currsteps, floorNumber;
	//Current guard pos
	Coord pos;
	bool myturn, movedOnce;
	//Vector of coordinates of all current alarms in the floor
	vector<Coord> * alarms;
	//Guard's current expected movement, determined by the latest card drawn from the Patrol card deck
	Coord expectedMov;
	Coord target;
	//Current guard path to closest alarm or destination.
	list<Coord> path;
	//Matrix of floor's tile adjacency
	vector<Coord> floor[4][4];
	//Pointers to players
	PlayerInterface * player1;
	PlayerInterface * player2;
	//Pointer to floor's patrol card deck.
	PatrolCardDeck * patroldeck;

	//Changes an index represented position to its equivalent coordinate. Indexes are numbers that start from 0 to 15 increasing from left to right and from top to bottom.
	Coord toCoord(unsigned index) { return Coord(floorNumber, index % F_WIDTH, index / F_HEIGHT); };

	//Changes a Coordinate in the floor to its index equivalent number
	unsigned toIndex(Coord coord) { return(coord.row * F_HEIGHT + coord.col); };

	//Finds shortest path to assigned alarm
	bool shortestPath(unsigned const startNode, unsigned const endNode, vector<int> parent);

	//Determines which alarm is closer to the guard, returns closest alarm index
	unsigned closestTarget(vector<int> distances);
};

