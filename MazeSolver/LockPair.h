#pragma once
#include "Cell.h"


// LockPair class contains a pair of key and door
// used by the path-finding algorithm
class LockPair
{

private:
	
	// a pointer to the cell which contains the key
	Cell* key;

	// a pointer to the cell which contains the key
	Cell* door;

	// the symbol of the key
	char keySymbol;

	// the symbol of the door
	char doorSymbol;

public:

	// default c-tor
	LockPair() : key(NULL), door(NULL), keySymbol(0), doorSymbol(0) {}

	// gets the key cell
	Cell* getKeyCell() const { return key; }

	// gets the door cell
	Cell* getDoorCell() const { return door; }

	// sets the key cell
	void setKeyCell(Cell* cell) { key = cell; }

	// sets the door cell
	void setDoorCell(Cell* cell) { door = cell; }

	// gets the key symbol
	char getKeySymbol() const { return keySymbol; }

	// gets the door symbol
	char getDoorSymbol() const { return doorSymbol; }

	// sets the key symbol
	void setKeySymbol(const char symbol) { keySymbol = symbol; }

	// sets the door symbol
	void setDoorSymbol(const char symbol) { doorSymbol = symbol; }
};