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