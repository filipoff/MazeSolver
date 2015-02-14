#include "Utilities.h"


Position::Position() : rowPosition(0), columnPosition(0) {}
Position::Position(const size_t rowPosition, const size_t columnPosition) :
rowPosition(rowPosition),
columnPosition(columnPosition) {}

Position& Position::operator=(const Position& other)
{
	rowPosition = other.rowPosition;
	columnPosition = other.columnPosition;
	return *this;
}

bool Position::operator==(const Position& other)
{
	return (rowPosition == other.rowPosition && columnPosition == other.columnPosition);
}

Position::Position(const Position& other)
{
	rowPosition = other.rowPosition;
	columnPosition = other.columnPosition;
}

void Position::setPosition(const size_t rowPosition, const size_t columnPosition)
{
	this->rowPosition = rowPosition;
	this->columnPosition = columnPosition;
}

bool Position::nextPositionIsUpper(const Position& next)
{
	if (next.rowPosition == rowPosition - 1)
		return true;
	return false;
}

bool Position::nextPositionIsDown(const Position& next)
{
	if (next.rowPosition == rowPosition + 1)
		return true;
	return false;
}

bool Position::nextPositionIsLeft(const Position& next)
{
	if (next.columnPosition == columnPosition - 1)
		return true;
	return false;
}

bool Position::nextPositionIsRight(const Position& next)
{
	if (next.columnPosition == columnPosition + 1)
		return true;
	return false;
}

