#pragma once
#include "Player.h"

Player::Player(string & playerName) {
	name = playerName;
	pos = { 0,0 };
	actionTokens = 0;
	stealthTokens = 0;
}

void Player::setName(string & playerName)
{
	name = playerName;
}

void Player::setId(characterID character) {
	id = character;
	stealthTokens = NUMBER_STEALTH_TOKENS;
	actionTokens = NUMBER_ACTION_TOKENS;
}

void Player::newTurn()
{
	actionTokens = NUMBER_ACTION_TOKENS;
}

void Player::move(Coord newPos)
{
	pos = newPos;
	for (auto& loot : loots)
		loot.setPos(newPos);
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
int Player::throwDice() {
	return rand() % 6;
}
