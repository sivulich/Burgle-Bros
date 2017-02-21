#pragma once
#include "Player.h"
#include "CharacterFactory.h"

Player::Player(string & playerName) {
	name = playerName;
	pos = { 0,0 };
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

void Player::newTurn()
{
	actionTokens = NUMBER_ACTION_TOKENS;
}

void Player::move(Coord newPos)
{
	pos = newPos;
	for (auto& loot : loots)
		loot->setPos(newPos);
}

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
	return distribution(generator);
}
