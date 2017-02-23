#include "../Header Files/Coord.h"
#include <iostream>

std::ostream& operator<<(std::ostream& os, static Coord& c)
{
	os << "Floor: " << c.floor << " Col: " << c.col << " Row: " << c.row << std::endl;
	return os;
}