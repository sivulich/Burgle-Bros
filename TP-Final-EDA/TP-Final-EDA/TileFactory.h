#pragma once
#include "Atrium.h"
#include "Camera.h"
#include "ComputerRoomF.h"
#include "ComputerRoomL.h"
#include "ComputerRoomM.h"
#include "Deadbolt.h"
#include "Fingerprint.h"
#include "Foyer.h"
#include "Keypad.h"
#include "Laboratory.h"
#include "Laser.h"
#include "Lavatory.h"
#include "Motion.h"
#include "Safe.h"
#include "Scanner.h"
#include "SecretDoor.h"
#include "ServiceDuct.h"
#include "Stair.h"
#include "Thermo.h"
#include "Tile.h"
#include "Walkway.h"
 
class TileFactory
{
public:
	TileFactory() {};
	~TileFactory() {};

	static Tile* newTile(tileType type)
	{
		switch (type)
		{
		case ATRIUM:
			return new Atrium;
		case CAMERA:
			return new Camera;
		case COMPUTER_ROOM_F:
			return new ComputerRoomF;
		case COMPUTER_ROOM_L:
			return new ComputerRoomL;
		case COMPUTER_ROOM_M:
			return new ComputerRoomM;
		case DEADBOLT:
			return new Deadbolt;
		case FINGERPRINT:
			return new Fingerprint;
		case FOYER:
			return new Foyer;
		case KEYPAD:
			return new Keypad;
		case LABORATORY:
			return new Laboratory;
		case LASER:
			return new Laser;
		case LAVATORY:
			return new Lavatory;
		case MOTION:
			return new Motion;
		case SAFE:
			return new Safe;
		case SCANNER:
			return new Scanner;
		case SECRET_DOOR:
			return new SecretDoor;
		case SERVICE_DUCT:
			return new ServiceDuct;
		case STAIR:
			return new Stair;
		case THERMO:
			return new Thermo;
		case WALKWAY:
			return new Walkway;
		default:
			return nullptr;
		}
	};
}