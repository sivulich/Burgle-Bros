#pragma once
#include "Animation.h"
#include "../Model/Header Files/Configs.h"

class MoveAnimation :public Animation
{
public:
	MoveAnimation(pair<int, int> current, pair<int, int> target, double dur);
	~MoveAnimation();
	virtual void play(ObjectInterface* object)override;
private:
	int xTarget, yTarget;
	double xStep, yStep;
	double duration;
};

