#pragma once
#include "./Animation.h"

// Zooms in or out an objet
// If scale of an object is set to 3x, zoomAnimation(3) 
// will make it 9x and a zoomAnimation(0.5) will make it 1.5x

class zoomAnimation :	public Animation
{
public:
	zoomAnimation(double zoom, double duration);
	~zoomAnimation();
	void play(ObjectInterface* object);
private:
	double zoom; // x2 for example
	double step;
};

