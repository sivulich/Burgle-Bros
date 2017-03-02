#pragma once

#include "object.h"
/*Class used to draw an image, it mantains the original aspect ratio*/
class Image :public Object {
public:
	Image() {};
	Image(string& path);
	/** Draws the image to the given bitmap
		@param target Target to draw the image in
	*/
	void draw(Bitmap* target);

	/** Sets scale for the image to be drawn, it mantains aspect ratio
		@param s Scale
	*/
	void setScale(double s) { this->scale = s; };

	/** Sets new image
		@param path
	*/
	void load(string& s);

private:
	Bitmap im;
};