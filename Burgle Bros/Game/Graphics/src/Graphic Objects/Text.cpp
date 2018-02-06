#include "Text.h"

Text::Text(string font)
{
	f = new Font(font.c_str());
	content = string("");
	if (f->get() != nullptr)
		initOk = true;

}

Text::Text(string font, Color c, int size, int xpos, int ypos) : Object(font, xpos, ypos, 0, 0, 1)
{
	// Load font
	initOk = false;
	f = new Font(font.c_str(), size);
	if (f->get() != nullptr)
	{
		clickable = false;
		color = c;
		content = string("");
		initOk = true;
	}
	else DEBUG_MSG("Error loading font " + font);
}

Text::Text(string font, string content, Color c, int size, int xpos, int ypos) : Object(font, xpos, ypos, 0, 0, 1)
{
	// Load font
	initOk = false;
	f = new Font(font.c_str(), size);

	if (f->get() != nullptr)
	{
		color = c;
		clickable = false;
		initOk = true;

		this->content = content;
		w = f->getWidth(content.c_str());
		h = f->getHeight();
	}
	else DEBUG_MSG("Error loading font " + font);

}


void Text::setText(string s)
{
	content = s;
	w = f->getWidth(content.c_str());
	h = f->getHeight();
}

void Text::draw(Bitmap* target)
{
	// Before drawing play animation
	playAnimation();

	if (visible)
	{
		if (initOk == true && target != nullptr && target->get() != nullptr)
		{
			target->setTarget();
			if (disabled)
			{
				float r, g, b;
				al_unmap_rgb_f(color, &r, &g, &b);
				f->draw(x, y, ALLEGRO_ALIGN_CENTRE, al_map_rgba_f(r, g, b, 0.5), content.c_str());
			}
			else
				f->draw(x, y, ALLEGRO_ALIGN_CENTRE, color, content.c_str());

			if (borderVisibe)
				al_draw_rectangle(x, y, x + w*scaleX, y + h*scaleY, al_map_rgb(0, 0, 0), 3);
		}
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
}
