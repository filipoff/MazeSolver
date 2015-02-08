#include "Cell.h"

Cell::Cell() : symbol(0), pos(0, 0), gCost(0), hCost(0), fCost(0), parent(NULL) {}

Cell::Cell(char symbol, size_t rowPosition, size_t columnPosition) : symbol(symbol),
pos(rowPosition, columnPosition),gCost(0), hCost(0), fCost(0), parent(NULL) {}


Cell::Cell(const Cell& other)
{
	copyFrom(other);
}

Cell& Cell::operator=(const Cell& other)
{
	if (this != &other)
		copyFrom(other);
	return *this;
}

void Cell::copyFrom(const Cell& other)
{
	symbol = other.symbol;
	pos = other.pos;
	gCost = other.gCost;
	hCost = other.hCost;
	fCost = other.fCost;
	
	// ? is it?
	parent = other.parent;
}

