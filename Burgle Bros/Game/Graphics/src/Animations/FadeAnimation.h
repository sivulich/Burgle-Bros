#pragma once
#include "Animation.h"
class FadeAnimation : public Animation
{
public:
	FadeAnimation(double alpha0,double alpha1, double dur, bool hideWhenFinished=false);
	virtual void play(ObjectInterface* object)override;
private:
	double alpha0, alpha1, step;
	bool hideWhenFinished;
};

