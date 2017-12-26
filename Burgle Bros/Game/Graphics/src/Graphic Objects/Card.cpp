#include "./Card.h"

Card::Card(string& frontPath, string& reversePath,bool flipped) : Image(reversePath)
{
	reverse = frontPath;
	front = reversePath;
	if (flipped == true)
	{
		showingReverse = false;
		flip();
	}
	else
		showingReverse = true;

}

Card::Card(string& frontPath, string& reversePath, int xpos, int ypos, int width, int height, bool flipped) : Image(reversePath, xpos, ypos, width, height)
{
	reverse = reversePath;
	front = frontPath;
	if (flipped == true)
	{
		showingReverse = false;
		flip();
	}
	else
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
