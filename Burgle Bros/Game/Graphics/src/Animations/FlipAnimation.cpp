#include "./FlipAnimation.h"

FlipAnimation::FlipAnimation(ObjectInterface* ob, double duration) : Animation(duration)
{
	initialFrames = framesLeft = ceil(duration * FPS);
	scales = ob->getScales();
	startPos = ob->getPos();
	rate = 2.0 * scales.second /(double) framesLeft;
	rateY = 2.0 * 0.16 / (double)framesLeft;
	this->duration = duration;
	midPos = std::pair<int, int>((int)(startPos.first - TILE_SIZE *0.08),(int) (startPos.second + TILE_SIZE));
	move = new MoveAnimation(midPos, duration / 2.0);
	middle = false;
}

void FlipAnimation::play(ObjectInterface* ob)
{
	if (framesLeft == 1)
	{
		delete move;
		ob->setPosition(startPos.first, startPos.second);
		ob->setScaleY(scales.first);
		ob->setScaleX(scales.second);
		framesLeft--;
		return;
	}

	if (framesLeft > initialFrames / 2)
	{
		move->play(ob);
		ob->setScaleX(ob->getScales().second - rate);
		ob->setScaleY(ob->getScales().first + rateY);
		framesLeft--;
	}
	else if (framesLeft <= initialFrames / 2)
	{
		if (middle == false)
		{
			delete move;
			ob->flip();
			move =  new MoveAnimation(startPos, duration / 2.0);
			middle = true;
		}
		move->play(ob);
		ob->setScaleX(ob->getScales().second + rate);
		ob->setScaleY(ob->getScales().first - rateY);
		framesLeft--;
		
	}
	
}