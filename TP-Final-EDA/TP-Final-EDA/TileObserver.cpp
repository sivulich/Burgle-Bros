#include "TileObserver.h"


map<tileType, string> imagesPath = {	{ATRIUM,"./Images/Tile - Atrium.jpg"},
										{CAMERA,"./Images/Tile - Camera.jpg"},
										{COMPUTER_ROOM_F,"./Images/Tile - Computer Room (Fingerprint).jpg"},
										{COMPUTER_ROOM_L,"./Images/Tile - Computer Room (Laser).jpg"},
										{COMPUTER_ROOM_M,"./Images/Tile - Computer Room (Motion).jpg"},
										{DEADBOLT,"./Images/Tile - Deadbolt.jpg"},
										{FINGERPRINT,"./Images/Tile - Fingerprint.jpg"},
										{FOYER,"./Images/Tile - Foyer.jpg"},
										{KEYPAD,"./Images/Tile - Keypad.jpg"},
										{LABORATORY,"./Images/Tile - Laboratory.jpg"},
										{LASER,"./Images/Tile - Laser.jpg"},
										{LAVATORY,"./Images/Tile - Lavatory.jpg"},
										{MOTION,"./Images/Tile - Motion.jpg"},
										{SAFE,"./Images/Tile - Scanner.jpg"},
										{SECRET_DOOR,"./Images/Tile - Secret Door.jpg"},
										{SERVICE_DUCT,"./Images/Tile - Service Duct.jpg"},
										{STAIR,"./Images/Tile - Stair.jpg"},
										{THERMO,"./Images/Tile - Thermo.jpg"},
										{WALKWAY,"./Images/Tile - Walkway.jpg"}
};

TileObserver::TileObserver(Tile* t, Container* p)
{
	tile = t;
	front = new Image(imagesPath[tile->getType()]);
	back = new Image(string("./Images/Tile - Reverse.jpg"));
	Coord coord = tile->getPos();
	front->setName(to_string(coord.col + 'A') + to_string(coord.row) + string("F") + to_string(coord.floor) + string(" front"));
	back->setName(to_string(coord.col + 'A') + to_string(coord.row)+string("F")+to_string(coord.floor) + string(" back"));
	front->setPosition(coord.row*p->getHeight() / 4, coord.col*p->getWidth() / 4);
	back->setPosition(coord.row*p->getHeight() / 4, coord.col*p->getWidth() / 4);
	front->setScale(double(p->getWidth()) / 4.0 / double(front->getWidth()));
	back->setScale(double(p->getWidth()) / 4.0 / double(back->getWidth()));
	parent = p;
	if (tile->isFlipped() == true)
	{
		parent->addObject(front);
		set = true;
	}
	else
	{
		parent->addObject(back);
		set = false;
	}
}
void
TileObserver::update()
{
	if (set == false && tile->isFlipped() == true)
	{
		set = true;
		parent->removeObject(back);
		parent->addObject(front);
	}
}
TileObserver::~TileObserver()
{
	delete back;
	delete front;
}