#pragma once
#include "./Player.h"
#include "./Characters/CharacterFactory.h"

Player::Player(Board * b, Player * p, int n)
{
	board = b;
	otherPlayer = p;
	resetActionTokens();
	crowToken = NPOS;
	stealthTokens = NUMBER_STEALTH_TOKENS;
	currentTile = nullptr;
	character = nullptr;
	this->n = n;
	if (n == 1)
		playing = true;
	else
		playing = false;
	turn = 0;
	loot2bTransfered = 0;
}

void Player::setPosition(Coord c)
{
	if (c == ROOF)
		currentTile = new Tile(STAIR, 3, 0, 0);
	else
	{
		Tile * t = board->getTile(c);
		setPosition(t);
	}

}

void Player::setPosition(Tile * tile)
{
	currentTile = tile;
	if (tile->getType() != WALKWAY && tile->getType() != LASER && tile->getType() != DEADBOLT)
		tile->turnUp();
	//tile->updateVisibleFrom(this);// En el primer turno sos visible??? O empezas a ser visible cuando te moves? Si es asi el segundo jugador tiene desventaja
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

confirmation Player::needConfirmation(Coord c)
{
	return needConfirmationToMove(c);
};

// TRUE if the user needs to make a decision to move to Tile 'c'
// FALSE if nothing is needed from the user
confirmation Player::needConfirmationToMove(Coord c)
{
	if (c == ROOF)
		return _MOVE;

	confirmation  b = _MOVE;
	Tile * wantedTile = board->getTile(c);

	// If is deadbolt and is empty you need to pay 3 tokens!
	if (wantedTile->is(DEADBOLT) && wantedTile->guardHere() == false && c != otherPlayer->getPosition())
	{
		if ((wantedTile->isFlipped() && getActionTokens() >= 3) || (wantedTile->isFlipped() == false && this->getActionTokens() >= 4))
			b = _ASK;
		else
			b = _CANT_MOVE;
	}
	else if (wantedTile->is(LASER) && !wantedTile->hasAlarm() && !this->has(MIRROR) && character->is(HACKER) == false && ((Laser*)wantedTile)->isHackerHere() == false)
	{
		if ((wantedTile->isFlipped() == false && this->getActionTokens() >= 3) || (wantedTile->isFlipped() == true && this->getActionTokens() >= 2))
			b = _ASK;
	}
	else if (wantedTile->is(KEYPAD) && !((Keypad *)wantedTile)->keyDecoded())
	{
		b = _DICE;
	}

	return b;
}
void Player::resetActionTokens()
{
	if (this->has(MIRROR))
		actionTokens = NUMBER_ACTION_TOKENS - 1;
	else
		actionTokens = NUMBER_ACTION_TOKENS;
	notify();
}

vector<Coord> Player::whereCanIMove()
{
	vector<Coord> v;
	Coord currPos = currentTile->getPos();
	for (auto &it : currentTile->getAdjacent())
	{
		if (this->has(GEMSTONE) && (this->actionTokens < 2) && otherPlayer->getPosition() == it);
		else if (this->has(PAINTING) && currentTile->is(SERVICE_DUCT) && board->getTile(it)->is(SERVICE_DUCT));
		else if (this->has(PAINTING) && currentTile->hasNorthWall() && it.floor == currPos.floor && it.row < currPos.row && it.col == currPos.col);
		else if (this->has(PAINTING) && currentTile->hasEastWall() && it.floor == currPos.floor && it.row == currPos.row && it.col > currPos.col);
		else if (this->has(PAINTING) && currentTile->hasSouthWall() && it.floor == currPos.floor && it.row > currPos.row && it.col == currPos.col);
		else if (this->has(PAINTING) && currentTile->hasWestWall() && it.floor == currPos.floor && it.row == currPos.row && it.col < currPos.col);
		else v.push_back(it);

	}
	if (currentTile->is(WALKWAY) && currPos.floor > 0)
		v.push_back(Coord(currPos.floor - 1, currPos.col, currPos.row));

	return v;
}

unsigned int Player::move(Coord c, unsigned int safeNumber)
{
	if (c == ROOF)
	{
		setPosition(ROOF);
		return 0;
	}
	else
		return move(board->getTile(c));
}

unsigned int Player::move(Tile * newTile, unsigned int safeNumber)
{
	removeActionToken();

	if (newTile->canMove(this))
	{
		if (this->has(GEMSTONE) && this->actionTokens > 2 && (newTile->getPos() == otherPlayer->getPosition()))
			removeActionToken();
		newAction("MOVE", newTile->getPos(), INT_MAX);

		// Exit the current tile
		currentTile->exit(this);

		setPosition(newTile);

		// And enter the next tile
		newTile->enter(this);

		// Update all loots
		for (auto & t : loots)
			t->update();

		if (safeNumber != 0)
			newTile->setSafeNumber(safeNumber);

		notify();
		return newTile->getSafeNumber();
	}
}

vector<Coord> Player::whereCanIPeek()
{
	vector<Coord> v = currentTile->whereCanIPeek();

	//If character is Hawk can make one peek through walls
	if (character->is(HAWK) && this->canIUseAbility())
	{
		Coord c = currentTile->getPos();

		if (currentTile->hasNorthWall())
			v.push_back(Coord(c.floor, c.col, c.row - 1));
		if (currentTile->hasWestWall())
			v.push_back(Coord(c.floor, c.col - 1, c.row));
		if (currentTile->hasSouthWall())
			v.push_back(Coord(c.floor, c.col, c.row + 1));
		if (currentTile->hasEastWall())
			v.push_back(Coord(c.floor, c.col + 1, c.row));
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
	if (character->is(JUICER))
	{
		vector<Coord> v = currentTile->getAdjacent();
		vector<Coord> noAlarm;
		for (vector<Coord>::iterator i = v.begin(); i != v.end(); i++)
		{
			if (!(board->getTile(*i)->hasAlarm()) && (this->getPosition().floor == i->floor))
			{
				noAlarm.push_back(*i);
			}
		}
		return noAlarm;
	}
	else return vector<Coord>();

}

unsigned int Player::peek(Coord c, unsigned int safeNumber)
{
	// Remove ability from hawk
	if (character->is(HAWK) && currentTile->isAdjacent(c) == false)
		useAbility(true);

	return peek(board->getTile(c));
}

unsigned int Player::peek(Tile * newTile, unsigned int safeNumber)
{
	if (newTile->isFlipped() == false)
	{
		removeActionToken();
		newAction("PEEK", newTile->getPos(), INT_MAX);
		newTile->turnUp(safeNumber);
		notify();
		return newTile->getSafeNumber();
	}
}

bool Player::createAlarm(Coord c)
{
	if ((character->is(JUICER)) && (currentTile->isAdjacent(c)) && (board->getTile(c)->hasAlarm() == false) && (this->actionTokens > 0) && (this->canIUseAbility()))
	{
		this->useAbility(true);
		board->getTile(c)->setAlarm(true);
		this->removeActionToken();
		cout << "Alarm created in Floor: " << c.floor << " col: " << c.col << " row; " << c.row << endl;
		newAction("CREATE_ALARM", c, INT_MAX);
		notify();
		return true;
	}
	else return false;
}

bool Player::placeCrow(Coord c)
{
	if (character->is(RAVEN) && character->canUseAbility() && !(c == crowToken) && c.col < F_WIDTH && c.row < F_HEIGHT)
	{
		if (!(crowToken == NPOS))
			board->getTile(crowToken)->setCrowToken(false);
		this->useAbility(true);
		board->getTile(c)->setCrowToken(true);
		crowToken = c;
		newAction("PLACE_CROW", c, INT_MAX);
		return true;
	}
	else return false;
}


void Player::useToken()
{
	currentTile->doAction(toString(USE_TOKEN), this);
	newAction("USE_TOKEN", getPosition(), INT_MAX);
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

vector<lootType> Player::getAvailableLoots()
{
	vector<lootType> v;
	for (auto& l : loots)
		if (l->isLootAvailable())
		{
			if (l->is(GOLD_BAR) && otherPlayer->has(GOLD_BAR))
				continue;
			else v.push_back(l->getType());
		}

	return v;
}
vector<string> Player::getActions()
{
	vector <string> possibleActions;
	if (currentTile != nullptr)
	{
		possibleActions = currentTile->getActions(this);

		if (currentTile->hasLoot() && !(this->has(GOLD_BAR) && currentTile->hasLoot(GOLD_BAR)))
			possibleActions.push_back("PICK_UP_LOOT");
	}
	
	if (character != nullptr)
		possibleActions.push_back(character->getAction(this));

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
	newAction("ADD_TOKEN", getPosition(), INT_MAX);
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

void Player::newAction(string action, Coord tile, int dice)
{
	actions.push_back(actionNode(action, tile, turn, dice));
}

string Player::lastAction(void)
{
	if (actions.empty() == false)
		return actions.back().myAction;
	else return string("");
}

bool Player::throwDice(int n)
{
	bool b = false;
	dice.push_back(n);
	currDice = n;
	b = currentTile->doAction("THROW_DICE", this);
	newAction(toString(THROW_DICE), currentTile->getPos(), INT_MAX);

	notify();
	return b;
}

int Player::throwDice()
{
	default_random_engine generator((unsigned int)std::chrono::system_clock::now().time_since_epoch().count());
	uniform_int_distribution<int> distribution(1, 6);
	return distribution(generator);
}

void Player::addLoot(lootType l)
{
	if (loots.size() < 3)
	{
		Loot * currLoot = (new LootFactory)->newLoot(l);
		if (currLoot != nullptr)
		{
			currLoot->setPos(this->getPosition());
			currLoot->pick(this);
			loots.push_back(currLoot);
			notify();
		}
	}
};

bool Player::hasLoot()
{
	return !loots.empty();
}

void Player::pickUpLoot()
{
	if (this->currentTile->hasLoot())
	{
		for (auto &it : this->currentTile->getLoot())
		{
			if (it->is(GOLD_BAR) && this->has(GOLD_BAR))
				cout << "Already has GOLD BAR cant pick another one" << endl;
			else
			{
				this->addLoot(it->getType());
				currentTile->removeLoot(it);
				cout << "Player just picked a:" << it->getDescription() << endl;
			}
		}
	}
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

bool Player::losePersianKitty()
{
	bool b = false;
	Coord pos = board->getFloor(getPosition().floor)->whereToPlaceKitty((getPosition()));
	Loot * kitty = nullptr;

	for (auto &it : loots)
		if (it->is(PERSIAN_KITTY))
			kitty = it;

	if (!(pos == NPOS))
	{
		if (kitty != nullptr)
		{
			board->getTile(pos)->setLoot(kitty);
			cout << "kitty is found at " << pos << endl;
			this->removeLoot(kitty);
			b = true;
		}
	}
	else cout << "No alarm tile flipped" << endl;
	return b;
}

void Player::areLootsReady()
{
	for (auto &it : loots)
	{
		if (it->is(PERSIAN_KITTY)) it->lootAvailable(true);
	}
}

void Player::giveLoot(lootType type)
{
	if (has(type))
	{
		newAction("OFFER_LOOT", getPosition(), INT_MAX);
		otherPlayer->newAction("REQUEST_LOOT", getPosition(), INT_MAX);

		for (unsigned i = 0; i < loots.size(); i++)
			if (type == loots[i]->getType())
				removeLoot(loots[i]);

		otherPlayer->addLoot(type);

	}

}

void Player::receiveLoot(lootType type)
{
	otherPlayer->giveLoot(type);
	/*if (n > 0 && (unsigned)n <= otherPlayer->getLoots().size())
	{
		if (otherPlayer->getLoots()[n - 1]->isLootAvailable() && otherPlayer->getLoots()[n - 1] != nullptr)
		{
			this->addLoot(otherPlayer->loots[n - 1]->getType());
			otherPlayer->removeLoot(loots[n - 1]);
			cout << "received Loot" << endl;
		}
		else
			cout << "loot couldnt be received" << endl;
	}*/
}
