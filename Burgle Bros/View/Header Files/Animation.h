#pragma once
#include "ObjectInterface.h"

class Animation
{
public:
	virtual ~Animation() { framesLeft = 0; };
	// Abstract function which modifies the object and advances animation
	virtual void play(ObjectInterface * object) = 0;
	bool hasEnded() { return (framesLeft > 0 ? false : true); };
	bool isPlaying() { return hasEnded()==false; };
protected:
	long framesLeft;
};

