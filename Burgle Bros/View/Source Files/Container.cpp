
#include "../Header Files/Container.h"

Container::Container(string& path)
{
	background.load(path.c_str());
	h = background.getHeight();
	w = background.getWidth();
	toDraw = new Bitmap(w, h);
	name = string("Container") + to_string(rand());
	if (toDraw != nullptr && toDraw->get() != nullptr)
	{
		if (background.get() != nullptr)
		{
			DEBUG_MSG_V("Initialized container correctly with background " << path<< " and name "<<name);
			initOk = true;
		}
		else
		{
			delete toDraw;
			DEBUG_MSG("Error in container initialization couldnt load background");
		}
	}
	else
		DEBUG_MSG("Error in container initialization couldnt create toDraw");
	offsetX = offsetY = 0;
	bScale = 1;
	onlyClickMe = false;
}
Container::Container(int h, int w)
{
	this->h = h;
	this->w = w;
	offsetX = offsetY = 0;
	bScale = 5;
	toDraw = new Bitmap(w, h);
	background.load("../View/Images/transparent.png");
	if (toDraw != nullptr && toDraw->get() != nullptr)
	{
		if (background.get() != nullptr)
		{
			DEBUG_MSG_V("Initialized container correctly with transparent background");
			initOk = true;
		}
		else
		{
			delete toDraw;
			DEBUG_MSG("Error in container initialization couldnt load background");
		}
	}
	else
		DEBUG_MSG("Error in container initialization couldnt create toDraw");
	onlyClickMe = false;
}

void
Container::draw(Bitmap* target)
{
	if (initOk == true && target != nullptr && target->get() != nullptr)
	{
		toDraw->setTarget();
		DEBUG_MSG_V("Drawing container " << name);
	}
	else if (initOk == true)
	{
		DEBUG_MSG("Error while drawing container " << name << " target was not initialized correctly");
		return;
	}
	else
	{
		DEBUG_MSG("Error while drawing container " << name << ", it was not initialized correctly");
		return;
	}

	
	al_clear_to_color(al_map_rgba_f(0, 0, 0, 0));

	if (background.get() == nullptr)
	{
		al_clear_to_color(al_map_rgba_f(0, 0, 0, 0));
		DEBUG_MSG("Error in container " << name << ", background was not loaded, drawing default transparent background");
	}
		
	else
		background.drawScaled( offsetX, offsetY, background.getWidth(), background.getHeight(), 0, 0,
			bScale*background.getWidth(), bScale*background.getHeight(), 0);
		

	for (int i=objects.size()-1;i>=0;i--)
		objects[i]->draw(toDraw);
	target->setTarget();
	toDraw->drawScaled( 0, 0, w, h, x, y, scale*w, scale*h, 0);

	if (borderVisibe)
		al_draw_rectangle(x, y, x + w*scale, y + h*scale, al_map_rgb(255, 0, 0), 3);
}

string
Container::click(int y, int x)
{
	if (initOk == false)
	{
		DEBUG_MSG("Trying to click container " << name << " when it was not initialized correctly");
		return "";
	}
	DEBUG_MSG_V("Clicking on container " << name);
	
	if (clickable == true && this->x <= x  &&  x <= (this->x + scale*this->w) && this->y <= y && y <= (this->y + scale*this->h))
	{
		if (onlyClickMe == false)
		{
			for (auto& ob : objects)
			{
				if (ob->overYou((y - this->y)*(1.0 / scale), (x - this->x)*(1.0 / scale)) == true)
					return ob->click((y - this->y)*(1.0 / scale), (x - this->x)*(1.0 / scale));
			}
		}
		clicked = true;
		return name;
	}
	return "";
}
void
Container::unClick(int y, int x)
{
	if (initOk == false)
	{
		DEBUG_MSG("Trying to unclick container " << name << " when it was not initialized correctly");
		return;
	}
	DEBUG_MSG_V("Unclicking on container " << name);
	clicked = false;
	for (auto& ob : objects)
		ob->unClick((y - this->y)*(1.0 / scale), (x - this->x)*(1.0 / scale));
}

bool
Container::overYou(int y, int x)
{
	if (initOk == false)
	{
		DEBUG_MSG("Trying to hover container " << name << " when it was not initialized correctly");
		return false;
	}
	DEBUG_MSG_V("Unclicking on container " << name);
	for (auto& ob : objects)
		if (ob->overYou((y - this->y)*(1.0 / scale), (x - this->x)*(1.0 / scale)) == true)
			return true;
	if (this->x <= x  &&  x <= (this->x + scale*this->w) && this->y <= y && y <= (this->y + scale*this->h))
	{
		return true;
	}
	return false;
}

void
Container::drag(int y, int x)
{
	if (initOk == false)
	{
		DEBUG_MSG("Trying to drag on container " << name << " when it was not initialized correctly");
		return ;
	}
	DEBUG_MSG_V("Draging on container " << name);

	
	if (dragable==true &&this->x <= x  &&  x <= (this->x + scale*this->w) && this->y <= y && y <= (this->y + scale*this->h))
	{
		for (auto& ob : objects)
			if (ob->overYou((y - this->y)*(1.0 / scale), (x - this->x)*(1.0 / scale)) == true)
			{
				ob->drag((y - this->y)*(1.0 / scale), (x - this->x)*(1.0 / scale));
				return;
			}
		DEBUG_MSG_V("Draging container " << name);
		this->x = x - scale*w / 2;
		this->y = y - scale*h / 2;
	}
}