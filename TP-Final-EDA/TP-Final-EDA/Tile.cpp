#include "Tile.h"



void Tile::setAdjacent(Coord c)
{
	adjacent.push_back(c);
};


void Tile::deleteAdjacent(Coord b)
{
	adjacent.erase(find(adjacent.begin(), adjacent.end(), b));
}


bool Tile::isAdjacent(Coord t)
{
	return find(adjacent.begin(), adjacent.end(), t) != adjacent.end();
}

/**
	Return true if the tile is from the given type
*/
bool Tile::is(tileType t)
{
	return t == getType();
}


Tile::Tile()
{
	turnDown();
	alarm = false;

}

Tile::Tile(unsigned floor, unsigned col, unsigned row)
{
	alarm = false;
	coord.col = col;
	coord.row = row;
	coord.floor = floor;
}

void Tile::peek(Player p)
{
	if(p.getActionTokens > 0)
		turnUp();
}

bool Tile::moveTo(Player p)
{

	return true;
}


tileType Tile::getType()
{
	return getType();;
}


bool Tile::hasAlarm()
{
	return alarm;
}


void Tile::turnUp()
{
	BaseCard::turnUp();
	default_random_engine generator;
	uniform_int_distribution<int> distribution(1, 6);
	safeNumber = distribution(generator);
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


bool Tile::doAction(string action, Player p)
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

vector<string>& Tile::getActions(Player p, Coord guardPos, Coord partnerPos) {
	
}

void Tile::addPlayerAction(Player p, string action) {
	actionNode temp;
	temp.setData(getCoord().first, getCoord().second, getFloor(), action);
	p.actions.push_front(temp);
}