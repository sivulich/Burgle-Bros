#pragma once
#include "Animation.h"
#include <Configs.h>

// Moves an object to the abolute position given in 'target' in 'dur' seconds
class MoveAnimation :public Animation
{
public:
	MoveAnimation(pair<int, int> target, double dur);
	~MoveAnimation();
	std::pair<int, int> getTarget() { return pair<int, int>(yTarget, xTarget); };
	virtual void play(ObjectInterface* object)override;
private:
	int xTarget, yTarget;
	double xStep, yStep;
};

