#pragma once
#include "Animation.h"
#include "MoveAnimation.h"
#include "ZoomAnimation.h"

#include <Configs.h>

// Moves and zooms an object to the abolute position given in 'target' in 'dur' seconds
class MoveAndZoomAnimation :public Animation
{
public:
	MoveAndZoomAnimation(int finalX, int finalY, int finalW, int finalH, double duration, bool deleteWhenFinished = false);
	virtual void play(ObjectInterface* object)override;
private:
	MoveAnimation * m;
	ZoomAnimation * z;
	bool hideWhenFinished;
};

