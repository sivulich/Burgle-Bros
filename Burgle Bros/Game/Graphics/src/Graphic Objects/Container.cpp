
#include "./Container.h"

Container::Container(string& path)
{
	background.load(path.c_str());
	h = background.getHeight();
	w = background.getWidth();
	toDraw = new Bitmap(w, h);
	offsetX = offsetY = 0;
	bScale = 1;
	onlyClickMe = false;
	dontClickMe = false;
	// Por que el nombre rand?
	name = string("Container") + to_string(rand());

	if (toDraw != nullptr && toDraw->get() != nullptr)
	{
		if (background.get() != nullptr)
		{
			DEBUG_MSG_V("Initialized container correctly with background " << path << " and name " << name);
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

}
Container::Container(int h, int w, string name)
{
	// Lo comento, al pedo un fondo transparente
	//background.load("../Game/Graphics/Images/transparent.png");
	this->h = h;
	this->w = w;
	offsetX = offsetY = 0;

	onlyClickMe = false;
	dontClickMe = false;

	this->name = name;

	toDraw = new Bitmap(w, h);
	if (toDraw != nullptr && toDraw->get() != nullptr)
	{
		initOk = true;
	}
	else DEBUG_MSG("Error in container " << name << " initialization couldnt create toDraw bitmap");

}

void Container::draw(Bitmap* target)
{
	if (initOk == true)
	{
		if (visible)
		{
			if (target != nullptr && target->get() != nullptr)
			{
				toDraw->setTarget();
				al_clear_to_color(al_map_rgba_f(0, 0, 0, 0));

				if (background.get() != nullptr)
					background.drawScaled(offsetX, offsetY, background.getWidth(), background.getHeight(), 0, 0, w*scaleX, h*scaleY, 0);

				for (int i = objects.size() - 1; i >= 0; i--)
					objects[i]->draw(toDraw);


				// Draw toDraw bitmap in target bitmap
				target->setTarget();
				toDraw->drawScaled(0, 0, w, h, x, y, scaleX*w, scaleY*h, 0);

				if (borderVisibe)
					al_draw_rectangle(x, y, x + w*scaleX, y + h*scaleY, al_map_rgb(255, 0, 0), 3);

			}
			else DEBUG_MSG("Error while drawing container " << name << " target was not initialized correctly");
		}
	}
	else DEBUG_MSG("Error while drawing container " << name << ", it was not initialized correctly");

}

string Container::click(int y, int x)
{
	if (initOk == false)
	{
		DEBUG_MSG("Trying to click container " << name << " when it was not initialized correctly");
		return "";
	}
	DEBUG_MSG_V("Clicking on container " << name);

	if (clickable == true && isInside(y, x)&& visible==true)
	{
		if (onlyClickMe == false)
		{
			for (auto& ob : objects)
			{
				if (ob->overYou((y - this->y) / scaleY, (x - this->x) / scaleX) == true)
				{
					string s = ob->click((y - this->y) / scaleY, (x - this->x) / scaleX);
					if (s == string("Not Clickable"))
						continue;
					else return s;
				}
			}
		}
		else
		{
			clicked = true;

			if (dontClickMe == false)
				return name;
			else
				return "";
		}

	}
	return "";
}

void Container::unClick(int y, int x)
{
	if (initOk == false)
	{
		DEBUG_MSG("Trying to unclick container " << name << " when it was not initialized correctly");
		return;
	}
	DEBUG_MSG_V("Unclicking on container " << name);
	clicked = false;
	for (auto& ob : objects)
		ob->unClick((y - this->y)*(1.0 / scaleY), (x - this->x)*(1.0 / scaleX));
}

bool Container::overYou(int y, int x)
{
	if (visible == false)
		return false;
	if (initOk == false)
	{
		DEBUG_MSG("Trying to hover container " << name << " when it was not initialized correctly");
		return false;
	}
	DEBUG_MSG_V("Unclicking on container " << name);
	for (auto& ob : objects)
		if (ob->overYou((y - this->y)*(1.0 / scaleY), (x - this->x)*(1.0 / scaleX)) == true)
			return true;

	// Probando hacer mas rapida la interfaz
	if (hoverable == true && this->x <= x  &&  x <= (this->x + scaleX*this->w) && this->y <= y && y <= (this->y + scaleY*this->h))
	{
		return true;
	}
	return false;
}

void Container::drag(int y, int x)
{
	if (initOk == false)
	{
		DEBUG_MSG("Trying to drag on container " << name << " when it was not initialized correctly");
		return;
	}
	DEBUG_MSG_V("Draging on container " << name);


	if (dragable == true && this->x <= x  &&  x <= (this->x + scaleX*this->w) && this->y <= y && y <= (this->y + scaleY*this->h))
	{
		for (auto& ob : objects)
			if (ob->overYou((y - this->y)*(1.0 / scaleY), (x - this->x)*(1.0 / scaleX)) == true)
			{
				ob->drag((y - this->y)*(1.0 / scaleY), (x - this->x)*(1.0 / scaleX));
				return;
			}
		DEBUG_MSG_V("Draging container " << name);
		this->x = x - scaleX*w / 2;
		this->y = y - scaleY*h / 2;
	}
}

void Container::printContent()
{
	for (auto& ob : objects)
		DEBUG_MSG(ob->getName() << " ");
}

void Container::setBorderVisible(bool b)
{
	borderVisibe = b;
	for (auto& ob : objects)
		ob->setBorderVisible(b);
}
