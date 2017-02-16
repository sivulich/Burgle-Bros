#pragma once
#include "Object.h"

class Textbox :public Object {
public:
	Textbox(int x, int y, string& path, int fSize,int max);
	void draw(Bitmap* target);
	string click(int y, int x);
	void unClick(int y, int x);
	void fitText(bool b) { fitToBox = b; };
	~Textbox() { delete font; delete titilate; };
private:
	EventQueue queue;
	Event event;
	Font* font;
	string buffer;
	bool fitToBox;
	unsigned long long count;
	Timer* titilate;
	int size;
};
