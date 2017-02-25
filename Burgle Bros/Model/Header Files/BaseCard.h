#pragma once
#include "Configs.h"

/*
	Base class for a card. It can be flipped in different ways and has a description
*/
class BaseCard
{
public:
	BaseCard() : faceUp(false) {};
	bool isFlipped() { return faceUp; };
	virtual void flip() { faceUp = !faceUp; };
	virtual void turnUp() { faceUp = true; };
	virtual void turnDown() { faceUp = false; };
	void setDescription(string& s) { description = s; };
	string getDescription() { return description; };
protected:
	bool faceUp;
	string description;
};

