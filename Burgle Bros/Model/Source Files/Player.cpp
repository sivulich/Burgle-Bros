#pragma once
#include "../Header Files/Player.h"
#include "../Header Files/Characters/CharacterFactory.h"

Player::Player(string & playerName) {
	name = playerName;
	//actionTokens = 0; POR QUE LOS SETEABAN EN 0???????????????'
	//stealthTokens = 0;
	stealthTokens = NUMBER_STEALTH_TOKENS;
	actionTokens = NUMBER_ACTION_TOKENS;
}

void Player::setName(string & playerName)
{
	name = playerName;
}

void Player::setCharacter(characterType type)
{
	character = CharacterFactory().newCharacter(type);
}

void Player::resetActionTokens()
{
	actionTokens = NUMBER_ACTION_TOKENS;
}

bool Player::move(Tile * newTile)
{
	if (newTile->isAdjacent(getPosition()))		//if the tile is adjacent to the player's position 
	{
		removeActionToken();
		if (newTile->canMove(this)) {
			changePos(newTile->getPos());
			setVisibleFrom(newTile->getAdjacents());		// add the new position's adjacent tile coordinates
			newAction(toString(MOVE), newTile->getPos());
			newTile->enterTile(this);					// and enter the tile
			return true;
		}
	}
	
	return false;
}

bool Player::peek(Tile * newTile) {
	removeActionToken();
	newAction(toString(PEEK), newTile->getPos());
	newTile->peek();
}

Coord Player::getPosition()
{
	return pos;
};

void Player::removeStealthToken()
{
	if (stealthTokens > 0)
		stealthTokens--;
}

void Player::removeActionToken() {
	if (actionTokens > 0)
		actionTokens--;
	else
		DEBUG_MSG("UNEXPECTED ERROR. COULD NOT REMOVE ACTION TOKEN.");
}

int  Player::getStealthTokens()
{
	return stealthTokens;
}

int  Player::getActionTokens()
{
	return actionTokens;
}

void Player::newAction( string action, Coord tile) {
	actionNode temp;
	temp.setData(tile.col, tile.row, tile.floor, action);
	actions.push_back(temp);
}
int Player::throwDice()
{
	default_random_engine generator;
	uniform_int_distribution<int> distribution(1, 6);
	unsigned int temp= distribution(generator);
	dice.push_back(temp);
	return temp;
}

void Player::addLoot(Loot * l) { loots.push_back(l); };

bool Player::hasLoot() {
	if (loots.empty())
		return false;
	else
		return true;
}

void Player::clearVisibleFrom() { visibleFrom.clear(); };

void Player::addVisibleTile(Coord tile) { visibleFrom.push_back(tile); };

vector <Coord>& Player::getVisibleFrom() { return visibleFrom; };

void Player::setVisibleFrom(vector <Coord> newCoords) {
	clearVisibleFrom();			// erase the previous coordinates
	for (auto i : newCoords)
		addVisibleTile(i);		// add the new visible from tile coordinates
}

string Player::getName() { return name; };
characterType Player::getCharacterType() { return character->getType(); };