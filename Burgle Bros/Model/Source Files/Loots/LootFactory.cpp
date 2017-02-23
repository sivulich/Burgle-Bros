#include "LootFactory.h"
#include "Chihuahua.h"
#include "CursedGoblet.h"
#include "Gemstone.h"
#include "GoldBar.h"
#include "Isotope.h"
#include "Keycard.h"
#include "Mirror.h"
#include "Painting.h"
#include "PersianKitty.h"
#include "Tiara.h"

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