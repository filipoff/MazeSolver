#pragma once
#include "Utilities.h"

struct Key
{
	char symbol;
	Position pos;
};

struct Door
{
	char symbol;
	Position pos;
};

class LockPair
{

private:
	Key key;
	Door door;

public:
	char getKeySymbol() const;
	char getDoorSymbol() const;
	Position getKeyPosition() const;
	Position getDoorPosition() const;
	void setKeyPosition(const size_t rowPosition, const size_t columnPosition);
	void setDoorPosition(const size_t rowPosition, const size_t columnPosition);
	void setKeySymbol(const char symbol);
	void setDoorSymbol(const char symbol);
};