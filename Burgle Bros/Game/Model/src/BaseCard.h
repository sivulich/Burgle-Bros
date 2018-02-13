#pragma once
#include "./Configs.h"
#include "./BaseModel.h"
/*
	Base class for a card. It can be flipped in different ways and has a description
*/
class BaseCard:public BaseModel
{
public:
	BaseCard() : faceUp(false) {};

	BaseCard(string s, bool face) : faceUp(face) { setDescription(s); };
	/**
	False = Turned Down ; True = Turned  Up
	*/
	
	// FOR DEBUGGING!!!
	void debugFlip() { faceUp = !faceUp; };

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

