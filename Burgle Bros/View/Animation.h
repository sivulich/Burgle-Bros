#pragma once
#include "./Header Files/ObjectInterface.h"

class Animation
{
public:
	virtual ~Animation() {};
	// Abstract function which modifies the object and advances animation
	virtual void play(ObjectInterface * object) = 0;
	bool hasEnded() { return framesLeft == 0 ? true : false; };
	bool isPlaying() { return !hasEnded(); };
protected:
	long framesLeft;
};

