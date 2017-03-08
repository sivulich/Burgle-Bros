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
	Guard() { pos = NPOS; player1 = player2 = nullptr; };

	/**

	*/
	~Guard();


	/**
		Point the guard to the players
	*/
	void setPlayers(PlayerInterface * p1, PlayerInterface * p2);

	/**
		Add the map of the floor
	*/
	void setFloorMap(vector<Coord> floor[4][4]);

	/**
	
	*/
	void setDeck(PatrolCardDeck * patroldeck);
	
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
	bool RemoveAlarm(Coord coord);

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
	void SetCurrSteps() { currsteps = speed + alarms->size(); };

	/**
	
	*/
	bool decSteps() 
	{
		if (currsteps > 0) { currsteps--; return true; }
		else return false; 
	};

	/**

	*/
	bool FindPath(Coord const coord);

	Coord getPos() { return pos; };

	void setPos(Coord coord) { pos = coord; };
private:
	unsigned speed, currsteps;
	Coord pos;
	vector<Coord> * alarms;
	Coord target;
	list<Coord> path;
	vector<Coord> floor[4][4];
	PlayerInterface * player1;
	PlayerInterface * player2;
	PatrolCardDeck * patroldeck;

	/**

	*/
	Coord toCoord(unsigned index) { return Coord(1, index % 4, index / 4); }; // hay q ver si tengo q definir el piso o no

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

