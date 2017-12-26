#pragma once

#include "object.h"
#include <Color.hpp>

/* Class used to draw an image, it mantains the original aspect ratio */
class Image : public Object
{
public:
	Image() {};
	Image(string& path);
	Image(string& path, int xpos, int ypos, int width, int height);

	/** 
		Draws the image to the given bitmap
		@param target Target to draw the image in
	*/
	virtual void draw(Bitmap* target)override;


	/**
		Loads new image
		@param path
	*/
	void load(string& s, bool keepProperties=true);

private:
	// Bitmap containing the image
	Bitmap im;
};