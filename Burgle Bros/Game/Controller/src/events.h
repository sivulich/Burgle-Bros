#pragma once
#include <vector>
//----------------------- EVENTS -----------------------------//

// Define a property for use with enable_if 
BOOST_MPL_HAS_XXX_TRAIT_DEF(CoordProp)

namespace ev {
	struct BaseEvent {};
	struct start : BaseEvent {};
	struct rules : BaseEvent {};
	struct credits : BaseEvent {};
	struct local : BaseEvent {};
	struct remote : BaseEvent {};
	struct back : BaseEvent {};
	struct next : BaseEvent {};
	struct cancel : BaseEvent {};
	struct play : BaseEvent {};
	struct connect : BaseEvent {};
	struct characterName : BaseEvent
	{
		characterName(string s) :character(s) {};
		string character;
	};

	struct movee : BaseEvent {};
	struct peek : BaseEvent {};
	struct throwDice : BaseEvent 
	{
		throwDice() {};
		throwDice(int n) :number(n) {};
		throwDice(vector<int> n) : dices(n) {};
		int number;
		vector<int> dices;
	};
	struct useToken : BaseEvent {};
	struct addToken : BaseEvent {};
	struct pass : BaseEvent {};
	struct passGuard : BaseEvent {};
	struct pause : BaseEvent {};
	struct resume : BaseEvent {};
	struct gameOver : BaseEvent {};
	struct burglarsWin : BaseEvent {};
	struct playAgain : BaseEvent {};
	struct close : BaseEvent {};
	struct errorReceived : BaseEvent {};
	struct errorHandled : BaseEvent {};
	struct offerLoot : BaseEvent {};
	struct requestLoot : BaseEvent {};
	struct lootType : BaseEvent
	{
		lootType(string s) :type(s) {};
		string type;
	};
	struct showAlarm : BaseEvent {};
	struct createAlarm : BaseEvent {};
	struct spyPatrol : BaseEvent {};
	struct placeCrow : BaseEvent {};
	struct pickUpLoot : BaseEvent {};
	struct yes : BaseEvent {};
	struct no : BaseEvent {};
	struct done : BaseEvent {};
	struct ok : BaseEvent {};
	struct render : BaseEvent {};
	struct coord : BaseEvent
	{
		typedef int CoordProp;
		coord(Coord p) :c(p) {};
		Coord c;
	};

}