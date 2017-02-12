#pragma once

#include "object.h"
class Screen :public object {
public:
	Screen(int h, int w, string& pathToBackground);
	void draw();
	void addObject(object* ob) { objects.insert(objects.begin(), ob); };
	bool removeObject(object* ob) { if (find(objects.begin(), objects.end(), ob) != objects.end()) { objects.erase(find(objects.begin(), objects.end(), ob)); return true; } else return false; };
	string click(int y, int x);
	bool overYou(int y, int x);
	void unClick();
	void backgroundProperties(int offsetX, int offsetY, double bScale) { this->offsetX = offsetX; this->offsetY = offsetY; this->bScale = bScale; };
	ALLEGRO_DISPLAY* getDisplay() { return display; };
private:
	ALLEGRO_DISPLAY* display;
	ALLEGRO_BITMAP* toDraw;
	ALLEGRO_BITMAP* background;
	int offsetX, offsetY; //Used to offset the drawing of the background in the given container
	double bScale; //Used to scale up or down the given backGround
	bool initOk;
	vector<object*> objects;
};