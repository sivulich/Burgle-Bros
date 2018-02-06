#pragma once
#include "./Animation.h"

// Zooms in or out an objet
// If scale of an object is set to 3x, ZoomAnimation(3) 
// will make it 9x and a ZoomAnimation(0.5) will make it 1.5x

class ZoomAnimation :	public Animation
{
public:
	// Create a zoom animation with a final scale to apply to the object
	ZoomAnimation(double zoom, double duration);
	// Create a zoom animation with a final with and height for the object
	ZoomAnimation(int finalW, int finalH,double duration);
	void play(ObjectInterface* object);
private:
	int finalW, finalH;
	double zoom;
	double stepX, stepY;
	bool computed;
};

