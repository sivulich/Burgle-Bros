
#include "../Header Files/Image.h"


Image::Image(string& path)
{
	al_init();
	al_init_image_addon();
	im.load(path.c_str());
	
	if (im.get() != nullptr)
	{
		
		initOk = true;
		h = im.getHeight();
		w = im.getWidth();
		size_t pos = path.find_last_of(".");
		size_t pos2 = path.find_last_of("/");
		clickable = true;
		hoverable = true;
		x = 0;
		y = 0;
		if (pos2 == string::npos)
			pos2 = 0;
		name = path.substr(pos2 + 1, pos-pos2-1);
		DEBUG_MSG_V("Init ok on image " << name);
	}
	else
		DEBUG_MSG("Error while loading image at path " << path); 
}

void
Image::draw(Bitmap* target)
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
	if(hover==true)
		im.drawTintedScaled(HOVER_TONE, 0, 0, w, h, x, y, scale*w, scale*h, 0);
	else
		im.drawScaled( 0, 0, w, h, x, y, scale* w, scale*h, 0);

	if(borderVisibe)
		al_draw_rectangle(x, y, x + w*scale, y + h*scale, al_map_rgb(255, 0, 0), 3);
}

void
Image::load(string& path)
{
	size_t pos = path.find('.');
	size_t pos2 = path.find_last_of('/');
	size_t pos3 = path.find_last_of('\\');
	if (pos2 == string::npos)
		pos2 = 0;
	if (pos3 != string::npos)
		pos2 = pos3;
	name = path.substr(pos2 + 1, pos);
	im.load(path.c_str());
	scale = w / im.getWidth();
}