#include "./Card.h"

Card::Card(string& frontPath, string& reversePath) : Image(reversePath)
{
	reverse = frontPath;
	front = reversePath;
	showingReverse = true;
}

Card::Card(string& frontPath, string& reversePath, int xpos, int ypos, int width, int height) : Image(reversePath, xpos, ypos, width, height)
{
	reverse = frontPath;
	front = reversePath;
	showingReverse = true;
}

// Change image keeping size, scales, and position
void Card::flip()
{
	if (showingReverse)
		load(front, true); 
	else
		load(reverse, true);

	showingReverse = !showingReverse;
}

Card::~Card()
{

}
