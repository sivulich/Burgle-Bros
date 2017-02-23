#pragma once
#include "Object.h"

class Button :public Object
{
public:
	/** This constructor sets the name for the button and the given paths are set in the given order,
	@param files files[0] - Default Image, files[1] - Hover or pressed if only two paths are give, files[2] - Pressed
	@param n Name for the button

	*/
	Button(string& n, vector<string>& files);
	/** Draws the the button to the given bitmap
	@param target Target bitmap, to draw button in
	*/
	void draw(Bitmap* target);
private:
	vector<Bitmap*> bitmaps;
};
