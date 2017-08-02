#pragma once
#include "./Animation.h"
#include <Configs.h>

// Moves an object a relative distance given in 'toMove' in 'dur' seconds
class MoveRelativeAnimation : public Animation
{
public:
	MoveRelativeAnimation(pair<int, int> toMove, double duration);
	~MoveRelativeAnimation();
	virtual void play(ObjectInterface* object)override;
private:
	int toMoveX, toMoveY;
	double xStep, yStep;
};

