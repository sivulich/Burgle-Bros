#pragma once
#include "Configs.h"
#include "Player.h"

DEFINE_ENUM_WITH_CONVERSIONS(lootType,
(TIARA, 0x30)
(PERSIAN_KITTY)
(PAINTING)
(MIRROR)
(KEYCARD)
(ISOTOPE)
(GEMSTONE)
(CURSED_GOBLET)
(CHIHUAHUA)
(GOLD_BAR))

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
	void pick(Player* p);
	

private:
	lootType type;
	Coord pos;
	bool taken;
	Player * owner;
};

