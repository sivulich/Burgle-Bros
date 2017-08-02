#include "./FlipAnimation.h"

FlipAnimation::FlipAnimation(ObjectInterface* ob, double duration) : Animation(duration)
{
	initialFrames=framesLeft = ceil(duration * FPS);
	std::pair<double, double> scales = ob->getScales();
	rate = 2.0*scales.first / framesLeft;
	startPos = ob->getPos();
	midPos= std::pair<int, int>(ob->getPos().first , ob->getPos().second + ob->getScale()*ob->getSize().second *0.5);
	move = new MoveAnimation(midPos, duration / 2.0);
	middle = false;
}

void
FlipAnimation::play(ObjectInterface* ob)
{
	if (framesLeft == 1)
	{
		delete move;
		ob->setPosition(startPos.first, startPos.second);
		ob->setScale(ob->getScale());
		framesLeft--;
	}
	else if (framesLeft > initialFrames / 2)
	{
		move->play(ob);
		ob->setScaleX(ob->getScales().second - rate);
		framesLeft--;
	}
	else
	{
		if (middle == false)
		{
			delete move;
			move =  new MoveAnimation(startPos, duration / 2.0);
			middle = true;
		}
		move->play(ob);
		ob->setScaleX(ob->getScales().second + rate);
		framesLeft--;
	}
}