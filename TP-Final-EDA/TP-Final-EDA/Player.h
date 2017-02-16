#pragma once
#include "Configs.h"
#include "actionNode.h"

class Player
{
public:
	Player(string & playerName);
	void setId(characterID character);
	void newTurn();
	void move(Coord & newPos);
	void newAction(string & action);
	void removeStealthToken();
	void removeActionToken();
	int getStealthTokens();
	int getActionTokens();

	vector<Coord> visibleFrom;
	list <actionNode> actions;
private:
	string name;
	characterID id;
	Coord pos;
	int actionTokens;
	int stealthTokens;
	
};