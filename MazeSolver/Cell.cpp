#include "Cell.h"

Cell::Cell(char symbol, int row, int column) :
symbol(symbol), row(row), column(column)
{}

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
