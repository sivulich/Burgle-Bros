#pragma once

#include <allegro5\allegro.h>
#include <allegro5\allegro_image.h>
#include <allegro5\bitmap.h>
#include "Configs.h"
class object {
public:
	object();
	virtual void draw();
	void setPosition(int x, int y) { this->x = x; this->y = y; };
	void setVisible(bool b) { visible = b; };
	void setDragable(bool b) { dragable = b; };
	void setClickable(bool b) { clickable = b; };
	void over(bool b) { hover = true; };
	void setName(string& s) { name = s; };
	pair<int, int> getPos() { pair<int, int> pos(x, y); return pos; };
protected:
	bool dragable, visible,clickable,hover;
	int x, y;
	string name;
};

class container:public object {
public:
	void draw();
	void setBackground(ALLEGRO_BITMAP* b);
	void addObject(object* ob) { objects.push_back(ob); };
	void setSize(int h, int w) { this->h = h; this->w = w; };
	bool overYou(int x, int y);
	string click(int x, int y);
private:
	ALLEGRO_BITMAP* background;
	int h, w;
	vector<object*> objects;
};