#include "Cell.h"

Cell::Cell()
{
	symbol = 0;
	row = 0;
	column = 0;
}

Cell::Cell(char symbol, int row, int column) :
symbol(symbol), row(row), column(column)
{}


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
	row = other.row;
	column = other.column;
}

char Cell::getSymbol() const
{
	return symbol;
}

int Cell::getRow() const
{
	return row;
}

int Cell::getColumn() const
{
	return column;
}

void Cell::setSymbol(const char& symbol)
{
	this->symbol = symbol;
}

void Cell::setRow(const int& row)
{
	this->row = row;
}

void Cell::setColumn(const int& column)
{
	this->column = column;
}
