#include "Stair.h"

vector<Coord> Stair::whereCanIPeek() {
	vector<Coord> v = adjacent;
	v.erase(remove_if(v.begin(), v.end(),
		[&](const Coord t)-> bool { return t.floor == 3; }),
		v.end());
	return v;

}