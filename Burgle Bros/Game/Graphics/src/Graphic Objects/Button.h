#pragma once
#include "Object.h"

class Button :public Object
{
public:
	Button() {};
	/** This constructor sets the name for the button and the given paths are set in the given order,
	@param files files[0] - Default Image, files[1] - Hover or pressed if only two paths are give, files[2] - Pressed
	@param n Name for the button

	*/
	Button(string& n, vector<string>& files);


	Button(string& n, string normal, string hover, string clicked);
	/** Draws the the button to the given bitmap
	@param target Target bitmap, to draw button in
	*/
	virtual void draw(Bitmap* target)override;

	virtual string click(int y, int x)override;

	virtual bool overYou(int y, int x)override;
private:
	// Three bitmaps for diferent button states
	vector<Bitmap*> bitmaps;

	bool isNotTransparent(int y, int x);
};
