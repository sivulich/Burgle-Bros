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

	struct move : BaseEvent
	{
		typedef int CoordProp;
		move() :c(NPOS), safeNumber(0) {};
		move(Coord p, unsigned int n) :c(p), safeNumber(n) {};
		Coord c;
		unsigned int safeNumber;
	};
	struct moveGuard : BaseEvent	{};
	struct peek : BaseEvent
	{
		typedef int CoordProp;
		peek() :c(NPOS),safeNumber(0) {};
		peek(Coord p, unsigned int n) :c(p),safeNumber(n) {};
		Coord c;
		unsigned int safeNumber;
	};
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
	struct close : BaseEvent
	{
		close() : remote(false) {};
		close(bool b) : remote(b) {};
		bool remote;
	};
	struct errorReceived : BaseEvent {};
	struct errorHandled : BaseEvent {};
	struct offerLoot : BaseEvent
	{
		offerLoot() : type(NO_LOOT_TYPE) {};
		offerLoot(lootType t) : type(t) {};
		lootType type;
	};
	struct requestLoot : BaseEvent
	{
		requestLoot() : type(NO_LOOT_TYPE) {};
		requestLoot(lootType t) : type(t) {};
		lootType type;
	};
	struct lootType : BaseEvent
	{
		lootType(string s) :type(s) {};
		string type;
	};
	struct showAlarm : BaseEvent {};
	struct createAlarm : BaseEvent
	{
		typedef int CoordProp;
		createAlarm() :c(NPOS) {};
		createAlarm(Coord p) : c(p) {};
		Coord c;
	};
	struct placeCrow : BaseEvent
	{
		typedef int CoordProp;
		placeCrow() :c(NPOS) {};
		placeCrow(Coord p) : c(p) {};
		Coord c;
	};
	struct spyPatrol : BaseEvent 
	{
		typedef int CoordProp;
		spyPatrol() :c(NPOS), tb('A'){};
		spyPatrol(Coord p,char b) : c(p), tb(b){};
		Coord c;
		char tb;
	};
	struct pickUpLoot : BaseEvent {};
	struct yes : BaseEvent {};
	struct no : BaseEvent {};
	struct done : BaseEvent {};
	struct ack : BaseEvent {};
	struct waitForNetwork : BaseEvent {};
	struct ok : BaseEvent {};
	struct render : BaseEvent {};
	struct coord : BaseEvent
	{
		typedef int CoordProp;
		coord(Coord p) :c(p),safeNumber(0) {};
		coord(Coord p,unsigned int n) :c(p),safeNumber(n) {};
		Coord c;
		unsigned int safeNumber;
	};

}