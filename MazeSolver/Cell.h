#pragma once
#include "Utilities.h"

class Cell; 
#include "Board.h"
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
	int gCost;

	// the distance from the current cell to the end cell
	int hCost;

	// the combined number of the gCost and hCost
	int fCost;

	// the parrent of the current cell
	// it is used for the algorithm
	Cell* parent;

private:

	// function that copies data from one cell to another
	void copyFrom(const Cell& other);


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
	int getGCost() const { return gCost; }

	// gets cell h cost
	int getHCost() const { return hCost; }

	// gets cell f cost
	int getFCost() const { return fCost; }

	// sets cell g cost
	void setGCost(int gCost) { this->gCost = gCost; }

	// sets cell h cost
	void setHCost(int hCost) { this->hCost = hCost; }

	// calculates the f cost
	void calculateFCost() { fCost = gCost + hCost; }

	// gets cell parent
	Cell* getParent() const { return parent; }

	// sets cell parent
	void setParent(Cell* parent) { this->parent = parent; }
};