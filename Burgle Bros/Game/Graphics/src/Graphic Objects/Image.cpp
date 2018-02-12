
#include "./Image.h"
#include <GraphicsDefs.h>

Image::Image(string& path) : Object()
{
	//Turbiada, si lo sacas la queda ????????????????????!!!!!!
	// PRUEBO COMENTARLO a ver si anda...
	al_init();
	al_init_image_addon();
	im.load(path.c_str());
	initOk = false;
	if (im.get() != nullptr)
	{
		initOk = true;
		flags = 0;
		x = 0;
		y = 0;

		h = im.getHeight();
		w = im.getWidth();

		scaleY = 1;
		scaleX = 1;
		r = g = b = 1.0;
		// Find the name in the path
		size_t pos = path.find_last_of(".");
		size_t pos2 = path.find_last_of("/");
		if (pos2 == string::npos) 	pos2 = 0;
		name = path.substr(pos2 + 1, pos - pos2 - 1);
		DEBUG_MSG_V("Init ok on image " << name);
	}

	else DEBUG_MSG("Error while loading image at path " << path);
}

Image::Image(string& path, int xpos, int ypos) : Object()
{
	//Turbiada, si lo sacas la queda ????????????????????!!!!!!
	// PRUEBO COMENTARLO a ver si anda...
	al_init();
	al_init_image_addon();
	im.load(path.c_str());
	initOk = false;
	if (im.get() != nullptr)
	{
		initOk = true;
		flags = 0;
		x = xpos;
		y = ypos;

		h = im.getHeight();
		w = im.getWidth();

		scaleY = 1;
		scaleX = 1;
		r = g = b = 1.0;
		// Find the name in the path
		size_t pos = path.find_last_of(".");
		size_t pos2 = path.find_last_of("/");
		if (pos2 == string::npos) 	pos2 = 0;
		name = path.substr(pos2 + 1, pos - pos2 - 1);
		DEBUG_MSG_V("Init ok on image " << name);
	}

	else DEBUG_MSG("Error while loading image at path " << path);
}

Image::Image(string& path, int xpos, int ypos, int width, int height) : Object()
{
	al_init();
	al_init_image_addon();
	im.load(path.c_str());
	initOk = false;
	if (im.get() != nullptr)
	{
		initOk = true;
		flags = 0;
		x = xpos;
		y = ypos;

		h = height;
		w = width;

		scaleY = 1;
		scaleX = 1;
		r = g = b = 1.0;
		// Find the name in the path
		size_t pos = path.find_last_of(".");
		size_t pos2 = path.find_last_of("/");
		if (pos2 == string::npos) 	pos2 = 0;
		name = path.substr(pos2 + 1, pos - pos2 - 1);
		DEBUG_MSG_V("Init ok on image " << name);
	}
	else DEBUG_MSG("Error while loading image at path " << path);
}


string Image::click(int y, int x)
{
	//if (initOk == true)
	//{
		if (clickable)
		{
			if (isInside(y, x) && isNotTransparent(y, x))
			{
				DEBUG_MSG("Clicking image " << name);
				clicked = true;
				if (obs != nullptr)
					obs->update();
				return this->name;
			}
			else return "";
		}
		else return "Not Clickable";
		//DEBUG_MSG_V("Trying to click object " << name << " when is not clickable");
	//}
	//else DEBUG_MSG("Trying to click image " << name << " when is not initialized correctly");

	return "";
}


bool Image::overYou(int y, int x)
{
	//if (initOk == true)
	//{
		if (visible==true && isInside(y, x) && isNotTransparent(y, x))
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
	//}
	//else
//		DEBUG_MSG("Trying to hover object " << name << " when is not initialized correctly");
	return false;
}

bool Image::isNotTransparent(int y, int x)
{
	float r, g, b, a;
	al_unmap_rgba_f(im.getPixel((x-this->x)*1.0/scaleX, (y-this->y)*1.0/scaleY), &r, &g, &b, &a);
	return a != 0.0;
}

void Image::draw(Bitmap* target)
{
	// Before drawing play animation
	playAnimation();

	if (visible)
	{
		if (initOk == true && target != nullptr && target->get() != nullptr)
			target->setTarget();
		else if (initOk == true)
		{
			DEBUG_MSG("Error while drawing image " << name << " target was not initialized correctly");
			return;
		}
		else
		{
			DEBUG_MSG("Trying to draw image " << name << " when it was not initialized");
			return;
		}
		DEBUG_MSG_V("Drawing image " << name);


		ALLEGRO_COLOR color;
		if (disabled)
			color = al_map_rgba_f(DISABLED_R*r, DISABLED_G*g, DISABLED_B*b, DISABLED_A*alpha);
		else if (clickable && hoverable && !clicked && hover)
			color = al_map_rgba_f(HOVER_R*r, HOVER_G*g, HOVER_B*b, HOVER_A*alpha);
		else if (!clickable || (!clickable && hoverable && !clicked) || (clickable && hoverable && !clicked && !hover))
			color = al_map_rgba_f(NORMAL_R*r, NORMAL_G*g, NORMAL_B*b, NORMAL_A*alpha);
		else if (clickable && clicked)
			color = al_map_rgba_f(CLICKED_R*r, CLICKED_G*g, CLICKED_B*b, CLICKED_A*alpha);
		
		im.drawTintedScaled(color, 0, 0, im.getWidth(), im.getHeight(), x, y, scaleX*w, scaleY*h, flags);

		if (borderVisibe)
			al_draw_rectangle(x, y, x + w*scaleX, y + h*scaleY, al_map_rgb(0, 0, 0), 3);
	}
}

void Image::setTone(float r, float g, float b)
{
	this->r = r;
	this->g = g;
	this->b = b;
}

void Image::setGreen()
{
	r = 0;
	g = 1;
	b = 0;
}
void Image::flipHorizontal()
{
	flags = flags | ALLEGRO_FLIP_HORIZONTAL;
}
void Image::load(string& path, bool keepProperties)
{
	//size_t pos = path.find('.');
	//size_t pos2 = path.find_last_of('/');
	//size_t pos3 = path.find_last_of('\\');
	//if (pos2 == string::npos) pos2 = 0;
	//if (pos3 != string::npos) pos2 = pos3;
	//name = path.substr(pos2 + 1, pos);

	im.load(path.c_str());
	if (keepProperties == false)
	{
		h = im.getHeight();
		w = im.getWidth();
		scaleX = w / im.getWidth();
		scaleY = w / im.getWidth();
	}
}