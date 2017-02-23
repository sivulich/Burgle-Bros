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

	static Tile* newTile(tileType type,int f, int x, int y);
	//static Tile* newTile(tileType type);

};