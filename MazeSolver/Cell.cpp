#include "Cell.h"

Cell::Cell() : symbol(0), pos(0, 0), gCost(0), hCost(0), fCost(0), parent(NULL), owner(NULL)
{
	isInClosedListStatus = false;
	isInClosedListStatus = false;
	isPassableStatus = false;
	isStartStatus = false;
	isEndStatus = false;
}

Cell::Cell(Board* owner, char symbol, size_t rowPosition, size_t columnPosition) :
owner(owner), symbol(symbol), pos(rowPosition, columnPosition), gCost(0), hCost(0), fCost(0),
parent(NULL) {}


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
	owner = other.owner;
	isInOpenedListStatus = other.isInOpenedListStatus;
	isInClosedListStatus = other.isInClosedListStatus;
	isPassableStatus = other.isPassableStatus;
	isStartStatus = other.isStartStatus;
	isEndStatus = other.isEndStatus;
	// ? is it?
	parent = other.parent;
}


Cell* Cell::getLeftNeighbour() const
{
	return owner->getCellAt(pos.rowPosition, pos.columnPosition - 1);
}

Cell* Cell::getRightNeighbour() const
{
	return owner->getCellAt(pos.rowPosition, pos.columnPosition + 1);
}

Cell* Cell::getUpperNeighbour() const
{
	return owner->getCellAt(pos.rowPosition - 1, pos.columnPosition);
}

Cell* Cell::getBottomNeighbour() const
{
	return owner->getCellAt(pos.rowPosition + 1, pos.columnPosition);
}