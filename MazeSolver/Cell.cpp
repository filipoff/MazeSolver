#include "Cell.h"

Cell::Cell() : symbol(0), pos(0, 0), gCost(0), hCost(0), parent(NULL), owner(NULL)
{
	initStatusesToFalse();
}

Cell::Cell(Board* owner, char symbol, size_t rowPosition, size_t columnPosition) :
owner(owner), symbol(symbol), pos(rowPosition, columnPosition), gCost(0), hCost(0),
parent(NULL)
{

	initStatusesToFalse();

	if (symbol == constants::PASSABLE)
	{
		isPassableStatus = true;
	}

	if (symbol == constants::START)
	{
		isStartStatus = true;
	}
	if (symbol == constants::END)
	{
		isEndStatus = true;
	}
}


void Cell::initStatusesToFalse()
{
	isInClosedListStatus = false;
	isInOpenedListStatus = false;
	isPassableStatus = false;
	isStartStatus = false;
	isEndStatus = false;
	isKeyStatus = false;
	isDoorStatus = false;
}

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


bool Cell::conditionToPushInPassableNeighbours(const Cell* neighbour) const
{
	if (neighbour &&
		neighbour->isPassable() ||
		neighbour->isKey() ||
		neighbour->isDoor() ||
		//neighbour->isStart() ||
		neighbour->isEnd())
	{
		return true;
	}
	return false;
}


void Cell::getPassableNeighbours(Vector<Cell*> &neighbours) const
{

	neighbours.clear();

	if (conditionToPushInPassableNeighbours(getLeftNeighbour()))
		neighbours.push(getLeftNeighbour());

	if (conditionToPushInPassableNeighbours(getRightNeighbour()))
		neighbours.push(getRightNeighbour());

	if (conditionToPushInPassableNeighbours(getUpperNeighbour()))
		neighbours.push(getUpperNeighbour());

	if (conditionToPushInPassableNeighbours(getBottomNeighbour()))
		neighbours.push(getBottomNeighbour());
}
