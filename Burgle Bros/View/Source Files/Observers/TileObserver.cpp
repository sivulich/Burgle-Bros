#include "../../Header Files/Observers/FloorObserver.h"

static map<tileType, Image> images = {	{ATRIUM,Image(string("../View/Images/Tiles/Tile - Atrium.jpg"))},
										{CAMERA,Image(string("../View/Images/Tiles/Tile - Camera.jpg")) },
										{COMPUTER_ROOM_F,Image(string("../View/Images/Tiles/Tile - Computer Room (Fingerprint).jpg")) },
										{COMPUTER_ROOM_L,Image(string("../View/Images/Tiles/Tile - Computer Room (Laser).jpg")) },
										{COMPUTER_ROOM_M,Image(string("../View/Images/Tiles/Tile - Computer Room (Motion).jpg")) },
										{DEADBOLT,Image(string("../View/Images/Tiles/Tile - Deadbolt.jpg")) },
										{FINGERPRINT,Image(string("../View/Images/Tiles/Tile - Fingerprint.jpg")) },
										{FOYER,Image(string("../View/Images/Tiles/Tile - Foyer.jpg")) },
										{KEYPAD,Image(string("../View/Images/Tiles/Tile - Keypad.jpg")) },
										{LABORATORY,Image(string("../View/Images/Tiles/Tile - Laboratory.jpg")) },
										{LASER,Image(string("../View/Images/Tiles/Tile - Laser.jpg")) },
										{LAVATORY,Image(string("../View/Images/Tiles/Tile - Lavatory.jpg")) },
										{MOTION,Image(string("../View/Images/Tiles/Tile - Motion.jpg")) },
										{SAFE,Image(string("../View/Images/Tiles/Tile - Scanner.jpg")) },
										{SECRET_DOOR,Image(string("../View/Images/Tiles/Tile - Secret Door.jpg")) },
										{SERVICE_DUCT,Image(string("../View/Images/Tiles/Tile - Service Duct.jpg")) },
										{STAIR,Image(string("../View/Images/Tiles/Tile - Stairs.jpg")) },
										{THERMO,Image(string("../View/Images/Tiles/Tile - Thermo.jpg")) },
										{WALKWAY,Image(string("../View/Images/Tiles/Tile - Walkway.jpg")) }
};

static vector<Image> tokens = { Image(string("../View/Images/AlarmToken.png")),Image(string("../View/Images/CrackToken.png")) ,Image(string("../View/Images/CrowToken.png")) };
static Image reverseTile(string("../View/Images/Tiles/Tile - Reverse.jpg"));

TileObserver::TileObserver(Tile* t, Container* p)
{
	tile = t;
	Coord coord = tile->getPos();
	toDraw = new Container(700, 700);
	string des = string("A") + to_string(coord.row + 1) + string("F") + to_string(coord.floor);
	des[0] + coord.col;
	toDraw->setName(des);
	toDraw->setPosition(coord.row*p->getHeight() / 4, coord.col*p->getWidth() / 4);
	toDraw->setScale(double(p->getWidth()) / 4.0 / double(toDraw->getWidth()));
	parent = p;
	parent->addObject(toDraw);
	images[tile->getType()].setScale(0.9*double(toDraw->getWidth()) / images[tile->getType()].getWidth());
	reverseTile.setScale(0.9*double(toDraw->getWidth()) / reverseTile.getWidth());
	toDraw->onlyMe(true);
	if (tile->isFlipped() == true)
		toDraw->addObject(&images[tile->getType()]);
	else
		toDraw->addObject(&reverseTile);

	for (int i = 0; i < 3; i++)
	{
		tokens[i].setScale(150 / tokens[0].getWidth());
		if (i == 0)
			tokens[i].setPosition(0, 0);
		else if (i == 1)
			tokens[i].setPosition(0, toDraw->getWidth() - tokens[i].getWidth());
		else
			tokens[i].setPosition( toDraw->getHeight() - tokens[i].getWidth(),0);
	}
	tile->attach(this);
}
void
TileObserver::update()
{
	if (tile->isFlipped() == true)
	{
		if (toDraw->contains(&images[tile->getType()]) == false)
		{
			toDraw->clear();
			toDraw->addObject(&images[tile->getType()]);
		}
		
	}
	if (tile->hasAlarm() == true && toDraw->contains(&tokens[0])==false)
	{
		toDraw->addObject(&tokens[0]);
	}
	else if(tile->hasAlarm() == false)
		toDraw->removeObject(&tokens[0]);

	if (tile->hasCrackToken() == true && toDraw->contains(&tokens[1])==false)
	{
		toDraw->addObject(&tokens[1]);
	}
	else if(tile->hasCrackToken() == false)
		toDraw->removeObject(&tokens[1]);

	if (tile->hasCrowToken() == true && toDraw->contains(&tokens[2])==false)
	{
		toDraw->addObject(&tokens[2]);
	}
	else if(tile->hasCrowToken() == false)
		toDraw->removeObject(&tokens[2]);
}
TileObserver::~TileObserver()
{
	if (toDraw != nullptr)
	{
		toDraw->clear();
		parent->removeObject(toDraw);
		delete toDraw;
	}
}