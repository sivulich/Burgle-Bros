#include "../../Header Files/Observers/FloorObserver.h"

static map<tileType, Image> images = {	{ATRIUM,string("../View/Images/Tiles/Tile - Atrium.png")},
										{CAMERA,string("../View/Images/Tiles/Tile - Camera.png") },
										{COMPUTER_ROOM_F,string("../View/Images/Tiles/Tile - Computer Room (Fingerprint).png") },
										{COMPUTER_ROOM_L,string("../View/Images/Tiles/Tile - Computer Room (Laser).png") },
										{COMPUTER_ROOM_M,string("../View/Images/Tiles/Tile - Computer Room (Motion).png") },
										{DEADBOLT,string("../View/Images/Tiles/Tile - Deadbolt.png") },
										{FINGERPRINT,string("../View/Images/Tiles/Tile - Fingerprint.png") },
										{FOYER,string("../View/Images/Tiles/Tile - Foyer.png") },
										{KEYPAD,string("../View/Images/Tiles/Tile - Keypad.png") },
										{LABORATORY,string("../View/Images/Tiles/Tile - Laboratory.png") },
										{LASER,string("../View/Images/Tiles/Tile - Laser.png") },
										{LAVATORY,string("../View/Images/Tiles/Tile - Lavatory.png") },
										{MOTION,string("../View/Images/Tiles/Tile - Motion.png") },
										{SAFE,string("../View/Images/Tiles/Tile - Safe.png") },
										{SCANNER,string("../View/Images/Tiles/Tile - Scanner.png")},
										{SECRET_DOOR,string("../View/Images/Tiles/Tile - Secret Door.png") },
										{SERVICE_DUCT,string("../View/Images/Tiles/Tile - Service Duct.png") },
										{STAIR,string("../View/Images/Tiles/Tile - Stairs.png") },
										{THERMO,string("../View/Images/Tiles/Tile - Thermo.png") },
										{WALKWAY,string("../View/Images/Tiles/Tile - Walkway.png") }
};


TileObserver::TileObserver(Tile* t, Container* p)
{
	tile = t;
	parent = p;
	tokens = { Image(string("../View/Images/AlarmToken.png")),Image(string("../View/Images/CrackToken.png")) ,Image(string("../View/Images/CrowToken.png")) };
	reverseTile = new Image(string("../View/Images/Tiles/Tile - Reverse.png"));
	front = new Image(images[tile->getType()]);
	Coord coord = tile->getPos();
	string des = string("A") + to_string(coord.row + 1) + string("F") + to_string(coord.floor);
	des[0] += coord.col;
	front->setName(des);
	front->setPosition(coord.row*p->getHeight() / 4, coord.col*p->getWidth() / 4);
	front->setScale(0.9* double(p->getWidth()) / 4.0 / double(front->getWidth()));
	reverseTile->setName(des);
	reverseTile->setPosition(coord.row*p->getHeight() / 4, coord.col*p->getWidth() / 4);
	reverseTile->setScale(0.9* double(p->getWidth()) / 4.0 / double(reverseTile->getWidth()));
	if (tile->isFlipped() == true)
		parent->addObject(front);
	else
		parent->addObject(reverseTile);

	for (int i = 0; i < 3; i++)
	{
		tokens[i].setScale(front->getScale() * 150 / tokens[0].getWidth());
		if (i == 0)
			tokens[i].setPosition(front->getPos().first, front->getPos().second);
		else if (i == 1)
			tokens[i].setPosition(front->getPos().first, front->getPos().second +front->getScale()*(front->getWidth() - tokens[i].getWidth()));
		else
			tokens[i].setPosition(front->getPos().first+front->getScale()*( front->getHeight() - tokens[i].getWidth()),front->getPos().second);
	}
	tile->attach(this);
}
void
TileObserver::update()
{
	if (tile->isFlipped() == true)
	{
		if (parent->contains(front) == false)
		{
			parent->removeObject(reverseTile);
			for (auto& x : tokens)
				parent->removeObject(&x);
			parent->addObject(front);
		}
		
	}
	if (tile->hasAlarm() == true && parent->contains(&tokens[0])==false)
	{
		parent->addObject(&tokens[0]);
	}
	else if(tile->hasAlarm() == false)
		parent->removeObject(&tokens[0]);

	/*if (tile->hasCrackToken() == true && toDraw->contains(&tokens[1])==false)
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
		toDraw->removeObject(&tokens[2]);*/
}
TileObserver::~TileObserver()
{
	if (front != nullptr)
	{
		parent->removeObject(front);
		delete front;
	}
	if (reverseTile != nullptr)
	{
		parent->removeObject(reverseTile);
		delete reverseTile;
	}
}