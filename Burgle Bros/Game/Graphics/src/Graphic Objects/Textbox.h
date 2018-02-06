#pragma once
#include "Object.h"

class Textbox :public Object {
public:
	/** Initializes the textbox
	    @param x X coordinate in the parent
	    @param y Y coordinate in the parent
	    @param path Path to the font to load
	    @param fSize Font size in pixels
	    @param max Max letters to input in this textbox
	*/
	Textbox(int x, int y, string& path, int fSize,int max);
	/** Initializes the textbox
	@param x X coordinate in the parent
	@param y Y coordinate in the parent
	@param path Path to the font to load
	*/
	Textbox::Textbox(int x, int y, int w, int h, string& path);
	/** Draws the textbox to the target
		@param target Target to draw the textbox in
	*/

	void setMax(int max);

	void draw(Bitmap* target);
	/** If the textbox is clicked it will return its name
		@param y Mouse y coordinate
		@param x Mouse x coordinate
	*/
	string click(int y, int x);
	void click();
	/** Tests whether to unclick or not
		@param y Mouse y coordinate
		@param x Mouse x coordinate
	*/
	void unClick(int y, int x);
	void unClick();
	/** If over the textbox return true
		@param y Mouse y coordinate
		@param x Mouse x coordinate
	*/
	bool overYou(int y, int x);
	/** If true, lets you input text until the textbox is full
	*/
	void fitText(bool b) { fitToBox = b; };

	string getText();
	void clear() { buffer.clear(); curPos = 0; };
	void setFontColor(Color c) { fontColor = c; };
	void setBoxColor(Color c) { boxColor = c; };

	~Textbox() { delete font; delete titilate; };
private:
	EventQueue queue;
	Event event;
	Font* font;
	string buffer;
	Color fontColor, boxColor;
	unsigned long long count;
	bool fitToBox;
	Timer* titilate;
	int size;
	int curPos;
};
