#include "MoveAnimation.h"
#include "../Model/Header Files/Configs.h"


MoveAnimation::MoveAnimation(int currentX, int currentY, int xTg, int yTg, double dur)
{
	xTarget = xTg;
	yTarget = yTg;
	duration = dur;
	
	framesLeft = duration * 30; // TIENEN QUE SER LOS FPS

	xStep = (xTarget - currentX) / framesLeft;
	yStep = (yTarget - currentY) / framesLeft;
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
