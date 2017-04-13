#pragma once
#include "Configs.h"
#include "PlayerInterface.h"
#include "PatrolCardDeck.h"

// OJO con punteros players y patrol deck (se deberia chequear q no sean null)
class Guard: public BaseModel
{
public:
	/**
	@addparams Receives a pointer to the guard deck
	*/
	Guard(unsigned n,PatrolCardDeck*p, PlayerInterface * p1, PlayerInterface* p2) : pos(NPOS), floorNumber(n), player1(p1), player2(p2), patroldeck(p)
	{
		speed = 2 + n;
	};

	/**

	*/
	~Guard();

	/**
		Add the map of the floor
	*/
	void setFloorMap(vector<Coord> floor[4][4]);
	
	/**
	
	*/
	void setAlarms(vector<Coord> * alarms) { this->alarms = alarms; };
	/**
	adds triggered alarm to alarm list
	@addparams receives the coords of a triggered alarm

	*/
	void AddNextAlarm(Coord coord) { DEBUG_MSG("alarm set in:"<<coord); alarms->push_back(coord); }

	/**
	@addparams coordinate of alarm to turn off
	@return boolean value, true if alarm was succesfully turned off, else false is returned
	*/
	bool removeAlarm(Coord coord);

	/**
	moves the guard one position, if the guard steps on the current target a new one is added (if the patrol deck has to be reseted guard base speed increases)
	if the guard steps over an alarm it is turned off
	*/
	bool move();

	/**
	checks if guard sees a PlayerInterface. if it is the case a stealth token is removed from the PlayerInterface
	*/
	void GuardCheck();

	/**

	*/
	void print();

	/**
	sets amount of steps the guard has during his turn
	*/
	void SetCurrSteps() { currsteps = speed + alarms->size(); if (currsteps > 6)currsteps = 6; };

	/**
	
	*/
	bool decSteps() 
	{
		if (currsteps > 0) { currsteps--; return true; }
		else return false; 
	};
	/**
	
	*/
	void locateGuard();
	/**

	*/
	bool FindPath(Coord const coord);
	/**
	
	*/
	Coord getPos() { return pos; };
	/**
	
	*/
	void setPos(Coord coord) { pos = coord; };
	/**
	
	*/
	unsigned getSpeed() { return speed; };
	/**
	
	*/
	Coord getTarget() { return target; };
	/**
	
	*/
	void isMyTurn(bool b) { myturn = b;};
private:
	unsigned speed, currsteps,floorNumber;
	Coord pos;
	bool myturn;
	vector<Coord> * alarms;
	Coord target;
	list<Coord> path;
	vector<Coord> floor[4][4];
	PlayerInterface * player1;
	PlayerInterface * player2;
	PatrolCardDeck * patroldeck;

	/**

	*/
	Coord toCoord(unsigned index) { return Coord(floorNumber, index % 4, index / 4); }; // hay q ver si tengo q definir el piso o no

	/**

	*/
	unsigned toIndex(Coord coord) { return(coord.row * 4 + coord.col); };

	/**

	*/
	bool shortestPath(unsigned const startNode, unsigned const endNode, vector<int> parent);

	/**

	*/
	unsigned closestTarget(vector<int> distances);
};

