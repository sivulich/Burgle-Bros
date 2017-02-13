#include "Button.h"

void
Button::draw(Bitmap* target)
{
	target->setTarget();
	int pressed = 2;
	if (bitmaps.size() == 2)
	{
		pressed = 1;

	}
	if (clicked == true)
		bitmaps[pressed]->drawScaled(
			 0, 0
			, w, h
			, x, y
			, scale* w, scale* h
			, 0
		);
	else if (hover == true)
		if(pressed==1)
			bitmaps[0]->drawTintedScaled(HOVER_TONE
				, 0, 0
				, w, h
				, x, y
				, scale* w, scale* h
				, 0
			);
		else
			bitmaps[1]->drawScaled(
				 0, 0
				, w, h
				, x, y
				, scale* w, scale* h
				, 0
			);
	else
		bitmaps[0]->drawScaled(
			 0, 0
			, w, h
			, x, y
			, scale* w, scale* h
			, 0
		);

}

void
Button::setImages(vector<string>& files)
{
	for (auto& x : files)
		bitmaps.push_back(new Bitmap(x.c_str()));
	h = bitmaps[0]->getHeight();
	w = bitmaps[0]->getWidth();
}