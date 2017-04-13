#include "../Header Files/Button.h"

void
Button::draw(Bitmap* target)
{
	if (initOk == true && target != nullptr && target->get() != nullptr)
		target->setTarget();
	else
	{
		if (initOk == true)
			DEBUG_MSG("Error while trying to draw " << name << " target was not correclty initialized");
		else
			DEBUG_MSG("Error while trying to draw " << name << ", it was not initialized correctly");
		return;
	}
	DEBUG_MSG_V("Drawing button " << name);
	int pressed = bitmaps.size() - 1;
	if (clicked == true)
	{
		if (pressed >= 1)
			bitmaps[pressed]->drawScaled(0, 0, w, h, x, y, scale* w, scale* h, 0);
		else
			bitmaps[0]->drawTintedScaled(PRESSED_TONE, 0, 0, w, h, x, y, scale* w, scale*h, 0);
	}
	else if (hover == true)
	{
		if (pressed <= 1)
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
	}
	else
		bitmaps[0]->drawScaled(
			 0, 0
			, w, h
			, x, y
			, scale* w, scale* h
			, 0
		);

}
Button::Button(string& n, vector<string>& files)
{
	name = n;
	for (auto& x : files)
		bitmaps.push_back(new Bitmap(x.c_str()));
	initOk = true;
	for (auto& x : bitmaps)
		if (x == nullptr || x->get() == nullptr)
			initOk = false;
	if (initOk == false)
	{
		DEBUG_MSG("Error while initializing button " << name << " probably missing an image file");
		return;
	}
	DEBUG_MSG_V("Init ok on button " << name);
	h = bitmaps[0]->getHeight();
	w = bitmaps[0]->getWidth();
}