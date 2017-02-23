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

void Player::resetStealthTokens()
{
	actionTokens = NUMBER_ACTION_TOKENS;
}

void Player::move(Tile* newPos)
{
	if (newPos->canMove(this))
		newPos->moveTo(this);
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
}

int  Player::getStealthTokens()
{
	return stealthTokens;
}

int  Player::getActionTokens()
{
	return actionTokens;
}

void Player::newAction(actionNode node) {
	actions.push_front(node);
}
int Player::throwDice()
{
	default_random_engine generator;
	uniform_int_distribution<int> distribution(1, 6);
	int dieValue = distribution(generator);
	dice.push_back(dieValue);
	return dieValue;
}

void Player::addLoot(Loot * l) { loots.push_back(l); };


void Player::clearVisibleFrom() { visibleFrom.clear(); };

void Player::addVisibleTile(Coord tile) { visibleFrom.push_back(tile); };

vector <Coord>& Player::getVisibleFrom() { return visibleFrom; };



string Player::getName() { return name; };
characterType Player::getCharacterType() { return character->getType(); };