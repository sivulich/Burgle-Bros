#pragma once
#include "./Configs.h"
#include "./BaseModel.h"
/*
	Base class for a card. It can be flipped in different ways and has a description
*/
class BaseCard:public BaseModel
{
public:
	// False = Turned Down ; True = Turned  Up
	BaseCard() : faceUp(false) {};
	bool isFlipped() { return faceUp; };
	virtual void flip() { faceUp = !faceUp; notify(); };
	virtual void turnUp() { faceUp = true; notify(); };
	virtual void turnDown() { faceUp = false; notify(); };
	void setDescription(string& s) { description = s; };
	string getDescription() { return description; };
protected:
	
	bool faceUp;
	string description;
};

