#include "DelayAnimation.h"

DelayAnimation::DelayAnimation(double dur) : Animation(dur)
{}

void DelayAnimation::play(ObjectInterface* object)
{
	framesLeft--;
}
