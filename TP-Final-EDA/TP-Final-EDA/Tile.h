#pragma once
#include "Player.h"
#include "Configs.h"
class
	Tile
{
	Tile();
	Tile(int x, int y);
	Tile(int type, int x, int y);
	/**

	*/
	virtual void peek(Player p);

	/**

	*/
	virtual bool moveTo(Player p);

	/**

	*/
	int getType();

	/**

	*/
	bool hasAlarm();

	/**

	*/
	bool isFlipped();

	/**

	*/
	void  setAlarm(bool b);

	/**

	*/
	vector<string>& getActions(Player p);

	/**

	*/
	bool doAction(string Action, Player p);

	/**

	*/
	int getSafeNumber();

	/**

	*/
	vector<Tile*>& getAdjacent();

private:
	bool flipped;
	bool alarm;
	int safeNumber;
	int type;
	vector<string> actions;
	vector<Tile*> adjacent;
	COORD coord;
};
