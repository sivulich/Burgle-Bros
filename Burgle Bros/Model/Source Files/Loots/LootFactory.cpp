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

static Loot* LootFactory::newTile(lootType type)
{
	switch (type)
	{
	case TIARA:
		return new Tiara;
	case PERSIAN_KITTY:
		return new PersianKitty;
	case PAINTING:
		return new Painting;
	case MIRROR:
		return new Mirror;
	case KEYCARD:
		return new Keycard;
	case ISOTOPE:
		return new Isotope;
	case GEMSTONE:
		return new Gemstone;
	case CURSED_GOBLET:
		return new CursedGoblet;
	case CHIHUAHUA:
		return new Chihuahua;
	case GOLD_BAR:
		return new GoldBar;
	default:
		return nullptr;
	}
}