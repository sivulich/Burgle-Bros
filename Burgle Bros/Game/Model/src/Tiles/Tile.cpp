#include <Tile.h>


Tile::Tile()
{
	turnDown();
	alarmToken = false;
	crackToken = false;
	crowToken = false;
}

Tile::Tile(tileType t, unsigned floor, unsigned col, unsigned row) 
{
	turnDown();
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
	default_random_engine generator(std::chrono::system_clock::now().time_since_epoch().count());
	uniform_int_distribution<int> distribution(1, 6);
	safeNumber = distribution(generator);
}

void Tile::setAlarm(bool b)
{
	if(b) DEBUG_MSG("The alarm went off at " << getPos());
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
	return p->getActionTokens()>=1 && isAdjacent(p->getPosition());
}

void Tile::enter(PlayerInterface * p)
{
	if (!isFlipped())
		turnUp();
	p->setPosition(getPos());
	updateVisibleFrom(p);
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

bool Tile::doAction(string action, PlayerInterface * p)
{
	////////////////// HACER BIEN RETURN VALUE
	return true;
}

void Tile::updateVisibleFrom(PlayerInterface * player) {
	player->clearVisibleFrom();
	player->addVisibleTile(getPos());
}
