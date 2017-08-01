#include ".././Loots/LootFactory.h"
#include ".././Loots/Chihuahua.h"
#include ".././Loots/CursedGoblet.h"
#include ".././Loots/Gemstone.h"
#include ".././Loots/GoldBar.h"
#include ".././Loots/Isotope.h"
#include ".././Loots/Keycard.h"
#include ".././Loots/Mirror.h"
#include ".././Loots/Painting.h"
#include ".././Loots/PersianKitty.h"
#include ".././Loots/Tiara.h"

Loot* LootFactory::newLoot(lootType type)
{
	switch (type)
	{
	case TIARA:
		return new Tiara(type);
	case PERSIAN_KITTY:
		return new PersianKitty(type);
	case PAINTING:
		return new Painting(type);
	case MIRROR:
		return new Mirror(type);
	case KEYCARD:
		return new Keycard(type);
	case ISOTOPE:
		return new Isotope(type);
	case GEMSTONE:
		return new Gemstone(type);
	case CURSED_GOBLET:
		return new CursedGoblet(type);
	case CHIHUAHUA:
		return new Chihuahua(type);
	case GOLD_BAR:
		return new GoldBar(type);
	default:
		return nullptr;
	}
}