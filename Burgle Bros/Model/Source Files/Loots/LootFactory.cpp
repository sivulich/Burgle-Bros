#include "../../Header Files/Loots/LootFactory.h"
#include "../../Header Files/Loots/Chihuahua.h"
#include "../../Header Files/Loots/CursedGoblet.h"
#include "../../Header Files/Loots/Gemstone.h"
#include "../../Header Files/Loots/GoldBar.h"
#include "../../Header Files/Loots/Isotope.h"
#include "../../Header Files/Loots/Keycard.h"
#include "../../Header Files/Loots/Mirror.h"
#include "../../Header Files/Loots/Painting.h"
#include "../../Header Files/Loots/PersianKitty.h"
#include "../../Header Files/Loots/Tiara.h"

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