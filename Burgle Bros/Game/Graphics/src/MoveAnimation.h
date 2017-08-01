#pragma once
#include "Animation.h"
#include <Configs.h>

class MoveAnimation :public Animation
{
public:
	MoveAnimation(pair<int, int> current, pair<int, int> target, double dur);
	std::pair<int, int> getTarget() { return pair<int, int>(yTarget, xTarget); };
	~MoveAnimation();
	virtual void play(ObjectInterface* object)override;
private:
	int xTarget, yTarget;
	double xStep, yStep;
	double duration;
};

