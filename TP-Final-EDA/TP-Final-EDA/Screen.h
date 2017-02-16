#pragma once

#include "Object.h"

class Screen :public Object {
public:
	Screen(int h, int w, string& pathToBackground);
	void draw();
	void addObject(Object* ob) { objects.insert(objects.begin(), ob); };
	bool removeObject(Object* ob) { if (find(objects.begin(), objects.end(), ob) != objects.end()) { objects.erase(find(objects.begin(), objects.end(), ob)); return true; } else return false; };
	string click(int y, int x);
	bool overYou(int y, int x);
	void unClick(int y, int x);
	void backgroundProperties(int offsetX, int offsetY, double bScale) { this->offsetX = offsetX; this->offsetY = offsetY; this->bScale = bScale; };
	Display* getDisplay() { return display; };
	void drag(int y, int x);
	~Screen() { delete toDraw; delete display; };
private:
	Display* display;
	Bitmap* toDraw;
	Bitmap background;
	int offsetX, offsetY; //Used to offset the drawing of the background in the given container
	double bScale; //Used to scale up or down the given backGround
	bool initOk;
	vector<Object*> objects;
};