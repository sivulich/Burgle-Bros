#include "Screen.h"

Screen::Screen(int h, int w, string& pathToBackground)
{
	initOk = false;
	if (al_init() == true)
	{
		if (al_init_image_addon()==true && al_init_primitives_addon()==true )
		{

			toDraw = al_create_bitmap(w, h);
			this->h = h;
			this->w = w;
			clickable = false;
			hoverable = false;
			offsetX = 0;
			offsetY = 0;
			bScale = 1;
			background = al_load_bitmap(pathToBackground.c_str());
			display = al_create_display(w, h);
			toDraw = al_create_bitmap(w, h);
			initOk = true;
		}
		else
			cout << "Couldnt init allegro addons" << endl;
	}
	else
		cout << "Couldnt init allegro" << endl;
}
string
Screen::click(int y, int x)
{
	for (auto& ob : objects)
	{
		if (ob->overYou(y, x ) == true)
			return ob->click(y, x);
	}
	return "";
}

void
Screen::unClick()
{
	for (auto& ob : objects)
		ob->unClick();
}

void
Screen::draw()
{
	al_set_target_bitmap(toDraw);
	al_clear_to_color(al_map_rgba_f(0, 0, 0, 0));
	al_draw_scaled_bitmap(background, offsetX, offsetY, al_get_bitmap_width(background), al_get_bitmap_height(background), 0, 0,
		bScale*al_get_bitmap_width(background), bScale*al_get_bitmap_height(background), 0);
	for (int i = objects.size() - 1; i >= 0; i--)
		objects[i]->draw(toDraw);
	al_set_target_backbuffer(display);
	al_draw_bitmap(toDraw, 0, 0, 0);
	al_flip_display();
}

bool
Screen::overYou(int y, int x)
{
	for (int i = objects.size() - 1; i >= 0; i--)
		objects[i]->overYou(y, x);
	return true;
}