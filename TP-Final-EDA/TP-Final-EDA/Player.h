#pragma once
#include "Configs.h"
#include "actionNode.h"

class Player
{
public:
	Player(string & playerName);
	void setId();

	vector<Coord> visibleFrom;
	list <actionNode> actions;
private:
	string name;
	int id;
	Coord pos;
	int actionTokens;
	int stealthTokens;
	
};