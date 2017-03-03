#include "MoveAnimation.h"


MoveAnimation::MoveAnimation(pair<int,int> current, pair<int, int> target, double dur)
{
	xTarget = target.first;
	yTarget = target.second;
	duration = dur;
	
	framesLeft = duration * 30; // TIENEN QUE SER LOS FPS

	xStep = (xTarget - current.first) / framesLeft;
	yStep = (yTarget - current.second) / framesLeft;
}


MoveAnimation::~MoveAnimation()
{
}
void MoveAnimation::play(ObjectInterface* object)
{
	if (this->isPlaying())
	{
		pair<int, int> curr = object->getPos();
		object->setPosition(curr.first + xStep, curr.second + yStep);
		framesLeft--;
	}
}
