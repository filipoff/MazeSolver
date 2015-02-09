#pragma once
#include "Utilities.h"

class Cell;
#include "Board.h"
#include <vector>
#include <iostream>
/// Cell is a class that represents a cell in board of cells
class Cell
{

private:
	// the symbol by which the cell is shown on the board
	char symbol;

	// the position of the cell on the board
	Position pos;

	// the board to which the cell belongs to
	Board* owner;
	/// numbers used for the path-finding algorithm

	// the distance from the current cell to the start cell
	size_t gCost;

	// the distance from the current cell to the end cell
	size_t hCost;

	// the parrent of the current cell
	// it is used for the algorithm
	Cell* parent;

	bool isInOpenedListStatus;
	bool isInClosedListStatus;
	bool isPassableStatus;
	bool isStartStatus;
	bool isEndStatus;

private:

	// function that copies data from one cell to another
	void copyFrom(const Cell& other);

	// gets left neighbour if there is any else returns null pointer
	Cell* getLeftNeighbour() const;

	// gets right neighbour if there is any else returns null pointer
	Cell* getRightNeighbour() const;

	// gets upper neighbour if there is any else returns null pointer
	Cell* getUpperNeighbour() const;

	// gets bottom neighbour if there is any else returns null pointer
	Cell* getBottomNeighbour() const;
	
	void initStatusesToFalse();

public:

	// the default ctor
	Cell();

	// the copy ctor
	Cell(const Cell& other);

	// ctor that takes symbol and position of the cell and sets the owner
	Cell(Board* owner, char symbol, size_t rowPosition, size_t columnPosition);

	// the assigment operator

	Cell& operator=(const Cell& other);

	// gets cell symbol
	char getSymbol() const { return symbol; }

	// gets cell position
	Position getPosition() const { return pos; }

	// sets cell symbol
	void setSymbol(const char& symbol);

	// sets cell position
	void setPosition(size_t rowPosition, size_t columnPosition) { pos.setPosition(rowPosition, columnPosition); }

	// gets cell g cost
	size_t getGCost() const { return gCost; }

	// gets cell h cost
	size_t getHCost() const { return hCost; }

	// gets cell f cost
	size_t getFCost() const { return gCost + hCost; }

	// sets cell g cost
	void setGCost(size_t gCost) { this->gCost = gCost; }

	// sets cell h cost
	void setHCost(size_t hCost) { this->hCost = hCost; }

	// gets cell parent
	Cell* getParent() const { return parent; }

	// sets cell parent
	void setParent(Cell* parent) { this->parent = parent; }


	// gets owner of the cell
	Board* getOwner() const { return owner; }

	// sets owner of the cell
	void setOwner(Board* owner) { this->owner = owner; }

	bool isPassable() const { return isPassableStatus; }
	bool isStart() const { return isStartStatus; }
	bool isEnd() const { return isEndStatus; }
	bool isInOpenedList() const { return isInOpenedListStatus; }
	bool isInClosedList() const { return isInClosedListStatus; }

	void setPassableStatus(bool status) { isPassableStatus = status; }
	void setStartStatus(bool status) { isStartStatus = status; }
	void setEndStatus(bool status) { isEndStatus = status; }
	void setInOpenedListStatus(bool status) { isInOpenedListStatus = status; }
	void setInClosedListStatus(bool status) { isInClosedListStatus = status; }

	void getPassableNeighbours(std::vector<Cell*> &neighbours) const;
};