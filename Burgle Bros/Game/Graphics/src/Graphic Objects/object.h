#pragma once

#include <Configs.h>
#include <alx.hpp>
#include <queue>
#include "./ObjectInterface.h"
#include "../Animations/Animation.h"
#include "../Observers/observer.h"

using namespace alx;

class Object : public ObjectInterface
{
public:
	// Default constructor
	Object();

	// Constructor that sets the name, the x pos, the y pos, height, width and scale
	Object(string name, int x, int y, int h, int w, double scale);

	// Set an observer to the graphic object
	void setObserver(Observer * obs) { this->obs = obs; };

	// Set position of the object	
	virtual void setPosition(int y, int x)override { this->x = x; this->y = y; };

	// Get position of the object	
	pair<int, int> getPos() { return pair<int, int>(y, x); };

	// Set the size of the object	
	virtual void setSize(int h, int w) { this->h = h; this->w = w; };

	// Get the width of the object
	int getWidth() { return w; };

	// Get the height of the object
	int getHeight() { return h; };

	// Get the size of the object
	pair<int, int> getSize() { return pair<int, int>(h, w); };

	// Set the scale to draw the object 	
	void setScale(double s) { scaleX = s; scaleY = s; };

	// Set the scale for the width
	void setScaleX(double s) { scaleX = s; };

	// Set the scale for the height	
	void setScaleY(double s) { scaleY = s; };

	// Get scale of both axes
	pair<double, double> getScales() { return pair<double, double>(scaleY, scaleX); }

	// Assuming scaleX=scaleY, get only one of them
	double getScale() { return scaleX; };

	// Set object transparency	
	void setAlpha(double a) { alpha = a; };

	// Get object transparency
	double getAlpha() { return alpha; };

	// Set whether the object is visible or not
	void setVisible(bool b) { visible = b; };

	// Get whether the object is visible or not
	bool isVisible() { return visible; };

	// Set whether the object is dragable or not
	void setDragable(bool b) { dragable = b; };

	// Set whether the object is clickable or not
	void setClickable(bool b) { clickable = b; };

	// Set whether the object is hoverable or not
	void setHoverable(bool b) { hoverable = b; hover = false; };

	// Sets the name for the object 
	void setName(string& s) { name = s; };

	// Get the name of the object
	string getName() { return name; };

	// Sets if the border is visible in the object
	virtual void setBorderVisible(bool b) { borderVisibe = b; };

	// Enables the object 
	virtual void enable() { disabled = false; clickable = true; hoverable = true; };

	// Disable the object 
	virtual void disable() { disabled = true; clickable = false; hoverable = false; };

	// Get whether the object is enbaled or not
	virtual bool isEnable() { return !disabled; };

	// Returns whether the object is clicked or not
	virtual bool isClicked() { return clicked; };

	/* SE USAN EN ALGUN LADO?
	virtual void setClickTone(alx::Color)

	//
	virtual alx::Color getNormalTone()

	//
	virtual void setHoverTone(alx::Color)

	//
	virtual alx::Color getHoverTone()*/

	//--------------------------------------------------------------------------
		// Checks if point is over the object (HOVER)	
	virtual bool overYou(int y, int x);

	// Returns the object name if clicked 
	virtual string click(int y, int x);

	// Unclicks the object	
	virtual void unClick(int y, int x);

	// Drag the object	
	virtual void drag(int y, int x);

	// Returns a nullptr it can be overloaded for diferent pruposes
	virtual Bitmap* getTarget() { return nullptr; };

	// Draws the object to the given target 
	virtual void draw(Bitmap* target = nullptr) = 0;

	//
	bool wasInitOk() { return initOk; };

	// To add an animaion call this function with a new animation. When animation ends object deletes it
	void addAnimation(Animation* a);

	// Play one frame of the animation of the object
	void playAnimation();

	// Returns whether the object has an animation or not
	bool hasAnimation() { return !animation.empty(); };

	//
	void deleteAnimation();

	//
	bool animationFinished();

	//
	Animation* getAnimation();

	virtual void flip() {};
	// Checks if a coordinate is inside the object
	bool isInside(int y, int x);

protected:
	Observer * obs;

	// Properties
	bool dragable, clickable, hoverable, borderVisibe, disabled;

	// States
	bool visible, clicked, hover;

	//Properties of the object
	int y, x;  // From uper left corner
	int h, w;
	double alpha;
	double scaleX, scaleY;
	string name;
	queue<Animation*> animation;
	bool initOk;
	
};





