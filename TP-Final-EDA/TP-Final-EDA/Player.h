#pragma once
#include "Configs.h"
#include "actionNode.h"

class Player
{
public:
	Player(string name);
	Player(string name, int id);
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