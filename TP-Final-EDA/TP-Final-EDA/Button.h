#pragma once
#include "object.h"

class Button :public object
{
public:
	Button(string& n) { name = n; };
	void draw(ALLEGRO_BITMAP* target);
	/*Image 0 is the default image, Image 1 is the hover image, Image 2 is the pressed image*/
	void setImages(vector<string>& files);
private:
	vector<ALLEGRO_BITMAP*> bitmaps;
};
