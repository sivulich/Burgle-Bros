#pragma once
#include "Configs.h"
class Player
{
public:
	Player(string name);
	Player(string name, int id);
	void setId();

private:
	string name;
	int id;
	int actionTokens;
	int cor;
	
};