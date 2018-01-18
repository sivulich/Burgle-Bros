#pragma once
#include "./Player.h"
#include "./Characters/CharacterFactory.h"

Player::Player(Board * b, Player * p, int n)
{
	board = b;
	otherPlayer = p;
	resetActionTokens();
	crowToken = NPOS;
	lastPos = NPOS;
	destination = NPOS;
	stealthTokens = NUMBER_STEALTH_TOKENS;
	currentTile = nullptr;
	character = nullptr;
	this->n = n;
	if (n == 1)
		playing = true;
	else
		playing = false;
	turn = 0;
}

void Player::setPosition(Coord c)
{
	Tile * t = board->getTile(c);
	setPosition(t);
}

void Player::setPosition(Tile * tile)
{
	currentTile = tile;
	if(tile->getType() != WALKWAY)
		tile->turnUp();
	tile->updateVisibleFrom(this);
	notify();
}

void Player::setName(string & playerName)
{
	name = playerName;
}

void Player::setCharacter(characterType type)
{
	character = CharacterFactory().newCharacter(type);
}
void Player::setCharacter(string type)
{
	character = CharacterFactory().newCharacter(toEnum_characterType(type.c_str()));
}


bool Player::has(lootType l)
{
	for (auto& loot : loots)
		if (l == loot->getType())
			return true;
	return false;
}

bool Player::needConfirmation(Coord c)
{
	return needConfirmationToMove(c);
};

bool Player::needConfirmationToMove(Coord c)
{
	bool  b = false;	
z	if (board->getTile(c)->is(DEADBOLT) && board->getTile(c)->is(LASER))
	{
		if (board->getTile(c)->is(DEADBOLT) && !(board->getTile(c)->guardHere() || c == otherPlayer->getPosition()) && ((this->getActionTokens() >= 3 && board->getTile(c)->isFlipped() == true) || (this->getActionTokens() >= 4 && board->getTile(c)->isFlipped() == false)))
		{
			b = true;
		}
		if (board->getTile(c)->is(LASER) && (((this->getActionTokens() >= 3) && board->getTile(c)->isFlipped() == false) || ((this->getActionTokens() >= 2) && board->getTile(c)->isFlipped() == false))) b = true;
		{
			b = true;
		};
	}
	return b;
}
void Player::resetActionTokens()
{
	actionTokens = NUMBER_ACTION_TOKENS;
	notify();
}

vector<Coord> Player::whereCanIMove()
{
	vector<Coord> v = currentTile->getAdjacent();

	// Remove the ones where I cant move
	for (auto& t : v)
	{
		// Aca hay un problema con el keypad, porque canMove tira el dado!! Lo arreglo con un continue
		if (board->getTile(t)->is(KEYPAD))
			continue;
		//else if (board->getTile(t)->canMove(this) == false)
		//	v.erase(remove(v.begin(), v.end(), t));
	}
	return v;
}

bool Player::move(Coord c)
{
	return move(board->getTile(c));
}

bool Player::move(Tile * newTile)
{
	// Solo saco un action token si me puedo mover
	removeActionToken();

	newAction("MOVE", newTile->getPos());

	// Exit the current tile
	lastPos = this->getPosition();
	currentTile->exit(this);

	setPosition(newTile);

	// And enter the next tile
	newTile->enter(this);

	// Update all loots
	for (auto & t : loots)
		t->update();

	// Notify the view the player has moved
	notify();

	return true;
}

vector<Coord> Player::whereCanIPeek()
{
	vector<Coord> v = currentTile->whereCanIPeek();

	//If character is Hawk can make one peek through walls
	if (character->is(HAWK) && this->canIUseAbility())
	{
		if (currentTile->hasNorthWall())
		{
			v.push_back(Coord(currentTile->getPos().floor, currentTile->getPos().col, currentTile->getPos().row-1));
		}
		if (currentTile->hasWestWall())
		{
			v.push_back(Coord(currentTile->getPos().floor, currentTile->getPos().col-1, currentTile->getPos().row));
		}
		if (currentTile->hasSouthWall())
		{
			v.push_back(Coord(currentTile->getPos().floor, currentTile->getPos().col, currentTile->getPos().row+1));
		}
		if (currentTile->hasEastWall())
		{
			v.push_back(Coord(currentTile->getPos().floor, currentTile->getPos().col+1, currentTile->getPos().row));
		}
	}

	// Remove the flipped ones
	v.erase(remove_if(v.begin(), v.end(),
		[&](const Coord t)-> bool
	{ return board->getTile(t)->isFlipped(); }),
		v.end());
	return v;

}

vector<Coord> Player::getAdjacentJuicer()
{
	vector<Coord> v = currentTile->getAdjacent();
	vector<Coord> noAlarm;
	for (vector<Coord>::iterator i=v.begin();i!=v.end();i++)
	{
		if (!(board->getTile(*i)->hasAlarm()) && (this->getPosition().floor == i->floor))
		{
			noAlarm.push_back(*i);
		}
	}
	return noAlarm;
}

bool Player::peek(Coord c)
{
	bool b = false;
	if (character->is(HAWK))
	{
		for (auto &it: currentTile->getAdjacent())
		{
			if (it == c) b = true;
		}
	}
	if (!b) useAbility(true);
	return peek(board->getTile(c));
}

bool Player::peek(Tile * newTile)
{
	// no chequeo mas si es adyacente, peek lo hace sin preguntar, la adyacencia se consigue con whereCanIPeek()

	if (newTile->isFlipped() == false)
	{
		removeActionToken();
		newAction("PEEK", newTile->getPos());
		newTile->turnUp();
		notify();
		return true;
	}
	return false;

}

bool Player::createAlarm(Coord c)
{
	if ((character->is(JUICER)) && (currentTile->isAdjacent(c)) && (board->getTile(c)->hasAlarm() == false) && (this->actionTokens>0) && (this->canIUseAbility()) )
	{
		this->useAbility(true);
		board->getTile(c)->setAlarm(true);
		this->removeActionToken();
		cout << "Alarm created in Floor: " << c.floor << " col: " << c.col << " row; " << c.row << endl;
		notify();
		return true;
	}
	else return false;
}

bool Player::placeCrow(Coord c)
{
	if (character->is(RAVEN) && character->canUseAbility() && !(c == crowToken) && c.col<F_WIDTH && c.row <F_HEIGHT)
	{
		if (!(crowToken == NPOS))
			board->getTile(crowToken)->setCrowToken(false);
		this->useAbility(true);
		board->getTile(c)->setCrowToken(true);
		crowToken = c;
	}
	else return false;
}


void Player::useToken()
{

}


Coord Player::getPosition()
{
	return currentTile == nullptr ? NPOS : currentTile->getPos();
};

vector < string> Player::gettActions()
{
	vector <string> v = this->getActions();
	notify();
	return v;
}

vector<string> Player::getActions()
{
	vector <string> possibleActions;

	if (currentTile != nullptr)
	{
		possibleActions = currentTile->getActions(this);

		if (currentTile->hasLoot())
			possibleActions.push_back("PICK_UP_LOOT");
	}

	//AGREGAR LAS ACCIONES DE LOS CHARACTERS
	if (character != nullptr)
	{
		possibleActions.push_back(character->getAction(this));
		/*if (getCharacter() == JUICER)
			possibleActions.push_back("CREATE_ALARM");
		else if (getCharacter() == RAVEN)
			possibleActions.push_back("PLACE_CROW");
		else if (getCharacter() == SPOTTER)
			possibleActions.push_back("SPY_PATROL_DECK_CARD");*/
	}

	if (otherPlayer != nullptr && otherPlayer->getPosition() == getPosition())
	{
		if (hasLoot())
			possibleActions.push_back("OFFER_LOOT");
		if (otherPlayer->hasLoot())
			possibleActions.push_back("REQUEST_LOOT");
	}
	return possibleActions;
}

void Player::addToken()
{
	currentTile->doAction(string("ADD_TOKEN"), this);
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
	for (auto c : getVisibleFrom())
		cout << c << " ";
	cout << endl;

	cout << "Loots : ";
	for (auto c : loots)
		cout << toString(c->getType()) << " ";
	cout << endl;

}
void Player::removeStealthToken()
{
	if (this->currentTile->tryToHide() == false)
	{
		stealthTokens--;
		cout << this->name << " lost a stealth token" << endl;
		if (stealthTokens == 0)
			DEBUG_MSG("NO STEALTH TOKENS LEFT, YOU ARE DEADDDDD");
	}
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

void Player::newAction(string action, Coord tile)
{
	actions.push_back(actionNode(action, tile, turn));
}

int Player::throwDice()
{
	default_random_engine generator(std::chrono::system_clock::now().time_since_epoch().count());
	uniform_int_distribution<int> distribution(1, 6);
	unsigned int temp = distribution(generator);
	dice.push_back(temp);
	currentTile->doAction("THROW_DICE",this);
	newAction(toString(THROW_DICE), currentTile->getPos());

	//DEBUG_MSG("You rolled the dice and got a " << temp);

	notify();
	return temp;
}

void Player::addLoot(lootType l)
{
	loots.push_back((new LootFactory)->newLoot(l));
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

string Player::getName()
{
	return name;
};

characterType Player::getCharacter()
{
	return character->getType();
};

/**
Clears the visibleFrom list
*/
void Player::clearVisibleFrom()
{
	visibleFrom.clear();
}

