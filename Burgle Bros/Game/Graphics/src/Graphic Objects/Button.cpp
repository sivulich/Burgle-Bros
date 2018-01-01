#include "./Button.h"
#include <GraphicsDefs.h>


Button::Button(string& n, vector<string>& files) : Object()
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

Button::Button(string& n, string normal, string hover, string clicked) : Object()
{
	name = n;
	bitmaps.push_back(new Bitmap(normal.c_str()));
	bitmaps.push_back(new Bitmap(hover.c_str()));
	bitmaps.push_back(new Bitmap(clicked.c_str()));

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

void Button::draw(Bitmap* target)
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
			bitmaps[pressed]->drawScaled(0, 0, w, h, x, y, scaleX* w, scaleY* h, 0);
		else
			bitmaps[0]->drawTintedScaled(al_map_rgba_f(CLICKED_R, CLICKED_G, CLICKED_B, CLICKED_A), 0, 0, w, h, x, y, scaleX* w, scaleY*h, 0);
	}
	else if (hover == true)
	{
		if (pressed <= 1)
			bitmaps[0]->drawTintedScaled(al_map_rgba_f(HOVER_R, HOVER_G, HOVER_B, HOVER_A), 0, 0, w, h, x, y, scaleX* w, scaleY* h, 0);
		else
			bitmaps[1]->drawScaled(0, 0, w, h, x, y, scaleX* w, scaleY* h, 0);
	}
	else
		bitmaps[0]->drawScaled(0, 0, w, h, x, y, scaleX* w, scaleY* h, 0);

}



string Button::click(int y, int x)
{
	if (initOk == true)
	{
		if (clickable)
		{
			if (isInside(y, x) && isNotTransparent(y, x))
			{
				DEBUG_MSG("Clicking button " << name);
				clicked = true;
				if (obs != nullptr)
					obs->update();
				return this->name;
			}
			else return "";
		}
		else return "Not Clickable";
		//DEBUG_MSG_V("Trying to click object " << name << " when is not clickable");
	}
	else DEBUG_MSG("Trying to click button " << name << " when is not initialized correctly");

	return "";
}


bool Button::overYou(int y, int x)
{
	if (initOk == true)
	{
		if (isInside(y, x) && isNotTransparent(y, x))
		{
			if (hoverable)
			{
				hover = true;
				DEBUG_MSG_V("Hovering " << name);
				return true;
			}
		}
		else
		{
			clicked = false;
			hover = false;
			return false;
		}
	}
	else
		DEBUG_MSG("Trying to hover object " << name << " when is not initialized correctly");
	return false;
}


bool Button::isNotTransparent(int y, int x)
{
	float r, g, b, a;
	al_unmap_rgba_f(bitmaps[0]->getPixel(x, y), &r, &g, &b, &a);
	return a != 0.0;
}