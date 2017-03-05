#include "../Header Files/MoveAnimation.h"


MoveAnimation::MoveAnimation(pair<int,int> current, pair<int, int> target, double dur)
{
	xTarget = target.second;
	yTarget = target.first;
	duration = dur;
	
	framesLeft =ceil(duration* 30.0); // TIENEN QUE SER LOS FPS
	
	xStep = (xTarget - current.second) / framesLeft;
	yStep = (yTarget - current.first) / framesLeft;
}


MoveAnimation::~MoveAnimation()
{
}
void MoveAnimation::play(ObjectInterface* object)
{
	if (framesLeft>1)
	{
		pair<int, int> curr = object->getPos();
		object->setPosition(curr.first + yStep, curr.second + xStep);

		framesLeft--;
	}
	else if (framesLeft == 1)
	{
		object->setPosition(yTarget, xTarget);
		framesLeft--;
	}
		
}
