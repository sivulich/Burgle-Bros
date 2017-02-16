#include "Tile.h"

Tile::Tile()
{
	flipped = false;
	alarm = false;

}

Tile::Tile(int x, int y, tileType t)
{
	flipped = false;
	alarm = false;
	coord.first = x;
	coord.second = y;
	type = t;
}


/**
*/
void Tile::peek(Player p)
{
	flipped = true;


}

/**
*/
bool Tile::moveTo(Player p)
{

	return true;
}

/**
*/
tileType Tile::getType()
{
	return type;
}

/**
*/
bool Tile::hasAlarm()
{
	return alarm;
}

/**
*/
bool Tile::isFlipped()
{
	return true;
}

/**
*/
void  Tile::setAlarm(bool b)
{

}

/**
*/
void Tile::setCoord(int x, int y)
{
	coord.first = x;
	coord.second = y;
}

/**
*/
vector<string>& Tile::getActions(Player p)
{
	return actions;
}

/**
*/
bool Tile::doAction(string Action, Player p)
{
	return true;
}

/**
*/
int Tile::getSafeNumber()
{
	return safeNumber;
}

/**

*/
vector<Tile*>& Tile::getAdjacent()
{
	return adjacent;
}
