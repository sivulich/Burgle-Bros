#pragma once
#include <utility>
/* Interface implemented for a graphic object. Used by animations to modify an object*/
class ObjectInterface
{
public:
	/** Set position for the object
	@param y Y position
	@param x X position
	*/
	virtual void setPosition(int y, int x) = 0;

	/** Returns the position of the object*/
	virtual std::pair<int, int> getPos() = 0;

	/**  Set the size for the given object
	@param h Height
	@param w Width
	*/



	virtual void setSize(int h, int w) = 0;

	/** Returns the size of the object*/
	virtual std::pair<int, int> getSize() = 0;

	/** Returns the width of the object*/
	virtual int getWidth() = 0;

	/** Returns the height of the object*/
	virtual int getHeight() = 0;



	/** Sets the scale to draw the object
	@param s Scale
	*/
	virtual void setScale(double s) = 0;
	/*	*/
	virtual double getScale() = 0;



	/* Set object transparency */
	virtual void setAlpha(int a) = 0;
	/* Get object transparency */
	virtual int getAlpha() = 0;



	/** Set the visibility of the object in screen*/
	virtual void setVisible(bool b) = 0;

	/** Set whether the object is dragable or not*/
	virtual void setDragable(bool b) = 0;

	/** Set whether the object is clickable or not*/
	virtual void setClickable(bool b) = 0;

	/** Sets if the border is visible in the object*/
	virtual void setBorderVisible(bool b) = 0;
};





