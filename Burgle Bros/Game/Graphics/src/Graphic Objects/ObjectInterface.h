#pragma once
#include <utility>
#include <cmath>
#include <alx.hpp>

// Interface implemented for a graphic object, used by Animation Class to modify an object
class ObjectInterface
{
public:
	// Set position of the object	
	virtual void setPosition(int y, int x) = 0;

	// Get position of the object	
	virtual std::pair<int, int> getPos() = 0;

	// Set the size of the object	
	virtual void setSize(int h, int w) = 0;

	// Get the width of the object
	virtual int getWidth() = 0;

	// Get the height of the object
	virtual int getHeight() = 0;

	// Get the size of the object
	virtual std::pair<int, int> getSize() = 0;

	// Set the scale to draw the object 	
	virtual void setScale(double s) = 0;

	// Set the scale for the width
	virtual void setScaleX(double s) = 0;

	// Set the scale for the height	
	virtual void setScaleY(double s) = 0;

	// Get scale of both axes
	virtual std::pair<double, double> getScales() = 0;

	// Assuming scaleX=scaleY, get only one of them
	virtual double getScale() = 0;

	// Set object transparency	
	virtual void setAlpha(double a) = 0;

	// Get object transparency
	virtual double getAlpha() = 0;

	// Set whether the object is visible or not
	virtual void setVisible(bool b) = 0;

	// Get whether the object is visible or not
	virtual bool isVisible() = 0;

	// Set whether the object is dragable or not
	virtual void setDragable(bool b) = 0;

	// Set whether the object is clickable or not
	virtual void setClickable(bool b) = 0;

	// Set whether the object is hoverable or not
	virtual void setHoverable(bool b) = 0;

	// Only for TileCard and FlipAnimation!
	virtual void flip() = 0;
};





