#pragma once
#include <Configs.h>
#include "../PlayerInterface.h"
#include "../BaseCard.h"
#include <BaseModel.h>
class Loot: public BaseCard
{
public:
	Loot();
	Loot(lootType l);
	~Loot();

	Coord getPos() { return pos; };
	void setPos(Coord p) { pos = p; };
	lootType getType() { return  type; };
	bool is(lootType t) { return t == type; };
	bool isTaken() { return owner == nullptr? false : true; };
	void drop() { owner = nullptr; };
	void pick(PlayerInterface* p) { owner = p;};
	bool isLootAvailable() { return ready; };
	void lootAvailable(bool b) { ready = b; };
	bool isInsafe() { return inSafe; };
	void takeFromSafe() { inSafe = false; };
	/**
		Function called each time player moves to a new tile
	*/
	void update();
	virtual int  input(string& s1) { return 0; };
	
	

private:
	lootType type;
	bool inSafe;
	Coord pos;
	PlayerInterface * owner;
	bool ready;
};

