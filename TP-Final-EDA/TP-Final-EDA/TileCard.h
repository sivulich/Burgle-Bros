#pragma once
#include "Configs.h"
#include "Player.h"
class TileCard
{
public:
	TileCard();
	TileCard(tileType type);
	~TileCard();
	tileType getType() { return tileID; };
	void setType(tileType type) { tileID = type; };
	
	/**
	*/

private:
	tileType tileID;
	vector<string> actions;

	/**
	Return true if the player can move to the tile
	*/
	bool canMove(Player p, Coord guardPos, Coord partnerPos);
	/**
	Returns true if player can peek
	*/
	bool canPeek(Player p);


};

