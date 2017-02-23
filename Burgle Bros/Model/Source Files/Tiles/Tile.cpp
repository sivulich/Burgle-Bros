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

void Tile::addPlayerAction(Player p, string action) {
	actionNode temp;
	temp.setData(col(), row(), floor(), action);
	p.newAction(temp);
}

vector<string>& Tile::getActions(Player p, Coord guardPos, Coord partnerPos)
{
	actions.clear();
	if (isAdjacent(p.getPosition()))	//if the player is adjacent to the tile, get the list of actions
	{
		if (canPeek(p))	//Check if the player can peek 
			actions.push_back(toString(PEEK));
		if (canMove(p))	//Check if the player can move
			actions.push_back(to_string(MOVE));
	}
	return actions;
}

void Tile::doAction(string action, Player p, Coord guardPos, Coord partnerPos)
{
	p.removeActionToken();
	if (action == toString(PEEK))
		peek(p);
	else if (action == toString(MOVE)) {
		if (isFlipped() == false)	turnUp();
		enterTile(p);
	}
}

void Tile::enterTile(Player p) {
	p.move(getPos());		// move the player
	updateVisibleFrom(p);	// add the tiles adjacent to the visible from list
	addPlayerAction(p, toString(MOVE));
	DEBUG_MSG("Player moved to the " << toString(getType()) << getPos());
}

void Tile::peek(Player p) {
	turnUp();
	addPlayerAction(p, toString(PEEK));
	DEBUG_MSG("Player peeked the " << toString(getType()) << getPos());
}

bool Tile::canMove(Player p) {
	if (p.getActionTokens() > 0)
		return true;
	else
		return false;
}

bool Tile::canPeek(Player p) {
	if (p.getActionTokens() > 0 && isFlipped() == false)
		return true;
	else
		return false;
}


void Tile::updateVisibleFrom(Player p) {
	p.clearVisibleFrom();		// clear the visible from list
	for (auto i : adjacent)
		p.addVisibleTile(i);	// add the adjacent tiles to the list
}