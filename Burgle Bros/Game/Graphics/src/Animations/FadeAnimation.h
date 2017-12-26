#pragma once
#include "Animation.h"
class FadeAnimation : public Animation
{
public:
	FadeAnimation(double alpha0,double alpha1, double dur);
	virtual void play(ObjectInterface* object)override;
private:
	double alpha0, alpha1, step;
};

