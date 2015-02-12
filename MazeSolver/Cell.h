#pragma once
#include "Utilities.h"
#include "Vector.h"
#include <iostream>
class Cell;
#include "Board.h"

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

	// a bool status used by the pathfinder
	// stores if the cell is in the opened list
	bool isInOpenedListStatus;

	// a bool status used by the pathfinder
	// stores if the cell is in the closed list
	bool isInClosedListStatus;

	// bool status that stores if the cell is passable
	bool isPassableStatus;

	// bool status that stores if the cell is the start point of the maze
	bool isStartStatus;

	// bool status that stores if the cell is the end point of the maze
	bool isEndStatus;

	// bool status that stores if the cell is a key
	bool isKeyStatus;

	// bool status that stores if the cell is door
	bool isDoorStatus;

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

	// initializes all bool statuses to false
	void initStatusesToFalse();

	bool conditionToPushInPassableNeighbours(const Cell* neighbour) const;


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
	void setSymbol(const char& symbol) { this->symbol = symbol; }

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

	// checks if the cell is passable
	bool isPassable() const { return isPassableStatus; }

	// checks if the cell is the start cell of the maze
	bool isStart() const { return isStartStatus; }

	// checks if the cell is the end cell of the maze
	bool isEnd() const { return isEndStatus; }

	// checks if the cell is in the opened list used by the pathfinder
	bool isInOpenedList() const { return isInOpenedListStatus; }

	// checks if the cell is in the closed list used by the pathfinder
	bool isInClosedList() const { return isInClosedListStatus; }

	// checks if the cell is an key
	bool isKey() const { return isKeyStatus; }
	
	// checks if the cell is a door
	bool isDoor() const { return isDoorStatus; }

	// sets the cell's key status
	void setKeyStatus(bool status) { isKeyStatus = status; }

	// sets the cell's door status
	void setDoorStatus(bool status) { isDoorStatus = status; }

	// sets the cell's passable status
	void setPassableStatus(bool status) { isPassableStatus = status; }

	// sets the cell's start status
	void setStartStatus(bool status) { isStartStatus = status; }

	// sets the cell's end status
	void setEndStatus(bool status) { isEndStatus = status; }

	// sets the cell's status if it's in the opened list
	void setInOpenedListStatus(bool status) { isInOpenedListStatus = status; }

	// sets the cell's status if it's in the closed list
	void setInClosedListStatus(bool status) { isInClosedListStatus = status; }

	// fills the vector that is passed as parameter with neighbours of the cell
	// only if the are passable cells
	void getPassableNeighbours(Vector<Cell*> &neighbours) const;
};