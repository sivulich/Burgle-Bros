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
	coord.col = x;
	coord.row = y;
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


void  Tile::setAlarm(bool b)
{
	alarm = b;
}


void Tile::setCoord(int x, int y)
{
	coord.col = x;
	coord.row = y;
}


int Tile::getSafeNumber()
{
	return isFlipped() ? safeNumber : 0;
}


vector<Tile*>& Tile::getAdjacent()
{
	return adjacent;
}

void Tile::addPlayerAction(Player p, string action) {
	actionNode temp;
	temp.setData(getPos().col, getPos().row, getFloor(), action);
	p.newAction(temp);
}

vector<string>& Tile::getActions(Player p, Coord guardPos, Coord partnerPos) {
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

void Tile::doAction(string action, Player p)
{
	if (action == toString(PEEK))
		peek(p);
	else if (action == toString(MOVE))
		moveTo(p);
}

void Tile::moveTo(Player p) {
	turnUp();				// show the card
	p.removeActionToken();
	p.move(getPos());		// move the player
	updateVisibleFrom(p);	// add the tiles adjacent to the visible from list
	addPlayerAction(p, toString(MOVE));
	DEBUG_MSG("Player moved to the " << toString(getType()) << getPos());
}

void Tile::peek(Player p) {
	p.removeActionToken();
	turnUp();
	addPlayerAction(p, toString(PEEK));
	DEBUG_MSG("Player peeked the " << toString(getType()) << getPos());
}

bool Tile::canMove(Player p) {
	if (p.getActionTokens > 0)
		return true;
	else
		return false;
}

bool Tile::canPeek(Player p) {
	if (p.getActionTokens > 0 && isFlipped() == false)
		return true;
	else
		return false;
}


void Tile::updateVisibleFrom(Player p) {
	p.clearVisibleFrom();		// clear the visible from list
	for (auto i : adjacent)
		p.addVisibleTile(i);	// add the adjacent tiles to the list
}