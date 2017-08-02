#include "./MoveRelativeAnimation.h"

MoveRelativeAnimation::MoveRelativeAnimation(pair<int, int> toMove, double duration) : Animation(duration)
{
	toMoveY = toMove.first;
	toMoveX = toMove.second;
	framesLeft = ceil(duration* 30.0);
	
	xStep = toMoveX / framesLeft;
	yStep = toMoveY / framesLeft;
}


MoveRelativeAnimation::~MoveRelativeAnimation()
{
}

void MoveRelativeAnimation::play(ObjectInterface* object)
{
	if (framesLeft>0)
	{
		object->setPosition(object->getPos().first + yStep, object->getPos().second + xStep);
		framesLeft--;
	}

}
