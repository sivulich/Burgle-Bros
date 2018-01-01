#pragma once
#include <stack>
#include "Animation.h"
#include "FadeAnimation.h"
#include "DelayAnimation.h"
class FadeInOutAnimation : public Animation
{
public:
	FadeInOutAnimation(std::pair<int,int> target, double dur);
	virtual void play(ObjectInterface* object)override;
private:
	
	std::stack<Animation*> animations;
	FadeAnimation * out;
	FadeAnimation * in;
	std::pair<int, int> target;
};

