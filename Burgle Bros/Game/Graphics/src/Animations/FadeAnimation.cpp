#include "FadeAnimation.h"

FadeAnimation::FadeAnimation(double alpha0, double alpha1, double dur) : Animation(dur)
{
	this->alpha0 = alpha0;
	this->alpha1 = alpha1;
	step = 0;
}

void FadeAnimation::play(ObjectInterface* object)
{
	if (step == 0)
	{
		step = (alpha1 - alpha0) / framesLeft;
		object->setAlpha(alpha0);
	}

	if (framesLeft>1)
	{
		object->setAlpha(object->getAlpha() + step);
		framesLeft--;
	}

	// In last frame... to avoid float errors in increments
	else if (framesLeft == 1)
	{
		object->setAlpha(alpha1);
		framesLeft--;
	}
}
