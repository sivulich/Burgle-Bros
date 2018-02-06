#include <Tile.h>


Tile::Tile()
{
	turnDown();
	alarmToken = false;
	crackToken = false;
	crowToken = false;
	hackerHere = false;
}

Tile::Tile(tileType t, unsigned floor, unsigned col, unsigned row)
{
	turnDown();

	type = t;
	coord.col = col;
	coord.row = row;
	coord.floor = floor;
	crowToken = false;
	crackToken = false;
	stairToken = false;
	alarmToken = false;
	hackerHere = false;
	hasGuard = false;
	hackToken = 0;
	northWall = false;
	eastWall = false;
	southWall = false;
	westWall = false;
}

void Tile::setLoot(Loot * l)
{
	loot.push_back(l);
	notify();
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
/*
bool Tile::hasEastWall()
{
	return coord.col < 3 && !isAdjacent(Coord(coord.floor, coord.col + 1, coord.row));
}
bool Tile::hasWestWall()
{
	return coord.col > 0 && !isAdjacent(Coord(coord.floor, coord.col - 1, coord.row));
}
bool Tile::hasNorthWall()
{
	return coord.row > 0 && !isAdjacent(Coord(coord.floor, coord.col, coord.row - 1));
}
bool Tile::hasSouthWall()
{
	return coord.row < 3 && !isAdjacent(Coord(coord.floor, coord.col, coord.row + 1));
}*/


void Tile::turnUp()
{
	default_random_engine generator((unsigned int)std::chrono::system_clock::now().time_since_epoch().count());
	uniform_int_distribution<int> distribution(1, 6);
	safeNumber = distribution(generator);
	BaseCard::turnUp();
	notify();
}

void Tile::setAlarm(bool b)
{
	if (b) DEBUG_MSG("The alarm went off at " << getPos());
	else  DEBUG_MSG("The alarm was shut down at " << getPos());
	alarmToken = b;
	notify();
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

vector<Coord> Tile::getAdjacent()
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

bool Tile::canMove(PlayerInterface * player) {
	return true;
 }
void Tile::enter(PlayerInterface * p)
{
	if (!isFlipped())
		turnUp();
	updateVisibleFrom(p);
	DEBUG_MSG("Player moved to the " << toString(getType()) << " at " << getPos());
	notify();
}

vector<string> Tile::getActions(PlayerInterface * p)
{

	vector<string> actions;
	if (!p->isThrowingDices())
	{
		actions.push_back("PEEK");
		actions.push_back("MOVE");
	}
	return actions;
}

bool Tile::doAction(string action, PlayerInterface * p)
{
	////////////////// HACER BIEN RETURN VALUE
	return true;
}

void Tile::updateVisibleFrom(PlayerInterface * player) {
	player->clearVisibleFrom();
	player->addVisibleTile(getPos());
}
