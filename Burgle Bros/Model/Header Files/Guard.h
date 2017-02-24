#pragma once
#include "Configs.h"
#include "Player.h"
#include "PatrolCardDeck.h"

// OJO con punteros players y patrol deck (se deberia chequear q no sean null)
class Guard
{
public:
	/**
	@addparams receives 2 pointers to each respective player, receives a copy of a speficif floor map and a pointer to the guard deck
	*/
	Guard(vector<Coord> floor[4][4], Player * player1, Player * player2, PatrolCardDeck * patroldeck);

	/**

	*/
	~Guard();

	/**
	adds triggered alarm to alarm list
	@addparams receives the coords of a triggered alarm
	*/
	void AddNextAlarm(Coord coord) { alarms.push_front(coord); }

	/**
	@addparams coordinate of alarm to turn off
	@return boolean value, true if alarm was succesfully turned off, else false is returned
	*/
	bool RemoveAlarm(Coord coord);

	/**
	moves the guard one position, if the guard steps on the current target a new one is added (if the patrol deck has to be reseted guard base speed increases)
	if the guard steps over an alarm it is turned off
	*/
	bool Move();

	/**
	checks if guard sees a player. if it is the case a stealth token is removed from the player
	*/
	void GuardCheck();

	/**
	sets amount of steps the guard has during his turn
	*/
	void SetCurrSteps() { currsteps = speed + alarms.size(); };

	/**

	*/
	void FindPath(Coord const coord);


	Coord getPos() { return pos; };
private:
	unsigned speed, currsteps;
	Coord pos;
	list<Coord> alarms;
	Coord target;
	list<Coord> path;
	vector<Coord> floor[4][4];
	Player * player1;
	Player * player2;
	PatrolCardDeck * patroldeck;

	/**

	*/
	Coord toCoord(unsigned index) { return Coord(1, index % 4, index / 4); }; // hay q ver si tengo q definir el piso o no

    /**
	
	*/
	unsigned toIndex(Coord coord) { return(coord.col * 4 + coord.row); };

	/**

	*/
	void shortestPath(int const &startNode, int const &endNode, int* parent);

	/**

	*/
	unsigned closest(unsigned * distances);
};

