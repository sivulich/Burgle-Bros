#include "./zoomAnimation.h"



zoomAnimation::zoomAnimation(double relativeScale, double duration) : Animation(duration)
{
	this->zoom = zoom;
	step = 0;
}


zoomAnimation::~zoomAnimation()
{
}


void zoomAnimation::play(ObjectInterface* object)
{
	if (step == 0)
		step = (zoom - 1) * object->getScale() / framesLeft;

	if (framesLeft > 0)
	{
		object->setScale(object->getScale() + step);
	}
	
}