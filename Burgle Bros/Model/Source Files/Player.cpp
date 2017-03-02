#pragma once
#include "../Header Files/Player.h"
#include "../Header Files/Characters/CharacterFactory.h"

Player::Player(Board * b)
{
	board = b;
	resetActionTokens();
	stealthTokens = NUMBER_STEALTH_TOKENS;
}

void Player::setPosition(Tile * tile)
{
	currentTile = tile;
	notify();
}

void Player::setPosition(Coord c)
{
	currentTile = board->getTile(c);
	notify();
}

void Player::setName(string & playerName)
{
	name = playerName;
	notify();
}

void Player::setCharacter(characterType type)
{
	character = CharacterFactory().newCharacter(type);
	notify();
}


bool Player::has(lootType l)
{
	for (auto& loot : loots)
		if (l == loot->getType())
			return true;
	return false;
}

bool Player::needConfirmationToMove(Coord c)
{
	tileType t = board->getTile(c)->getType();
	return false;
	if (t == DEADBOLT)
		return true;
	else
		return false;
}
void Player::resetActionTokens()
{
	actionTokens = NUMBER_ACTION_TOKENS;
	notify();
}

bool Player::move(Coord c)
{
	Tile * t = board->getTile(c);
	return move(t);
}

bool Player::move(Tile * newTile)
{
	removeActionToken();
//	if (newTile->canMove(this))
//	{
		newAction("MOVE", getPosition());
		currentTile->exitTile(this);
		setPosition(newTile);
		newTile->enterTile(this);
		// Update from where the guard can see the player
		updateVisibleFrom();
		// Update all loots
		for (auto & t : loots)
			t->update();
		notify();
		return true;
	//}
//	return false;
	
}

void Player::peek(Coord c)
{
	Tile * t = board->getTile(c);
	peek(t);
}

void Player::peek(Tile * newTile)
{
	if (newTile->isAdjacent(getPosition()))
	{
		removeActionToken();
		newAction("PEEK", newTile->getPos());
		newTile->peek();
		notify();
	}
}

Coord Player::getPosition()
{
	return currentTile == nullptr ? NPOS : currentTile->getPos();
};

vector<string> Player::getActions()
{
	return currentTile->getActions(this);
}

bool Player::isOnRoof()
{
	return getPosition() == ROOF;
}
void Player::print()
{
	cout << name << " at " << currentTile->getPos() << " --> " << toString(currentTile->getType()) << endl;
	cout << "Action tokens " << getActionTokens() << endl;
	cout << "Stealth tokens " << getStealthTokens() << endl;
	
	cout << "Visible from: ";
	for (auto c : visibleFrom)
		cout << c << " ";
	cout << endl;

	cout << "Loots : ";
	for (auto c : loots)
		cout << toString(c->getType()) << " ";
	cout << endl;

	cout << "Character " << toString(character->getType()) << endl;
	cout << endl;
	
}
void Player::removeStealthToken()
{
	if(currentTile->tryToHide() == false)	// try to hide from the guard (for the LAVATORY)
		stealthTokens--;					// if that fails, remove a stealth tokens
	else
		DEBUG_MSG("NO STEALTH TOKENS LEFT, YOU ARE DEADDDDD");
	notify();
}

void Player::removeActionToken()
{
	if (actionTokens > 0)
		actionTokens--;
	else
		DEBUG_MSG("UNEXPECTED ERROR. COULD NOT REMOVE ACTION TOKEN.");
	notify();
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
	notify();
}

void Player::addLoot(Loot * l)
{
	loots.push_back(l);
	notify();
};

bool Player::hasLoot()
{
	return !loots.empty();
}

void Player::addVisibleTile(Coord tile)
{
	visibleFrom.push_back(tile);
};

vector <Coord> Player::getVisibleFrom()
{
	return visibleFrom;
};

bool Player::isVisibleFrom(Coord c)
{
	return find(visibleFrom.begin(), visibleFrom.end(), c) != visibleFrom.end() ? true : false;
}

void Player::updateVisibleFrom()
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

