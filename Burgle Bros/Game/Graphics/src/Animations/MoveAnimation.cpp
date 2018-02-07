#include "./MoveAnimation.h"


MoveAnimation::MoveAnimation(pair<int, int> target, double duration) : Animation(duration)
{
	yTarget = target.first;
	xTarget = target.second;
	
	count = 0;
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
		xStep = ((double)xTarget - (double)object->getPos().second) / (double)framesLeft;
		yStep = ((double)yTarget - (double)object->getPos().first) / (double)framesLeft;
		y0 = object->getPos().first;
		x0 = object->getPos().second;
	}

	if (framesLeft>1)
	{
		object->setPosition(y0+count*yStep, x0+count*xStep);
		framesLeft--;
		count++;
	}
	// In last frame set the object to the target! (to avoid float errors in increments)
	else if (framesLeft == 1)
	{
		object->setPosition(yTarget, xTarget);
		framesLeft--;
	}
		
}
