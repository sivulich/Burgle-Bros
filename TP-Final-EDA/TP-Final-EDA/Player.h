#pragma once
#include "Configs.h"
#include "actionNode.h"

class Player
{
public:
	Player(string & playerName);
	void setId(characterID i) { id = i; };
	characterID getId() { return id; };
	vector<Coord> visibleFrom;
	list <actionNode> actions;
private:
	string name;
	characterID id;
	Coord pos;
	int actionTokens;
	int stealthTokens;
	
};