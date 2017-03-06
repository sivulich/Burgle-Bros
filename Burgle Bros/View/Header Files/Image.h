#pragma once

#include "object.h"
#include "ALX\Color.hpp"
/*Class used to draw an image, it mantains the original aspect ratio*/
class Image :public Object {
public:
	Image() {};
	Image(string& path);
	/** Draws the image to the given bitmap
		@param target Target to draw the image in
	*/
	void draw(Bitmap* target);

	void setNormalTone(Color n) { normalTone = n; };
	void setHoverTone(Color n) { hoverTone = n; };
	/** Sets new image
		@param path
	*/
	void load(string& s);

	
private:
	Bitmap im;
	Color hoverTone, normalTone;
};