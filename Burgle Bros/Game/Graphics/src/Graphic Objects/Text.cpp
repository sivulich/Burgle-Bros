#include "Text.h"

Text::Text(string& font)
{
	f = new Font(font.c_str());
	content = string("");
	if (f != nullptr)
		initOk = true;

}

Text::Text(string& font, Color c, int size, int xpos, int ypos) : Object(font, xpos, ypos, 0, 0, 1)
{
	// Load font
	f = new Font(font.c_str(), size);
	color = c;
	content = string("");
	if (f != nullptr)
		initOk = true;
}

void Text::setText(string s)
{
	content = s;
	w = f->getWidth(content.c_str());
	h = f->getHeight();
}

void Text::draw(Bitmap* target)
{
	if (visible)
	{
		if (initOk == true && target != nullptr && target->get() != nullptr)
			target->setTarget();
		else if (initOk == true)
		{
			DEBUG_MSG("Error while drawing text " << name << " target was not initialized correctly");
			return;
		}
		else
		{
			DEBUG_MSG("Trying to draw text " << name << " when it was not initialized");
			return;
		}
		DEBUG_MSG_V("Drawing text " << name);
	}

	// Before drawing play animation
	playAnimation();

	f->draw(x, y, ALLEGRO_ALIGN_CENTRE, color, content.c_str());

	if (borderVisibe)
		al_draw_rectangle(x, y, x + w*scaleX, y + h*scaleY, al_map_rgb(0, 0, 0), 3);
}
