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
	throwingDices = false;
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
	Tile * t = board->getTile(c);
	setPosition(t);
}

void Player::setPosition(Tile * tile)
{
	currentTile = tile;
	/*if(tile->getType() != WALKWAY && tile->getType() != LASER && tile->getType() != DEADBOLT)*/
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

	confirmation  b = _MOVE;	
	Tile * wantedTile = board->getTile(c);
		
	if (wantedTile->is(DEADBOLT) && !(wantedTile->guardHere() || c == otherPlayer->getPosition()) )
	{
		if ((wantedTile->isFlipped() == true && this->getActionTokens() >= 3) || (wantedTile->isFlipped() == false && this->getActionTokens() >= 4))
			b = _ASK;
		else
			b = _CANT_MOVE;
	}
	else if (wantedTile->is(LASER) && wantedTile->hasAlarm() == false && ! this->has(MIRROR) && ! (this->getCharacter() == HACKER) && !((Laser*)wantedTile)->isHackerHere())
	{
		if ( (wantedTile->isFlipped() == false && this->getActionTokens() >= 3) || (wantedTile->isFlipped() == true && this->getActionTokens() >= 2))
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

	/*// Remove the ones where I cant move
	for (auto& t : v)
	{
		// Aca hay un problema con el keypad, porque canMove tira el dado!! Lo arreglo con un continue
		if (board->getTile(t)->is(KEYPAD))
			continue;
		//else if (board->getTile(t)->canMove(this) == false)
		//	v.erase(remove(v.begin(), v.end(), t));
	}*/
	return v;
}

bool Player::move(Coord c)
{
	return move(board->getTile(c));
}

bool Player::move(Tile * newTile)
{
		removeActionToken();

		if (newTile->canMove(this)) 
		{
			if (this->has(GEMSTONE) && this->actionTokens > 2 && (newTile->getPos() == otherPlayer->getPosition()))
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
		return false;
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
		newAction("CREATE_ALARM", c);
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
		newAction("PLACE_CROW",c);
	}
	else return false;
}


void Player::useToken()
{
	currentTile->doAction(toString(USE_TOKEN), this);
	newAction("USE_TOKEN", getPosition());
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

			if (!throwingDices)
			{
				if (currentTile->hasLoot())
				{
					bool b = false;
					for (auto &it : this->loots) if (it->is(GOLD_BAR)) b = true;
					if (!(b && (currentTile->getLoot().size() == 1 && currentTile->getLoot()[0]->is(GOLD_BAR))))
						possibleActions.push_back("PICK_UP_LOOT");
				}
			}

		}


		//AGREGAR LAS ACCIONES DE LOS CHARACTERS
		if (!throwingDices)
		{
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
		}
	if (destination.floor < NUMBER_FLOORS && destination.col < F_WIDTH && destination.row < F_HEIGHT)
	{
		if (board->getTile(destination)->is(KEYPAD) && !((Keypad *)board->getTile(destination))->keyDecoded())
		{
			possibleActions.push_back("THROW_DICE");
		}

	}
	return possibleActions;
}

void Player::addToken()
{
	currentTile->doAction(string("ADD_TOKEN"), this);
	newAction("ADD_TOKEN", getPosition());
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

bool Player::throwDice(int n)
{
	bool b = false;
	dice.push_back(n);
	currDice = n;
	 b =currentTile->doAction("THROW_DICE",this);
	newAction(toString(THROW_DICE), currentTile->getPos());

	//DEBUG_MSG("You rolled the dice and got a " << temp);

	notify();
	return b;
}

void Player::addLoot(lootType l)
{
	Loot * currLoot = (new LootFactory)->newLoot(l);
	currLoot->setPos(this->getPosition());
	currLoot->pick(this);
	loots.push_back(currLoot);
	notify();
};

bool Player::hasLoot()
{
	return !loots.empty();
}

 void Player::pickUpLoot(lootType l)
{
	 if (this->currentTile->hasLoot())
	 {
		 bool b = false;
		 for (auto &it : this->loots)
		 {
			 it->is(GOLD_BAR);
				 b = true;
		 };
		 for (auto &it : this->currentTile->getLoot())
		 {
			 if (it->is(l))
			 {
				 if(l == GOLD_BAR && b) cout << "Already has GOLD BAR cant pick another one" << endl;
				 else
				 {
					 this->addLoot(it->getType());
					 cout << "Player just picked a:" << it->getDescription() << endl;
					 currentTile->removeLoot(it);
				 }
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

void Player::losePersianKitty()
{
	Coord pos = board->getFloor(getPosition().floor)->whereToPlaceKitty(getPosition());
	Loot * kitty = nullptr;
	for (auto &it : loots) if (it->is(PERSIAN_KITTY)) kitty = it;
	if (!(pos == NPOS))
	{
		if (kitty != nullptr)
		{
			board->getTile(pos)->setLoot(kitty);
			cout << "kitty is found at " << pos << endl;
			this->removeLoot(kitty);
		}
	}
	else cout << "No alarm tile flipped" << endl;
}

void Player::areLootsReady()
{
	for (auto &it : loots)
	{
		if (it->is(PERSIAN_KITTY)) it->lootAvailable(true);
	}
}

void Player::giveLoot(int n)
{
	if (n > 0 && n <= loots.size())
	{
		if (loots[n - 1]->isLootAvailable() && loots[n-1] != nullptr)
		{
			otherPlayer->addLoot(loots[n - 1]->getType());
			this->removeLoot(loots[n - 1]);
			cout << "sent Loot" << endl;
		}
		else
			cout << "loot couldnt be sent" << endl;
	}
}


void Player::receiveLoot(int n)
{
	if (n > 0 && n <= otherPlayer->getLoots().size())
	{
		if (otherPlayer->getLoots()[n - 1]->isLootAvailable() && otherPlayer->getLoots()[n - 1] != nullptr)
		{
			this->addLoot(otherPlayer->loots[n - 1]->getType());
			otherPlayer->removeLoot(loots[n - 1]);
			cout << "received Loot" << endl;
		}
		else
			cout << "loot couldnt be received" << endl;
	}
}
