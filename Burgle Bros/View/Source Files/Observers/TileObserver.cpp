#include "../../Header Files/Observers/FloorObserver.h"


static map<tileType, Image> images = {	{ATRIUM,Image(string("../../Images/Tiles/Tile - Atrium.jpg"))},
										{CAMERA,Image(string("../../Images/Tiles/Tile - Camera.jpg")) },
										{COMPUTER_ROOM_F,Image(string("../../Images/Tiles/Tile - Computer Room (Fingerprint).jpg")) },
										{COMPUTER_ROOM_L,Image(string("../../Images/Tiles/Tile - Computer Room (Laser).jpg")) },
										{COMPUTER_ROOM_M,Image(string("../../Images/Tiles/Tile - Computer Room (Motion).jpg")) },
										{DEADBOLT,Image(string("../../Images/Tiles/Tile - Deadbolt.jpg")) },
										{FINGERPRINT,Image(string("../../Images/Tiles/Tile - Fingerprint.jpg")) },
										{FOYER,Image(string("../../Images/Tiles/Tile - Foyer.jpg")) },
										{KEYPAD,Image(string("../../Images/Tiles/Tile - Keypad.jpg")) },
										{LABORATORY,Image(string("../../Images/Tiles/Tile - Laboratory.jpg")) },
										{LASER,Image(string("../../Images/Tiles/Tile - Laser.jpg")) },
										{LAVATORY,Image(string("../../Images/Tiles/Tile - Lavatory.jpg")) },
										{MOTION,Image(string("../../Images/Tiles/Tile - Motion.jpg")) },
										{SAFE,Image(string("../../Images/Tiles/Tile - Scanner.jpg")) },
										{SECRET_DOOR,Image(string("../../Images/Tiles/Tile - Secret Door.jpg")) },
										{SERVICE_DUCT,Image(string("../../Images/Tiles/Tile - Service Duct.jpg")) },
										{STAIR,Image(string("../../Images/Tiles/Tile - Stair.jpg")) },
										{THERMO,Image(string("../../Images/Tiles/Tile - Thermo.jpg")) },
										{WALKWAY,Image(string("../../Images/Tiles/Tile - Walkway.jpg")) },
};

static vector<Image> tokens = { Image(string("../../Images/AlarmToken.png")),Image(string("../../Images/CrackToken.png")) ,Image(string("../../Images/CrowToken.png")) };
static Image reverseTile(string("./Images/Tile - Reverse.jpg"));

TileObserver::TileObserver(Tile* t, Container* p)
{
	tile = t;
	Coord coord = tile->getPos();
	toDraw = new Container(700, 700);
	toDraw->setName(to_string(coord.col + 'A') + to_string(coord.row+1) + string("F") + to_string(coord.floor));
	toDraw->setPosition(coord.row*p->getHeight() / 4, coord.col*p->getWidth() / 4);
	toDraw->setScale(double(p->getWidth()) / 4.0 / double(toDraw->getWidth()));
	parent = p;
	parent->addObject(toDraw);
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
	if (tile->hasAlarm() == true && toDraw->contains(&tokens[0]))
	{
		toDraw->addObject(&tokens[0]);
	}
	else
		toDraw->removeObject(&tokens[0]);

	if (tile->hasCrackToken() == true && toDraw->contains(&tokens[1]))
	{
		toDraw->addObject(&tokens[1]);
	}
	else
		toDraw->removeObject(&tokens[1]);

	if (tile->hasCrowToken() == true && toDraw->contains(&tokens[2]))
	{
		toDraw->addObject(&tokens[2]);
	}
	else
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