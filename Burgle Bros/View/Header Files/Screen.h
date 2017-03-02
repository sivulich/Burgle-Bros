#pragma once

#include "Object.h"

class Screen :public Object {
public:
	/** This constructor sets a fixed size to where the background will be drawn with the given offsets
		@param height Height for the transparent container
		@param width Width for the transparent container
		@param pathToBackground Path to the background file
		@param sets fullscreen
	*/
	Screen(int h, int w, string& pathToBackground,bool b);

	/** Draws the screen with all the child objects inside to the display*/
	void draw();

	/** Adds an Object to the parent screen
		@param ob Object to add
	*/
	void addObject(Object* ob) { objects.insert(objects.begin(), ob); };

	/** Removes an object from the parent screen
		@param ob Object to delete
	*/
	bool removeObject(Object* ob) { if (find(objects.begin(), objects.end(), ob) != objects.end()) { objects.erase(find(objects.begin(), objects.end(), ob)); return true; } else return false; };
	
	/** Returns the name of what you pressed within the screen
		@param y Mouse Y coordinate
		@param x Mouse X coordinate
	*/
	string click(int y, int x);

	/** Returns true if the mouse is over an object within the screen
		@param y Mouse Y coordinate
		@param x Mouse X coordinate
	*/
	bool overYou(int y, int x);

	/** Unclicks all the elements in the screen
		@param y Mouse Y coordinate
		@param x Mouse X coordinate
	*/
	void unClick(int y, int x);

	/** Changes the properties of the background
		@param offsetX Offset in the x coordinate for the background
		@param offsetY Offset in the y coordinate for the background
		@param bScale Scale to draw the backGround
	*/
	void backgroundProperties(int offsetX, int offsetY, double bScale) { this->offsetX = offsetX; this->offsetY = offsetY; this->bScale = bScale; };
	
	/** Returns the display for this screen*/
	Display* getDisplay() { return display; };

	/** Returns the bitmap where the screen will be drawn*/
	Bitmap* getTarget() { return toDraw; };

	/** Drags the elements on the screen
		@param y Mouse Y coordinate
		@param x Mouse X coordinate
	*/
	void drag(int y, int x);

	/** Sets the screen to Fullscreen
	*/
	void fullscreen();
	~Screen() { delete toDraw; delete display; };
private:
	Display* display;
	Bitmap* toDraw;
	Bitmap background;
	int offsetX, offsetY; //Used to offset the drawing of the background in the given container
	double bScale; //Used to scale up or down the given background
	vector<Object*> objects;
};