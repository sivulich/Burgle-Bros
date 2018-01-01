#include "FadeInOutAnimation.h"

FadeInOutAnimation::FadeInOutAnimation(std::pair<int, int> target, double dur) : Animation(dur)
{
	this->target = target;
	animations.push(new FadeAnimation(0.0, 1.0, dur*0.45));
	animations.push(new DelayAnimation(dur*0.1));
	animations.push(new FadeAnimation(1.0, 0.0, dur*0.45));

}

void FadeInOutAnimation::play(ObjectInterface* object)
{
	animations.top()->play(object);
	if (animations.top()->hasEnded())
	{
		switch (animations.size())
		{
		case 1:
			framesLeft = 0;
			break;
		case 2:
			object->setPosition(target.first, target.second);
			object->setVisible(true);
			break;
		case 3:
			object->setVisible(false);
			break;
		}
		delete animations.top();
		animations.pop();
	}
	else framesLeft--;


	/*if (out != nullptr && out->isPlaying())
	{
		out->play(object);
	}
	else if (out != nullptr && out->hasEnded())
	{
		object->setPosition(target.first, target.second);
		delete out;
		out = nullptr;
		framesLeft++;
	}
	else if (in != nullptr && in->isPlaying())
	{
		in->play(object);
	}
	else if (in != nullptr && in->hasEnded())
	{
		delete in;
		in = nullptr;
		framesLeft = 0;
	}
	framesLeft--;*/
}