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
	tileCard.setType(t);
}

void Tile::peek(Player p)
{
	if(p.getActionTokens > 0)
		flipped = true;


}

bool Tile::moveTo(Player p)
{

	return true;
}


tileType Tile::getType()
{
	return tileCard.getType();;
}


bool Tile::hasAlarm()
{
	return alarm;
}

void Tile::flip()
{
	flipped = true;
	default_random_engine generator;
	uniform_int_distribution<int> distribution(1, 6);
	safeNumber = distribution(generator);
}
bool Tile::isFlipped()
{
	return flipped;
}


void  Tile::setAlarm(bool b)
{
	alarm = b;
}


void Tile::setCoord(int x, int y)
{
	coord.first = x;
	coord.second = y;
}

/**
*/
vector<string>& Tile::getActions(Player p, Coord guardPos, Coord partnerPos)
{
	tileCard.actions.clear();
	if (p.getActionTokens() > 0 && flipped == false)
		tileCard.actions.push_back("PEEK");


	return tileCard.actions;
}

bool Tile::doAction(string Action, Player p)
{
	return true;
}


int Tile::getSafeNumber()
{
	return isFlipped() ? safeNumber : 0;
}


vector<Tile*>& Tile::getAdjacent()
{
	return adjacent;
}
