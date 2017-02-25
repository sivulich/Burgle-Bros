#pragma once
#include "../Header Files/Player.h"
#include "../Header Files/Characters/CharacterFactory.h"

Player::Player(Board * b)
{
	board = b;
	stealthTokens = NUMBER_STEALTH_TOKENS;
	actionTokens = NUMBER_ACTION_TOKENS;
}

void Player::setPosition(Tile * tile)
{
	currentTile = tile;
}
void Player::setPosition(Coord c)
{
	currentTile = board->getTile(c);
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
	// If the tile is adjacent to the player's position 
	if (newTile->isAdjacent(getPosition()))
	{
		removeActionToken();
		if (newTile->canMove(this))
		{
			currentTile = newTile;
			// visibleFrom no es la adyacencia de la tile! Que entertile modifique 
			// desde donde ve el guardia al jugador dependiendo el tipo de tile
			//setVisibleFrom(newTile->getAdjacents());
			newAction("MOVE", newTile->getPos());
			newTile->enterTile(this);						
			return true;
		}
	}
	
	return false;
}

void Player::peek(Tile * newTile)
{
	removeActionToken();
	newAction("PEEK", newTile->getPos());
	newTile->peek();
}

Coord Player::getPosition()
{
	return currentTile->getPos();
};

void Player::removeStealthToken()
{
	if (stealthTokens > 0)
		stealthTokens--;
	else
		DEBUG_MSG("NO STEALTH TOKENS LEFT, YOU ARE DEADDDDD");
}

void Player::removeActionToken()
{
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

void Player::newAction( string action, Coord tile)
{
	actions.push_back(actionNode(action,tile));
}

int Player::throwDice()
{
	default_random_engine generator;
	uniform_int_distribution<int> distribution(1, 6);
	unsigned int temp = distribution(generator);
	dice.push_back(temp);
	DEBUG_MSG("You rolled the dice and got a " << temp);
	return temp;
}

void Player::addLoot(Loot * l)
{
	loots.push_back(l);
};

bool Player::hasLoot()
{
	return !loots.empty();
}

void Player::clearVisibleFrom()
{
	visibleFrom.clear();
};

void Player::addVisibleTile(Coord tile)
{
	visibleFrom.push_back(tile);
};

vector <Coord>& Player::getVisibleFrom()
{
	return visibleFrom;
};

bool Player::isVisibleFrom(Coord c)
{
	return find(visibleFrom.begin(), visibleFrom.end(), c) != visibleFrom.end() ? true : false;
}

void Player::setVisibleFrom(vector <Coord> newCoords)
{
	clearVisibleFrom();			// erase the previous coordinates
	for (auto i : newCoords)
		addVisibleTile(i);		// add the new visible from tile coordinates
}

string Player::getName()
{ 
	return name;
};

characterType Player::getCharacterType()
{
	return character->getType();
};