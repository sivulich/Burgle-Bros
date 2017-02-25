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


bool Player::has(lootType l)
{
	for (auto& loot : loots)
		if (l == loot->getType())
			return true;
	return false;
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
			
			newAction("MOVE", newTile->getPos());
			newTile->enterTile(this);
			// Update from where the guard can see the player
			setVisibleFrom(newTile->getAdjacents());
			// Update all loots
			for (auto & t : loots)
				t->update();
			return true;
		}
		//return false??
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

void Player::setVisibleFrom()
{
	visibleFrom.clear();
	// Add the player position
	visibleFrom.push_back(getPosition());

}

string Player::getName()
{ 
	return name;
};

characterType Player::getCharacterType()
{
	return character->getType();
};