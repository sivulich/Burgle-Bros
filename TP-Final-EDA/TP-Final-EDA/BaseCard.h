#pragma once
#include <string>

class BaseCard
{
public:
	BaseCard() : faceUp(false) {};
	~BaseCard();
	bool isFlipped() { return faceUp; };
	virtual void flip() { faceUp = !faceUp; };
	virtual void turnUp() { faceUp = true; };
	virtual void turnUp(bool b) { b == true ? turnUp() : turnDown(); };
	virtual void turnDown() { faceUp = false; };
	virtual void turnDown(bool b) { b == true ? turnDown() : turnUp(); };
	void setDesctiption(std::string& s) { description = s; };
	std::string getDescription() { return description; };
private:
	bool  faceUp;
	std::string description;
};

