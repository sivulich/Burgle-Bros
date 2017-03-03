#pragma once

#include "Animation.h"
#include "MoveAnimation.h"
class FlipAnimation :public Animation {
public:
	FlipAnimation(ObjectInterface* ob,double duration);
	void play(ObjectInterface* ob);
	bool passedMiddle() { return middle; };
private:
	Animation* move;
	double rate,duration;
	std::pair<int, int> startPos,midPos;
	long initialFrames;
	bool middle;

};