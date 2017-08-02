#pragma once
#include "./Player.h"
#include "./Characters/CharacterFactory.h"

Player::Player(Board * b, Player * p)
{
	board = b;
	otherPlayer = p;
	resetActionTokens();
	stealthTokens = NUMBER_STEALTH_TOKENS;
	currentTile = nullptr;
	turn = 0;
}



void Player::setPosition(Coord c)
{
	setPosition(board->getTile(c));
}

void Player::setPosition(Tile * tile)
{
	currentTile = tile;
	currentTile->turnUp();
	notify();
}

void Player::setName(string & playerName)
{
	name = playerName;
	//notify(); creo que no hace falta llamar el update de la vista porque el
	//           nombre se setea antes de que se vea la pantalla de juego
}

void Player::setCharacter(characterType type)
{
	character = CharacterFactory().newCharacter(type);
	//notify(); creo que no hace falta llamar el update de la vista porque el
	//           character se setea antes de que se vea la pantalla de juego
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

vector<Coord> Player::whereCanIMove()
{

	vector<Coord> v = currentTile->whereCanIMove();
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
	// COmento el canMove, las tiles disponibles para moverse tienen que brindarse con el metodo whereCanIMove
	// este metodo mueve al jugador sin preguntar
	//if (newTile->canMove(this))
	//{
		// Solo saco un action token si me puedo mover
		removeActionToken();

		newAction("MOVE", newTile->getPos());

		// Exit the current tile
		currentTile->exit(this);

		setPosition(newTile->getPos());

		// And enter the next tile
		newTile->enter(this);

		// Update all loots
		for (auto & t : loots)
			t->update();
		
		// Notify the view the player has moved
		notify();

		return true;
	//}
	//return false;
	
}

vector<Coord> Player::whereCanIPeek()
{
	vector<Coord> v = currentTile->whereCanIPeek();
	// VER COMO HACER CON EL SPOTTER UNA VEZ POR TURNO PARA HACER PEEK EN UNA TILE separado por una pared

	if (character->is(SPOTTER) && "No use la habilidad en este turno")
	{
		//"agregar al vector v todos los tiles alrededor del que estoy, incluidos los separados por paredes"
	}

	// Remove the flipped ones


	v.erase(remove_if(v.begin(),v.end(),
		[&](const Coord t)-> bool
		{ return board->getTile(t)->isFlipped(); }),
		v.end());
	return v;

}

bool Player::peek(Coord c)
{
	return peek(board->getTile(c));
}

bool Player::peek(Tile * newTile)
{
	// no chequeo mas si es adyacente, peek lo hace sin preguntar, la adyacencia se consigue con whereCanIPeek()

	if (newTile->isFlipped()==false) 
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
	if (getCharacterType() == JUICER && currentTile->isAdjacent(c) && board->getTile(c)->hasAlarm() == false)
	{
		board->getTile(c)->setAlarm(true);
		return true;
	}
	else return false;
}

void Player::placeCrow(Coord c)
{
	if (getCharacterType() == RAVEN)
	{
		
	}
		board->getTile(c)->setAlarm(true);
}


void Player::useToken()
{

}


void Player::addToken()
{

}

Coord Player::getPosition()
{
	return currentTile == nullptr ? NPOS : currentTile->getPos();
};


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
		/*if (getCharacterType() == JUICER)
			possibleActions.push_back("CREATE_ALARM");
		else if (getCharacterType() == RAVEN)
			possibleActions.push_back("PLACE_CROW");
		else if (getCharacterType() == SPOTTER)
			possibleActions.push_back("SPY_PATROL_DECK_CARD");*/
	}
	
	if (otherPlayer!= nullptr && otherPlayer->getPosition() == getPosition())
	{
		if (hasLoot())
			possibleActions.push_back("OFFER_LOOT");
		if (otherPlayer->hasLoot())
			possibleActions.push_back("REQUEST_LOOT");
	}
	return possibleActions;
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
	// Lo del lavatory es una mierda, hay que preguntar al jugador si quiere usar un token o no..

	//if(currentTile->tryToHide() == false)	// try to hide from the guard (for the LAVATORY)
	stealthTokens--;					// if that fails, remove a stealth tokens
	if(stealthTokens==0)
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
	actions.push_back(actionNode(action,tile,turn));
}

int Player::throwDice()
{
	default_random_engine generator(std::chrono::system_clock::now().time_since_epoch().count());
	uniform_int_distribution<int> distribution(1, 6);
	unsigned int temp = distribution(generator);
	dice.push_back(temp);
	newAction(toString(THROW_DICE), currentTile->getPos());

	DEBUG_MSG("You rolled the dice and got a " << temp);

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

characterType Player::getCharacterType()
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

