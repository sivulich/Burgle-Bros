#include "../../Header Files/Tiles/Tile.h"


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


void Tile::setAdjacent(Coord c)
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
	return alarm;
}

bool Tile::hasLoot()
{
	return loot == nullptr ? false : true;
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


void Tile::setCoord(unsigned floor, unsigned col, unsigned row)
{
	coord.col = col;
	coord.row = row;
	coord.floor = floor;
}


int Tile::getSafeNumber()
{
	return isFlipped() ? safeNumber : 0;
}


vector<Coord>& Tile::getAdjacents()
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
}

bool Tile::canMove(PlayerInterface * p)
{
		return true;
}

void Tile::enterTile(PlayerInterface * p)
{
	if (!isFlipped())
		turnUp();
	DEBUG_MSG("Player moved to the " << toString(getType()) << " at " << getPos());
}

vector<string>& Tile::getActions(PlayerInterface * p)
{
	vector<string> actions;
	if (this->isAdjacent(p->getPosition()))
		actions.push_back("PEEK");
	return actions;
}

void Tile::doAction(string action, PlayerInterface * p) {

}



/////////////////////////////////////////////////////
/////////////////////////////////////////////////////
/*
bool Tile::canPeek(Player p) {
if (p.getActionTokens() > 0 && isFlipped() == false)
return true;
else
return false;
}
*/
