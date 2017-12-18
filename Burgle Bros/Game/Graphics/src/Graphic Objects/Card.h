#pragma once

#include "./Image.h"

// A card is an image which adds the option to flip and show front or reverse
class Card : public Image
{
public:
	Card(string& frontPath, string& reversePath);
	Card(string& frontPath, string& reversePath, int xpos, int ypos, int width, int height);

	void flip();
	~Card();

private:
	string reverse;
	string front;
	bool showingReverse;
};

