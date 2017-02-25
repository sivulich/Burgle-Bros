#include "../../Header Files/Observers/FloorObserver.h"


map<tileType, string> imagesPath = {	{ATRIUM,"../../Images/Tiles/Tile - Atrium.jpg"},
										{CAMERA,"../../Images/Tiles/Tile - Camera.jpg"},
										{COMPUTER_ROOM_F,"../../Images/Tiles/Tile - Computer Room (Fingerprint).jpg"},
										{COMPUTER_ROOM_L,"../../Images/Tiles/Tile - Computer Room (Laser).jpg"},
										{COMPUTER_ROOM_M,"../../Images/Tiles/Tile - Computer Room (Motion).jpg"},
										{DEADBOLT,"../../Images/Tiles/Tile - Deadbolt.jpg"},
										{FINGERPRINT,"../../Images/Tiles/Tile - Fingerprint.jpg"},
										{FOYER,"../../Images/Tiles/Tile - Foyer.jpg"},
										{KEYPAD,"../../Images/Tiles/Tile - Keypad.jpg"},
										{LABORATORY,"../../Images/Tiles/Tile - Laboratory.jpg"},
										{LASER,"../../Images/Tiles/Tile - Laser.jpg"},
										{LAVATORY,"../../Images/Tiles/Tile - Lavatory.jpg"},
										{MOTION,"../../Images/Tiles/Tile - Motion.jpg"},
										{SAFE,"../../Images/Tiles/Tile - Scanner.jpg"},
										{SECRET_DOOR,"../../Images/Tiles/Tile - Secret Door.jpg"},
										{SERVICE_DUCT,"../../Images/Tiles/Tile - Service Duct.jpg"},
										{STAIR,"../../Images/Tiles/Tile - Stair.jpg"},
										{THERMO,"../../Images/Tiles/Tile - Thermo.jpg"},
										{WALKWAY,"../../Images/Tiles/Tile - Walkway.jpg"}
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
	alarm = false;
	guard = false;
	player = 0;	
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