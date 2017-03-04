#pragma once
#include <utility>
#include <cmath>
#include "ALX\alx.hpp"
/* Interface implemented for a graphic object. Used by animations to modify an object*/
class ObjectInterface
{
public:
	/** Set position for the object
	@param y Y position
	@param x X position
	*/
	virtual void setPosition(int y, int x) {};

	/** Returns the position of the object*/
	virtual std::pair<int, int> getPos() { return std::pair<int, int>(0, 0); };

	/**  Set the size for the given object
	@param h Height
	@param w Width
	*/



	virtual void setSize(int h, int w) {};

	/** Returns the size of the object*/
	virtual std::pair<int, int> getSize() { return std::pair<int, int>(0, 0); };

	/** Returns the width of the object*/
	virtual int getWidth() { return 0; };

	/** Returns the height of the object*/
	virtual int getHeight() { return 0; };



	/** Sets the scale to draw the object
	@param s Scale
	*/
	virtual void setScale(double s) {};
	/** Sets the scale for the width
	@param s scaleX
	*/
	virtual void setScaleX(double s) {};

	/** Sets the scale for the heught
	@param s scaleY
	*/
	virtual void setScaleY(double s) {};

	virtual std::pair<double, double> getScales() {return std::pair<int, int>(0, 0);};
	/*	*/
	virtual double getScale() { return 0; };

	virtual void setNormalTone(alx::Color) {};
	virtual void setHoverTone(alx::Color) {};

	virtual alx::Color getHoverTone() { return alx::Color(0); };
	virtual alx::Color getNormalTone() { return alx::Color(0); };



	/** Set the visibility of the object in screen*/
	virtual void setVisible(bool b) {};

	/** Set whether the object is dragable or not*/
	virtual void setDragable(bool b) {};

	/** Set whether the object is clickable or not*/
	virtual void setClickable(bool b) {};

	/** Sets if the border is visible in the object*/
	virtual void setBorderVisible(bool b) {};
};





