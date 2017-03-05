#pragma once
#include "../Configs.h"
#include "../BaseCard.h"
#include "../BaseModel.h"
#include "../PlayerInterface.h"

class Character: public BaseCard
{
public:
	/**

	*/
	Character(characterType t) :type(t) { lastTimeUsed = INT_MAX; };
	~Character();
	/**
		Returns player´s character type
	*/
	characterType getType() { return  type; };
	/**
		Returns true if player is requested character
		@param t Character type that is to be checked
	*/
	bool is(characterType t) { return t == type; };
	/**
		Returns a string with the action the player can do due to their character choice
		@param p Player who wants to check the actions
	*/
	virtual string getAction(PlayerInterface * player);
	/**
		Returns the last turn character ability was used, if INT_MAX is returned means that ability was never used
	*/
	unsigned lastTurnUsed() { return lastTimeUsed; };
	/**
	
	*/
	void setLastTurnUsed(unsigned l) { lastTimeUsed = l; };
private:
	characterType type;
	unsigned lastTimeUsed;
};

