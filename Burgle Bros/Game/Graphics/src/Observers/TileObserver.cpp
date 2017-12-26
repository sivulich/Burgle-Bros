#include "./FloorObserver.h"

static map<tileType, string> images = {	{ATRIUM,string("../Game/Graphics/Images/Tiles/Tile - Atrium.png")},
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

TileObserver::TileObserver(Tile* t, Container* floorContainer)
{
	tile = t;
	
	this->floorContainer = floorContainer;

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

	tileCard = new Card(images[tile->getType()], string("../Game/Graphics/Images/Tiles/Tile - Reverse.png"),XPOS,YPOS,TILE_SIZE,TILE_SIZE,tile->isFlipped());

	// Set name of the tile (its coord)
	string name = string("COORDA") + to_string(coord.row + 1) + string("F") + to_string(coord.floor);
	name[5] += coord.col;
	tileCard->setName(name);

	// Add to parent container
	floorContainer->addObject(tileCard);
	
	// Now check for walls
	Image * wall = nullptr;
	if (tile->hasEastWall())
	{
		wall = new Image(string("../Game/Graphics/Images/wallV.png"), XPOS + TILE_SIZE, YPOS, TILE_SEPARATION, TILE_SIZE);
		wall->setClickable(false);
		wall->setHoverable(false);
		floorContainer->addObject(wall);
	}
			
	if (tile->hasSouthWall() == true)
	{
		wall = new Image(string("../Game/Graphics/Images/wallH.png"), XPOS, YPOS + TILE_SIZE, TILE_SIZE, TILE_SEPARATION);
		wall->setClickable(false);
		wall->setHoverable(false);
		floorContainer->addObject(wall);
	}
	double TOKEN_SIZE = TILE_SIZE / 4.5;

	alarmToken = new Image(string("../Game/Graphics/Images/AlarmToken.png"), XPOS + 0*TOKEN_SIZE, YPOS + TILE_SIZE - TOKEN_SIZE, TOKEN_SIZE, TOKEN_SIZE);
	alarmToken->setVisible(false);
	alarmToken->setHoverable(false);
	alarmToken->setClickable(false);
	floorContainer->addObject(alarmToken);

	crackToken = new Image(string("../Game/Graphics/Images/CrackToken.png"), XPOS + 1*TOKEN_SIZE, YPOS + TILE_SIZE - TOKEN_SIZE, TOKEN_SIZE, TOKEN_SIZE);
	crackToken->setVisible(false);
	crackToken->setHoverable(false);
	crackToken->setClickable(false);
	floorContainer->addObject(crackToken);

	crowToken = new Image(string("../Game/Graphics/Images/CrowToken.png"), XPOS + 2*TOKEN_SIZE, YPOS + TILE_SIZE - TOKEN_SIZE, TOKEN_SIZE, TOKEN_SIZE);
	crowToken->setVisible(false);
	crowToken->setHoverable(false);
	crowToken->setClickable(false);
	floorContainer->addObject(crowToken);

	stairToken = new Image(string("../Game/Graphics/Images/StairToken.png"), XPOS + 3*TOKEN_SIZE , YPOS + TILE_SIZE - TOKEN_SIZE, TOKEN_SIZE, TOKEN_SIZE);
	stairToken->setVisible(false);
	stairToken->setHoverable(false);
	stairToken->setClickable(false);
	floorContainer->addObject(stairToken);

	flipped = false;
	tile->attach(this);

}
// Updates the tile image, including the tokens in it
void TileObserver::update()
{
	if ( flipped != tile->isFlipped() )
	{
		//tileCard->addAnimation(new FlipAnimation(tileCard,1.0));
		tileCard->flip();
		flipped = tile->isFlipped();
	}

	if (tile->hasAlarm() != alarmToken->isVisible())
	{
		if (tile->hasAlarm())
			alarmToken->setVisible(true);
		else
			alarmToken->setVisible(false);
	}

	if (tile->hasCrackToken() != crackToken->isVisible())
	{
		if (tile->hasCrackToken())
			crackToken->setVisible(true);
		else
			crackToken->setVisible(false);
	}

	if (tile->hasCrowToken() != crowToken->isVisible())
	{
		if (tile->hasCrowToken())
			crowToken->setVisible(true);
		else
			crowToken->setVisible(false);
	}
	
	if (tile->isFlipped() && tile->hasStairToken()!=stairToken->isVisible())
	{
		if (tile->hasStairToken())
			stairToken->setVisible(true);
		else
			stairToken->setVisible(false);
	}
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