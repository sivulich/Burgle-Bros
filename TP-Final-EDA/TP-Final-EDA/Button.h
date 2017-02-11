#pragma once
#include "object.h"

class Button :public object {
public:
	void draw(ALLEGRO_BITMAP* target);
	/*Image 0 is the default image, Image 1 is the hover image, Image 2 is the pressed image*/
	void setImages(vector<ALLEGRO_BITMAP*>& bms) { bitmaps = bms; };
private:
	vector<ALLEGRO_BITMAP*> bitmaps;
};
