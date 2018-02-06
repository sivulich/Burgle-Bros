#include "./MoveAnimation.h"


MoveAnimation::MoveAnimation(pair<int, int> target, double duration) : Animation(duration)
{
	yTarget = target.first;
	xTarget = target.second;
	// Increments are not calculated here because animation is created 
	// outside the object, and sometimes its not posible to know its position
	// at that time. So this values are calculated in the first call of "play".
	xStep = 0;
	yStep = 0;
}


MoveAnimation::~MoveAnimation()
{
}

void MoveAnimation::play(ObjectInterface* object)
{
	// If step has not been calculates yet
	if (xStep == 0 && yStep == 0 && framesLeft>0)
	{
		// Calculate increments in each frame (with sign included!)
		xStep = (xTarget - object->getPos().second) / framesLeft;
		yStep = (yTarget - object->getPos().first) / framesLeft;

	}

	if (framesLeft>1)
	{
		object->setPosition(object->getPos().first + yStep, object->getPos().second + xStep);
		framesLeft--;
	}
	// In last frame set the object to the target! (to avoid float errors in increments)
	else if (framesLeft == 1)
	{
		object->setPosition(yTarget, xTarget);
		framesLeft--;
	}
		
}
