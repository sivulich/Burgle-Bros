#pragma once
#include <ostream>

#define NPOS Coord(5,5,5)
class Coord
{
public:
	Coord() {};
	Coord(unsigned f, unsigned c, unsigned r) : col(c), row(r), floor(f) {};
	unsigned col, row, floor;

	bool operator==(const Coord& other)
	{
		return (col==other.col && row==other.row && floor==other.floor);
	}

	friend std::ostream& operator<< (std::ostream &os, const Coord &c)
	{
		os << "Floor: " << c.floor << " Col: " << c.col << " Row: " << c.row << std::endl;
		return os;
	}
};


