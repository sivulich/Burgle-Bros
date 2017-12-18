
#include "./Image.h"
#include <GraphicsDefs.h>

Image::Image(string& path)
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
		clickable = true;
		hoverable = true;

		h = im.getHeight();
		w = im.getWidth();

		scale = 1;
		scaleY = 1;
		scaleX = 1;
		
		hoverTone = HOVER_TONE;
		normalTone = al_map_rgba(255, 255, 255, 255);

		x = 0;
		y = 0;

		// Find the name in the path
		size_t pos = path.find_last_of(".");
		size_t pos2 = path.find_last_of("/");
		if (pos2 == string::npos) 	pos2 = 0;
		name = path.substr(pos2 + 1, pos-pos2-1);
		DEBUG_MSG_V("Init ok on image " << name);
	}
	else DEBUG_MSG("Error while loading image at path " << path); 
}

Image::Image(string& path, int xpos, int ypos, int width, int height)
{
	//Turbiada, si lo sacas la queda ????????????????????!!!!!!
	// PRUEBO COMENTARLO a ver si anda...
	al_init();
	al_init_image_addon();
	
	im.load(path.c_str());

	if (im.get() != nullptr)
	{
		initOk = true;
		clickable = true;
		hoverable = true;

		h = height;
		w = width;

		int a, b;
		
		scaleX = 1;
		scaleY = 1;	

		hoverTone = HOVER_TONE;
		normalTone = al_map_rgba(255, 255, 255, 255);

		setPosition(ypos, xpos);

		// Find the name in the path
		size_t pos = path.find_last_of(".");
		size_t pos2 = path.find_last_of("/");
		if (pos2 == string::npos) 	pos2 = 0;
		name = path.substr(pos2 + 1, pos - pos2 - 1);
		DEBUG_MSG_V("Init ok on image " << name);
	}
	else
		DEBUG_MSG("Error while loading image at path " << path);
}

void Image::draw(Bitmap* target)
{
	if(initOk==true && target!=nullptr && target->get()!=nullptr)
		target->setTarget();
	else if (initOk == true)
	{
		DEBUG_MSG("Error while drawing image " << name << " target was not initialized correctly");
		return;
	}
	else
	{
		DEBUG_MSG("Trying to draw image "<<name<< " when it was not initialized");
		return;
	}
	DEBUG_MSG_V("Drawing image " << name);

	// Before drawing play animation
	if (hasAnimation())
	{
		animation->play(this);
		if (animation->hasEnded())
		{
			delete animation;
			animation = nullptr;
		}

	}

	if(hover==true)
		im.drawTintedScaled(hoverTone, 0, 0, im.getWidth(), im.getHeight(), x, y, scaleX*w, scaleY*h, 0);
	else
		im.drawTintedScaled(normalTone, 0, 0, im.getWidth(), im.getHeight(), x, y, scaleX* w, scaleY*h, 0);

	if(borderVisibe)
		al_draw_rectangle(x, y, x + w*scaleX, y + h*scaleY, al_map_rgb(0, 0, 0), 3);
}

void Image::load(string& path, bool keepProperties)
{
	size_t pos = path.find('.');
	size_t pos2 = path.find_last_of('/');
	size_t pos3 = path.find_last_of('\\');
	if (pos2 == string::npos) pos2 = 0;
	if (pos3 != string::npos) pos2 = pos3;
	name = path.substr(pos2 + 1, pos);

	im.load(path.c_str());
	if (keepProperties == false)
	{
		h = im.getHeight();
		w = im.getWidth();
		scale = scaleX = scaleY = w / im.getWidth();
	}
}