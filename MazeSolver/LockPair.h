#pragma once
#include "Utilities.h"
#include "Cell.h"


class LockPair
{

private:
	Cell* key;
	Cell* door;
	char keySymbol;
	char doorSymbol;

public:
	LockPair() : key(NULL), door(NULL), keySymbol(0), doorSymbol(0) {}
	Cell* getKeyCell() const { return key; }
	Cell* getDoorCell() const { return door; }
	void setKeyCell(Cell* cell) { key = cell; }
	void setDoorCell(Cell* cell) { door = cell; }
	char getKeySymbol() const { return keySymbol; }
	char getDoorSymbol() const { return doorSymbol; }
	void setKeySymbol(const char symbol) { keySymbol = symbol; }
	void setDoorSymbol(const char symbol) { doorSymbol = symbol; }
};