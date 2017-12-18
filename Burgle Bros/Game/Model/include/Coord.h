#pragma once
#include <ostream>
#include <vector>
#include <iostream>

#define NPOS Coord(5,5,5)

class Coord
{
public:
	Coord() {};
	Coord(unsigned f, unsigned c, unsigned r) : col(c), row(r), floor(f) {};
	unsigned col, row, floor;

	bool operator==(const Coord& other)
	{
		return (col == other.col && row == other.row && floor == other.floor);
	}

	bool operator!=(const Coord& other)
	{
		return (col != other.col || row != other.row || floor != other.floor);
	}


	friend std::ostream& operator<< (std::ostream &os, const Coord &c)
	{
		os << char('A' + c.col) << c.row + 1 << "F" << c.floor ;
		return os;
	}

	static void printVec(std::vector<Coord>& c)
	{
		if (c.empty() == false)
		{
			for (auto i = c.begin(); i != c.end(); ++i)
				std::cout << *i << ' ';
		}
	}

};



