#pragma once
#include "../Configs.h"
#include "../BaseCard.h"
#include "../BaseModel.h"
#include "../PlayerInterface.h"

class Character: public BaseCard
{
public:
	Character(characterType t) :type(t) { lastTurnUsed = INT_MAX; };
	~Character();

	characterType getType() { return  type; };
	bool is(characterType t) { return t == type; };

	/**
	Returns a vector of strings with the actions the player can do on the tile they are on.
	Actions PEEK and MOVE are always valid. On each tileType overload the function
	@param p Player who wants to check the actions
	*/
	virtual string getAction(PlayerInterface * player);
	unsigned lastTurnUsed;
private:
	characterType type;
};

