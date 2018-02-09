#include "./FloorObserver.h"
#include "./TileObserver.h"
#include "Animations.h"



static map<tileType, string> images = { {ATRIUM,string("../Game/Graphics/Images/Tiles/Tile - Atrium.png")},
										{CAMERA,string("../Game/Graphics/Images/Tiles/Tile - Camera.png") },
										{COMPUTER_ROOM_F,string("../Game/Graphics/Images/Tiles/Tile - Computer Room (Fingerprint).png") },
										{COMPUTER_ROOM_L,string("../Game/Graphics/Images/Tiles/Tile - Computer Room (Laser).png") },
										{COMPUTER_ROOM_M,string("../Game/Graphics/Images/Tiles/Tile - Computer Room (Motion).png") },
										{DEADBOLT,string("../Game/Graphics/Images/Tiles/Tile - Deadbolt.png") },
										{FINGERPRINT,string("../Game/Graphics/Images/Tiles/Tile - Fingerprint.png") },
										{FOYER,string("../Game/Graphics/Images/Tiles/Tile - Foyer.png") },
										{KEYPAD,string("../Game/Graphics/Images/Tiles/Tile - Keypad.png") },
										{LABORATORY,string("../Game/Graphics/Images/Tiles/Tile - Laboratory.png") },
										{LASER,string("../Game/Graphics/Images/Tiles/Tile - Laser.png") },
										{LAVATORY,string("../Game/Graphics/Images/Tiles/Tile - Lavatory.png") },
										{MOTION,string("../Game/Graphics/Images/Tiles/Tile - Motion.png") },
										{SAFE,string("../Game/Graphics/Images/Tiles/Tile - Safe.png") },
										{SCANNER,string("../Game/Graphics/Images/Tiles/Tile - Scanner.png")},
										{SECRET_DOOR,string("../Game/Graphics/Images/Tiles/Tile - Secret Door.png") },
										{SERVICE_DUCT,string("../Game/Graphics/Images/Tiles/Tile - Service Duct.png") },
										{STAIR,string("../Game/Graphics/Images/Tiles/Tile - Stairs.png") },
										{THERMO,string("../Game/Graphics/Images/Tiles/Tile - Thermo.png") },
										{WALKWAY,string("../Game/Graphics/Images/Tiles/Tile - Walkway.png") }
};

TileObserver::TileObserver(Tile* t, Container* floorContainer, Container* boardContainer)
{
	tile = t;

	this->floorContainer = floorContainer;
	this->boardContainer = boardContainer;
	// Compute some values 
	double TILE_GRID_SIZE, TILE_GRID_XPOS_IN_FLOOR, TILE_GRID_YPOS_IN_FLOOR, TILE_SEPARATION, TILE_SIZE;
	if (FLOOR_WIDTH < FLOOR_HEIGHT)
	{
		TILE_GRID_SIZE = FLOOR_WIDTH;
		TILE_GRID_XPOS_IN_FLOOR = 0;
		TILE_GRID_YPOS_IN_FLOOR = ((FLOOR_HEIGHT - TILE_GRID_SIZE) / 2.0);
	}
	else
	{
		TILE_GRID_SIZE = FLOOR_HEIGHT;
		TILE_GRID_XPOS_IN_FLOOR = ((FLOOR_WIDTH - TILE_GRID_SIZE) / 2.0);
		TILE_GRID_YPOS_IN_FLOOR = 0;
	}

	TILE_SEPARATION = (1.0 / 20.0 *  TILE_GRID_SIZE);
	TILE_SIZE = ((TILE_GRID_SIZE - 3 * TILE_SEPARATION) / 4);

	// Create a card with front and revere image
	Coord coord = tile->getPos();

	double XPOS = TILE_GRID_XPOS_IN_FLOOR + coord.col * (TILE_SIZE + TILE_SEPARATION);
	double YPOS = TILE_GRID_YPOS_IN_FLOOR + coord.row * (TILE_SIZE + TILE_SEPARATION);

	tileCard = new Card(images[tile->getType()], string("../Game/Graphics/Images/Tiles/Tile - Reverse.png"), XPOS, YPOS, TILE_SIZE, TILE_SIZE, tile->isFlipped());
	// Set name of the tile (its coord)
	string name = string("COORDA") + to_string(coord.row + 1) + string("F") + to_string(coord.floor);
	name[5] += coord.col;
	tileCard->setName(name);
	floorContainer->addObject(tileCard);

	zoomedCard = new Image(images[tile->getType()], FLOOR_XPOS[coord.floor]+XPOS, FLOOR_YPOS + YPOS, TILE_SIZE, TILE_SIZE);
	zoomedCard->setHoverable(false);
	zoomedCard->setClickable(false);
	zoomedCard->setVisible(false);
	boardContainer->addObject(zoomedCard);


	// Now check for walls
	Image * wall = nullptr;
	if (tile->hasEastWall())
	{
		wall = new Image(string("./Graphics/Images/wallV.png"), XPOS + TILE_SIZE, YPOS, TILE_SEPARATION, TILE_SIZE);
		wall->setClickable(false);
		wall->setHoverable(false);
		floorContainer->addObject(wall);
	}

	if (tile->hasSouthWall() == true && coord.row < 3)// QUICK FIX DE LAS PAREDES QUE NO TIENEN QUE ESTAR
	{
		wall = new Image(string("./Graphics/Images/wallH.png"), XPOS, YPOS + TILE_SIZE, TILE_SIZE, TILE_SEPARATION);
		wall->setClickable(false);
		wall->setHoverable(false);
		floorContainer->addObject(wall);
	}

	double TOKEN_SIZE = TILE_SIZE / 4.5;

	alarmToken = new Image(string("./Graphics/Images/Tokens/AlarmToken.png"), XPOS + 0 * TOKEN_SIZE, YPOS + TILE_SIZE - TOKEN_SIZE, TOKEN_SIZE, TOKEN_SIZE);
	alarmToken->setVisible(false);
	alarmToken->setHoverable(false);
	alarmToken->setClickable(false);
	floorContainer->addObject(alarmToken);

	/*crackToken = new Image(string("../Game/Graphics/Images/Tokens/Crack token.png"), XPOS + 1 * TOKEN_SIZE, YPOS + TILE_SIZE - TOKEN_SIZE, TOKEN_SIZE, TOKEN_SIZE);
	crackToken->setVisible(false);
	crackToken->setHoverable(false);
	crackToken->setClickable(false);
	floorContainer->addObject(crackToken);*/

	crowToken = new Image(string("../Game/Graphics/Images/Tokens/Crow Token.png"), XPOS + 2 * TOKEN_SIZE, YPOS + TILE_SIZE - TOKEN_SIZE, TOKEN_SIZE, TOKEN_SIZE);
	crowToken->setVisible(false);
	crowToken->setHoverable(false);
	crowToken->setClickable(false);
	floorContainer->addObject(crowToken);

	stairToken = new Image(string("../Game/Graphics/Images/Tokens/StairToken.png"), XPOS + 3 * TOKEN_SIZE, YPOS + TILE_SIZE - TOKEN_SIZE, TOKEN_SIZE, TOKEN_SIZE);
	stairToken->setVisible(false);
	stairToken->setHoverable(false);
	stairToken->setClickable(false);
	floorContainer->addObject(stairToken);

	if (tile->is(KEYPAD))
	{
		openToken = new Image(string("../Game/Graphics/Images/Tokens/Open token.png"), XPOS + 3 * TOKEN_SIZE, YPOS + TILE_SIZE - TOKEN_SIZE, TOKEN_SIZE, TOKEN_SIZE);
		openToken->setVisible(false);
		openToken->setHoverable(false);
		openToken->setClickable(false);
		floorContainer->addObject(openToken);
	}
	else openToken = nullptr;

	if (tile->is(COMPUTER_ROOM_F) || tile->is(COMPUTER_ROOM_L) || tile->is(COMPUTER_ROOM_M))
	{
		for (int i = 0; i < 6; i++)
		{
			if (i <= 2)
				hackTokens.push_back(new Image(string("../Game/Graphics/Images/Tokens/Hack token.png"), XPOS + 0 * TOKEN_SIZE + i*TOKEN_SIZE / 2, YPOS + TILE_SIZE - TOKEN_SIZE, TOKEN_SIZE, TOKEN_SIZE));
			if (i > 2)
				hackTokens.push_back(new Image(string("../Game/Graphics/Images/Tokens/Hack token.png"), XPOS + 0 * TOKEN_SIZE + (i - 2)* TOKEN_SIZE / 2, YPOS + TILE_SIZE - 2 * TOKEN_SIZE, TOKEN_SIZE, TOKEN_SIZE));
			hackTokens.back()->setVisible(false);
			hackTokens.back()->setHoverable(false);
			hackTokens.back()->setClickable(false);
			floorContainer->addObject(hackTokens.back());
		}
	}

	

	persianKitty = new Image(string("../Game/Graphics/Images/Tokens/Persian kitty.png"), XPOS + 3 * TOKEN_SIZE, YPOS + TILE_SIZE - TOKEN_SIZE, TOKEN_SIZE, TOKEN_SIZE);
	persianKitty->setVisible(false);
	persianKitty->setHoverable(false);
	persianKitty->setClickable(false);
	floorContainer->addObject(persianKitty);

	goldBar = new Image(string("../Game/Graphics/Images/Tokens/Gold Bar.png"), XPOS + 2 * TOKEN_SIZE, YPOS + TILE_SIZE - TOKEN_SIZE, TOKEN_SIZE, TOKEN_SIZE);
	goldBar->setVisible(false);
	goldBar->setHoverable(false);
	goldBar->setClickable(false);
	floorContainer->addObject(goldBar);

	flipped = false;
	cracked = false;
	tile->attach(this);

#ifdef DEBUG_TILES
	tile->flip();
	tile->debugFlip();
#endif // All tiles are set facing up (picture only)

}

void TileObserver::showSafeNumber()
{
	string path;
	if (tile->isFlipped())
		path = string("./Graphics/Images/Safe numbers/7SEG_") + to_string(tile->getSafeNumber()) + string(".jpg");
	else
		path = string("./Graphics/Images/Safe numbers/7SEG_OFF.jpg");
	int i = tile->row();
	int j = tile->col();
	safeNumber = new Image(path, TILE_XPOS[i][j] + TILE_SIZE - NUMBER_WIDTH, TILE_YPOS[i][j] + TILE_SIZE - NUMBER_HEIGHT, NUMBER_WIDTH, NUMBER_HEIGHT);
	safeNumber->setClickable(false);
	safeNumber->setHoverable(false);
	floorContainer->addObject(safeNumber);
}

// Updates the tile image, including the tokens in it
void TileObserver::update()
{
	if (flipped != tile->isFlipped() && tileCard->hasAnimation()==false)
	{
		tileCard->addAnimation(new FlipAnimation(tileCard,0.4));
		flipped = tile->isFlipped();
		if (safeNumber != nullptr)
			safeNumber->load(string("./Graphics/Images/Safe numbers/7SEG_") + to_string(tile->getSafeNumber()) + string(".jpg"), true);
	}

	if (safeNumber != nullptr && cracked != tile->hasCrackToken())
	{
		cracked = tile->hasCrackToken();
		safeNumber->load(string("./Graphics/Images/Safe numbers/7SEG_") + to_string(tile->getSafeNumber()) + string("_GREEN.jpg"), true);
	}

	if (tile->hasAlarm() != alarmToken->isVisible())
	{
		if (tile->hasAlarm())
			alarmToken->setVisible(true);
		else
			alarmToken->setVisible(false);
	}

	/*if (tile->hasCrackToken() != crackToken->isVisible())
	{
		if (tile->hasCrackToken())
			crackToken->setVisible(true);
		else
			crackToken->setVisible(false);
	}*/

	if (tile->hasCrowToken() != crowToken->isVisible())
	{
		if (tile->hasCrowToken())
			crowToken->setVisible(true);
		else
			crowToken->setVisible(false);
	}

	if (tile->isFlipped() && tile->hasStairToken() != stairToken->isVisible())
	{
		if (tile->hasStairToken())
			stairToken->setVisible(true);
		else
			stairToken->setVisible(false);
	}
	if (tile->isFlipped() && tile->getHackTokens() > 0 && (tile->is(COMPUTER_ROOM_F) || tile->is(COMPUTER_ROOM_L) || tile->is(COMPUTER_ROOM_M)))
	{
		for (auto &it : hackTokens)
			it->setVisible(false);
		for (int i = 0; i < tile->getHackTokens(); i++)
		{
			hackTokens[i]->setVisible(true);
		}
	}

	if (tile->isFlipped() && ((Keypad *)tile)->keyDecoded() && tile->is(KEYPAD))
	{
		openToken->setVisible(true);
	}

	if (tile->hasXLoot(PERSIAN_KITTY) != hasKitty)
	{
		hasKitty = tile->hasXLoot(PERSIAN_KITTY);
		if(hasKitty)
			persianKitty->setVisible(true);
		else
			persianKitty->setVisible(false);
	}
		
	if (tile->hasXLoot(GOLD_BAR) != hasGoldBar)
	{
		hasGoldBar = tile->hasXLoot(GOLD_BAR);
		if (hasGoldBar)
			goldBar->setVisible(true);
		else
			goldBar->setVisible(false);
	}
		
}

void TileObserver::zoom()
{
	if (tile->isFlipped())
	{
		zoomedCard->setVisible(true);
		zoomedCard->addAnimation(new MoveAndZoomAnimation(FLOOR_XPOS[tile->floor()] + TILE_A1_XPOS, FLOOR_YPOS + TILE_A1_YPOS, TILE_GRID_SIZE, TILE_GRID_SIZE, 0.3));
	}
}

void TileObserver::unZoom()
{
	if (zoomedCard->hasAnimation())
		zoomedCard->deleteAnimation();
	zoomedCard->addAnimation(new MoveAndZoomAnimation(FLOOR_XPOS[tile->floor()] + TILE_XPOS[tile->row()][tile->col()], FLOOR_YPOS + TILE_YPOS[tile->row()][tile->col()], TILE_SIZE, TILE_SIZE,0.3,true));
}

double TileObserver::size()
{
	return tileCard->getHeight();
}

double TileObserver::xpos()
{
	return tileCard->getPos().first;
}

double TileObserver::ypos()
{
	return tileCard->getPos().second;
}

TileObserver::~TileObserver()
{
	if (tileCard != nullptr)
	{
		floorContainer->removeObject(tileCard);
		delete tileCard;
	}
}