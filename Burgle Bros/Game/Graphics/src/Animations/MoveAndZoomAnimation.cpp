#include "MoveAndZoomAnimation.h"

MoveAndZoomAnimation::MoveAndZoomAnimation(int finalX, int finalY, int finalW, int finalH, double duration, bool hideWhenFinished) : Animation(duration)
{
	m = new MoveAnimation(std::pair<int, int>(finalY, finalX), duration);
	z = new ZoomAnimation(finalW, finalH, duration);
	this->hideWhenFinished = hideWhenFinished;
}

void MoveAndZoomAnimation::play(ObjectInterface* object)
{
	m->play(object);
	z->play(object);
	framesLeft--;
	if (framesLeft == 0 && hideWhenFinished)
		object->setVisible(false);
}