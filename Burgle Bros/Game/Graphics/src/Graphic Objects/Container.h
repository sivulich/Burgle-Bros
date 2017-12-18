#pragma once

#include "Object.h"
/*Class used to store graphic objets in a region, all objects will be drawn with its position relative to the container position
* and with the parents scale (pScale*cScale*size)*/

class Container :public Object
{
public:
	/** This constructor should be used when setting a background to fill the container
		@param path Path to the background
	*/
	Container(string& path);

	/** This constructor sets a fixed size for the container
		@param height Height for the transparent container
		@param width Width for the transparent container
	*/
	Container(int height, int width, string name);

	/** Draws the container with all the child objects inside
		@param target Parent bitmap to draw on
	*/
	void draw(Bitmap* target);

	/** Sets the background for the given container
		@param path Path to the background
	*/
	void setBackground(string& path) { background.load(path.c_str()); if (background.get() == nullptr) initOk = false;  };

	/** Changes the properties of the background 
		@param offsetX Offset in the x coordinate for the background
		@param offsetY Offset in the y coordinate for the background
		@param bScale Scale to draw the backGround
	*/
	void backgroundProperties(int offsetX, int offsetY, double bScale) { this->offsetX = offsetX; this->offsetY = offsetY; this->bScale = bScale; };

	/** Adds an Object to the container
		@param ob Object to add
	*/
	void addObject(Object* ob) { objects.insert(objects.begin(),ob); };

	/** Removes an object from the parent container
		@param ob Object to delete
	*/
	bool removeObject(Object* ob) { if (find(objects.begin(), objects.end(), ob) != objects.end()) { objects.erase(find(objects.begin(), objects.end(), ob)); return true; } else return false; }
	
	/** Sets the size in pixels, within the parent container
		@param h Height
		@param w Width
	*/
	void setSize(int h, int w) { this->h = h; this->w = w; };

	/**
		Set border visible of container and all its elements
	*/
	virtual void setBorderVisible(bool b)override;

	/** Returns the target to draw in this container*/
	Bitmap* getTarget() { return toDraw; };

	/** Returns the name of what you pressed, can be container or Object within the container
		@param y Mouse Y coordinate
		@param x Mouse X coordinate
	*/
	string click(int y, int x);

	/** Returns true if the mouse is over the container
		@param y Mouse Y coordinate
		@param x Mouse X coordinate
	*/
	bool overYou(int y, int x);

	/** Unclicks all the elements in the container
		@param y Mouse Y coordinate
		@param x Mouse X coordinate
	*/
	void unClick(int y, int x);

	/** Drags the container, or the objects inside of it
		@param y Mouse Y coordinate
		@param x Mouse X coordinate
	*/
	void drag(int y, int x);

	/**
		Set if the container overrides the click function of the objects inside it
	*/
	void onlyMe(bool b) { onlyClickMe = b; };
	
	/**
	Set if the container overrides the click function of the objects inside it
	*/
	void setOnlyChildClickable(bool b) { dontClickMe = b; };

	/**
		Return true if contains given object
	*/
	bool contains(Object* ob) { if (find(objects.begin(), objects.end(), ob) != objects.end()) return true; return false; };

	/*Clear the object list*/
	void clear() { objects.clear(); };

	/**
		Print name of all objects
	*/
	void printContent();

	~Container() { delete toDraw; };

private:
	/*Background info*/
	Bitmap background;
	int offsetX, offsetY; //Used to offset the drawing of the background in the given container
	double bScale; //Used to scale up or down the given backGround

	/**/
	Bitmap* toDraw;

	/*Container properties*/
	bool onlyClickMe; //
	bool dontClickMe; //

	/*Child objects for the given container*/
	vector<Object*> objects;
};