#pragma once
#include "Configs.h"
#include "actionNode.h"

class Player
{
public:
	Player(string & playerName);
	void setId(characterID character);
	void newTurn() { actionTokens = NUMBER_ACTION_TOKENS; };
	void move(Coord & newPos);
	void removeStealthToken() { stealthTokens--; };
	void removeActionToken() { actionTokens--; };
	int getStealthTokens() { return stealthTokens; };
	int getActionTokens() { return actionTokens; };

	vector<Coord> visibleFrom;
	list <actionNode> actions;
private:
	string name;
	characterID id;
	Coord pos;
	int actionTokens;
	int stealthTokens;
	
};