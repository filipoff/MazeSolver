#include "LockPair.h"

char LockPair::getKeySymbol() const
{
	return key.symbol;
}

char LockPair::getDoorSymbol() const
{
	return door.symbol;
}

Position LockPair::getKeyPosition() const
{
	return key.pos;
}

Position LockPair::getDoorPosition() const
{
	return door.pos;
}

void LockPair::setKeyPosition(const size_t rowPosition, const size_t columnPosition)
{
	key.pos.setPosition(rowPosition, columnPosition);
}

void LockPair::setDoorPosition(const size_t rowPosition, const size_t columnPosition)
{
	door.pos.setPosition(rowPosition, columnPosition);
}

void LockPair::setKeySymbol(const char symbol)
{
	key.symbol = symbol;
}
void LockPair::setDoorSymbol(const char symbol)
{
	door.symbol = symbol;
}