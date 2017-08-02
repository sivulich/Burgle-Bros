#pragma once
#include "ObjectInterface.h"
#include <GraphicsDefs.h> // SOLO POR FPS

class Animation
{
public:
	Animation(float duration) { framesLeft = ceil( duration * FPS ); };
	virtual ~Animation() { };

	// Abstract function which modifies the object and advances animation
	virtual void play(ObjectInterface * object) = 0;

	bool hasEnded() { return (framesLeft > 0 ? false : true); };

	bool isPlaying() { return hasEnded()==false; };

protected:
	long framesLeft;
};

