#pragma once
#include "Animation.h"

class DelayAnimation : public Animation
{
public:
	DelayAnimation(double dur);
	virtual void play(ObjectInterface* object)override;
};

