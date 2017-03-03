#pragma once
#include "Animation.h"
class MoveAnimation :public Animation
{
public:
	MoveAnimation(int currentX, int currentY, int xTg, int yTg, double dur);
	~MoveAnimation();
	virtual void play(ObjectInterface* object)override;
private:
	int xTarget, yTarget;
	double xStep, yStep;
	double duration;
};

