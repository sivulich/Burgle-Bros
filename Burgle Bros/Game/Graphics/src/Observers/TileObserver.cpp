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

	tileCard = new Card(images[tile->getType()], string("../Game/Graphics/Images/Tiles/Tile - Reverse.png"),XPOS,YPOS,TILE_SIZE,TILE_SIZE);
	

	//tileCard = new Card(images[tile->getType()], string("../Game/Graphics/Images/Tiles/Tile - Reverse.png"));
	//tileCard->setPosition(YPOS, XPOS);
	//tileCard->setSize(TILE_SIZE, TILE_SIZE);

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
		wall->setNormalTone(Color(0.8f, 0.8f, 0.8f, 1.0f));
		floorContainer->addObject(wall);
	}
			
	if (tile->hasSouthWall() == true)
	{
		wall = new Image(string("../Game/Graphics/Images/wallH.png"), XPOS, YPOS + TILE_SIZE, TILE_SIZE, TILE_SEPARATION);
		wall->setClickable(false);
		wall->setHoverable(false);
		wall->setNormalTone(Color(0.8f, 0.8f, 0.8f, 1.0f));
		floorContainer->addObject(wall);
	}


	
	/*tokens = { Image(string("../Game/Graphics/Images/AlarmToken.png")),Image(string("../Game/Graphics/Images/CrackToken.png")) ,Image(string("../Game/Graphics/Images/CrowToken.png")),Image(string("../Game/Graphics/Images/StairToken.png")) };

	for (int i = 0; i < 4; i++)
		tokens[i].setScale(front->getScale()*front->getWidth()*0.3 / tokens[i].getWidth());


	tokens[0].setPosition(front->getPos().first, front->getPos().second);
	tokens[1].setPosition(front->getPos().first, front->getPos().second + front->getScale()*front->getWidth() - tokens[1].getScale()*tokens[1].getWidth());
	tokens[2].setPosition(front->getPos().first + front->getScale()*front->getHeight() - tokens[2].getScale()*tokens[2].getWidth(), front->getPos().second);
	tokens[3].setPosition(front->getPos().first + front->getScale()*front->getHeight() - tokens[3].getScale()*tokens[3].getWidth(), front->getPos().second + front->getScale()*front->getWidth() - tokens[3].getScale()*tokens[3].getWidth());
	*/
	
	tile->attach(this);

}
void TileObserver::update()
{
	if ( flipped != tile->isFlipped() )
	{
		//tileCard->addAnimation(new FlipAnimation(tileCard,1.0));
		tileCard->flip();
		flipped = tile->isFlipped();
	}

	/*if (tile->hasAlarm() == true && parent->contains(&tokens[0])==false)
	{
		parent->addObject(&tokens[0]);
	}
	else if(tile->hasAlarm() == false)
		parent->removeObject(&tokens[0]);

	if (tile->hasCrackToken() == true && parent->contains(&tokens[1])==false)
	{
		parent->addObject(&tokens[1]);
	}
	else if(tile->hasCrackToken() == false)
		parent->removeObject(&tokens[1]);

	if (tile->hasCrowToken() == true && parent->contains(&tokens[2])==false)
	{
		parent->addObject(&tokens[2]);
	}
	else if(tile->hasCrowToken() == false)
		parent->removeObject(&tokens[2]);

	if (tile->isFlipped()==true && tile->hasStairToken() == true && parent->contains(&tokens[3]) == false)
	{
		parent->addObject(&tokens[3]);
	}
	else if (tile->hasStairToken() == false)
		parent->removeObject(&tokens[3]);*/
}

TileObserver::~TileObserver()
{
	if (tileCard != nullptr)
	{
		floorContainer->removeObject(tileCard);
		delete tileCard;
	}
}