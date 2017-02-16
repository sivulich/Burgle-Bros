#pragma once
#include "Object.h"

class Button :public Object
{
public:
	Button(string& n) { name = n; };
	void draw(Bitmap* target);
	/*Image 0 is the default image, Image 1 is the hover image, Image 2 is the pressed image*/
	void setImages(vector<string>& files);
private:
	vector<Bitmap*> bitmaps;
};
