#include "Tile.h"

Tile::Tile()
{
	turnDown();
	alarm = false;

}

Tile::Tile(int x, int y)
{
	turnDown();
	alarm = false;
	coord.first = x;
	coord.second = y;
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

void Tile::flip()
{
	turnUp();
	default_random_engine generator;
	uniform_int_distribution<int> distribution(1, 6);
	safeNumber = distribution(generator);
}
bool Tile::isFlipped()	
{
//	return isFlipped();
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