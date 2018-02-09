#include "./ZoomAnimation.h"

ZoomAnimation::ZoomAnimation(double zoom, double duration) : Animation(duration)
{
	this->zoom = zoom;
	this->finalW = 0;
	this->finalH = 0;
	stepX = stepY = 0;
	computed = false;
}

ZoomAnimation::ZoomAnimation(int finalW, int finalH, double duration) : Animation(duration)
{
	this->zoom = 0;
	this->finalW = finalW;
	this->finalH = finalH;
	stepX = stepY = 0;
	computed = false;
}

void ZoomAnimation::play(ObjectInterface* object)
{
	if (computed==false)
	{
		computed = true;
		if (zoom != 0)
		{
			finalW = zoom * object->getWidth();
			finalH = zoom * object->getHeight();
		}

		double scaleX = finalW / ((double)object->getWidth());// *object->getScales().second);
		double scaleY = finalH / ((double)object->getHeight());// *object->getScales().first);
		
		stepX = (scaleX - object->getScales().second) / framesLeft;
		stepY = (scaleY - object->getScales().first) / framesLeft;
	}

	if (framesLeft > 0)
	{
		std::pair<double, double> s = object->getScales();
		object->setScaleY(s.first + stepY);
		object->setScaleX(s.second + stepX);
	}
}
