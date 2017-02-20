#include "TileFactory.h"



TileFactory::TileFactory()
{
}


TileFactory::~TileFactory()
{
}

Tile* TileFactory::newTile(tileType type, int x, int y)
{
	switch (type)
	{
	case ATRIUM:
		return new Atrium(x, y);
	case CAMERA:
		return new Camera(x, y);
	case COMPUTER_ROOM_F:
		return new ComputerRoomF(x, y);
	case COMPUTER_ROOM_L:
		return new ComputerRoomL(x, y);
	case COMPUTER_ROOM_M:
		return new ComputerRoomM(x, y);
	case DEADBOLT:
		return new Deadbolt(x, y);
	case FINGERPRINT:
		return new Fingerprint(x, y);
	case FOYER:
		return new Foyer(x, y);
	case KEYPAD:
		return new Keypad(x, y);
	case LABORATORY:
		return new Laboratory(x, y);
	case LASER:
		return new Laser(x, y);
	case LAVATORY:
		return new Lavatory(x, y);
	case MOTION:
		return new Motion(x, y);
	case SAFE:
		return new Safe(x, y);
	case SCANNER:
		return new Scanner(x, y);
	case SECRET_DOOR:
		return new SecretDoor(x, y);
	case SERVICE_DUCT:
		return new ServiceDuct(x, y);
	case STAIR:
		return new Stair(x, y);
	case THERMO:
		return new Thermo(x, y);
	case WALKWAY:
		return new Walkway(x, y);
	default:
		return nullptr;
	};
}
