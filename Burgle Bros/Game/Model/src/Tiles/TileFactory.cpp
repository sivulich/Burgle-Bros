#include ".././Tiles/TileFactory.h"


Tile* TileFactory::newTile(tileType type,int f, int x, int y)
{
	switch (type)
	{
	case ATRIUM:
		return new Atrium(f, x, y);
	case CAMERA:
		return new Camera(f, x, y);
	case COMPUTER_ROOM_F:
		return new ComputerRoomF(f, x, y);
	case COMPUTER_ROOM_L:
		return new ComputerRoomL(f, x, y);
	case COMPUTER_ROOM_M:
		return new ComputerRoomM(f, x, y);
	case DEADBOLT:
		return new Deadbolt(f, x, y);
	case FINGERPRINT:
		return new Fingerprint(f, x, y);
	case FOYER:
		return new Foyer(f, x, y);
	case KEYPAD:
		return new Keypad(f, x, y);
	case LABORATORY:
		return new Laboratory(f, x, y);
	case LASER:
		return new Laser(f, x, y);
	case LAVATORY:
		return new Lavatory(f, x, y);
	case MOTION:
		return new Motion(f, x, y);
	case SAFE:
		return new Safe(f, x, y);
	case SCANNER:
		return new Scanner(f, x, y);
	case SECRET_DOOR:
		return new SecretDoor(f, x, y);
	case SERVICE_DUCT:
		return new ServiceDuct(f, x, y);
	case STAIR:
		return new Stair(f, x, y);
	case THERMO:
		return new Thermo(f, x, y);
	case WALKWAY:
		return new Walkway(f, x, y);
	default:
		return nullptr;
	};
}
