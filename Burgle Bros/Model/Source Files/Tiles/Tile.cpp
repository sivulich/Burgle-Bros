#include "../../Header Files/Tiles/Tile.h"


Tile::Tile()
{
	turnDown();
	alarmToken = false;
	crackToken = false;
	crowToken = false;
}

Tile::Tile(tileType t, unsigned floor, unsigned col, unsigned row) 
{
	alarmToken = false;
	type = t;
	coord.col = col;
	coord.row = row;
	coord.floor = floor;
	crowToken = false;
	crackToken = false;
}


void Tile::setLoot(Loot * l)
{
	loot.push_back(l);
}

void Tile::addAdjacent(Coord c)
{
	adjacent.push_back(c);
};

void Tile::deleteAdjacent(Coord b)
{
	adjacent.erase(find(adjacent.begin(), adjacent.end(), b));
}

bool Tile::isAdjacent(Coord b)
{
	return find(adjacent.begin(), adjacent.end(), b) != adjacent.end();
}

bool Tile::is(tileType t)
{
	return t == getType();
}

tileType Tile::getType()
{
	return type;
}

bool Tile::hasAlarm()
{
	return alarmToken;
}

bool Tile::hasLoot()
{
	return loot.empty() ? false : true;
}


void Tile::turnUp()
{
	BaseCard::turnUp();
	default_random_engine generator;
	uniform_int_distribution<int> distribution(1, 6);
	safeNumber = distribution(generator);
}

void Tile::setAlarm(bool b)
{
	alarmToken = b;
	notify();
}

void Tile::setCoord(Coord c)
{
	coord = c;
}

int Tile::getSafeNumber()
{
	return isFlipped() ? safeNumber : 0;
}

vector<Coord> Tile::whereCanIMove()
{
	return adjacent;
}

vector<Coord> Tile::whereCanIPeek()
{
	return adjacent;
}

Coord Tile::getPos() { return coord; };

int Tile::floor() { return coord.floor; };

int Tile::col() { return coord.col; };

int Tile::row() { return coord.row; };

void Tile::peek()
{
	turnUp();
	DEBUG_MSG("Player peeked the " << toString(getType()) << " at " << getPos());
	notify();
}

bool Tile::canMove(PlayerInterface * p)
{
	return isAdjacent(p->getPosition());
}

void Tile::enterTile(PlayerInterface * p)
{
	if (!isFlipped())
		turnUp();
	p->updateVisibleFrom();
	DEBUG_MSG("Player moved to the " << toString(getType()) << " at " << getPos());
	notify();
}

vector<string> Tile::getActions(PlayerInterface * p)
{
	vector<string> actions;
	actions.push_back("PEEK");
	actions.push_back("MOVE");
	return actions;
}

void Tile::doAction(string action, PlayerInterface * p)
{

}


