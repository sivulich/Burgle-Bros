#pragma once
#include "Player.h"

Player::Player(string & playerName) {
	name = playerName;
	id = 0;
	pos = { 0,0 };
	actionTokens = 0;
	stealthTokens = 0;
}
/**
	Sets the ID of the player
*/
void Player::setId(characterID character) {
	id = character;
	stealthTokens = NUMBER_STEALTH_TOKENS;
	actionTokens = NUMBER_ACTION_TOKENS;
}
/**
	Reset the player action tokens
*/
void Player::newTurn() {
	actionTokens = NUMBER_ACTION_TOKENS;
}
/**
	Sets the player position to the parameter given
*/
void Player::move(Coord & newPos) {
	pos = newPos;
}
/**
	Removes 1 stealth token if possible
*/
void Player::removeStealthToken() {
	if (stealthTokens > 0)
		stealthTokens--;
}
/**
	Removes 1 action token if possible
*/
void Player::removeActionToken() {
	if (actionTokens > 0)
		actionTokens--;
}
/**
	Returns the amount of stealth tokens
*/
int  Player::getStealthTokens() {
	return stealthTokens;
}
/**
	Returns the amount of action tokens
*/
int  Player::getActionTokens() {
	return actionTokens;
}