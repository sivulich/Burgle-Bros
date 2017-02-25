#pragma once
#include "../Configs.h"
#include "../PlayerInterface.h"


class Loot
{
public:
	Loot();
	~Loot();

	Coord getPos() { return pos; };
	void setPos(Coord p) { pos = p; };
	lootType getType() { return  type; };
	bool is(lootType t) { return t == type; };
	bool isTaken() { return taken; };
	void drop();
	//void pick(Player* p); Lo comento porque si no hay circular dependencies, esto puede ir en la clase heredada
	

private:
	lootType type;
	Coord pos;
	bool taken;
	PlayerInterface * owner;
};

