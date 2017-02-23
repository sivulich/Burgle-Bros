#pragma once
#include "Configs.h"
#include "Player.h"
#include "PatrolCardDeck.h"
class Guard
{
public:
	/**

	*/
	Guard(vector<Coord> floor[4][4], Player * player1, Player * player2);

	/**

	*/
	~Guard();

	/**

	*/
	void AddNextAlarm(Coord coord) { alarms.push_front(coord); }
	/**

	*/
	bool Move();

	void GuardCheck();

	void SetCurrSteps() { currsteps = speed + alarms.size(); };

	void FindPath(list<Coord> alarms, Coord dest);

private:
	unsigned speed, currsteps;
	Coord pos;
	list<Coord> alarms;
	Coord target;
	list<Coord> path;
	vector<Coord> floor[4][4];
	Player * player1;
	Player * player2;
	PatrolCardDeck patroldeck;
};

