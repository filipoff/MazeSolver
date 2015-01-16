#pragma once


// Cell is a class that represents a cell in board of cells
class Cell
{
private:
	// the symbol by which the cell is shown on the board
	char symbol;
	
	// the row position of the cell
	int row;
	
	// the coluwn postion of the cell
	int column;
	Cell() {}

public:

	// ctor that takes symbol and position of the cell
	Cell(char symbol, int row, int column);

	// gets cell symbol
	char getSymbol() const;
	
	// gets row position
	int getRow() const;

	// gets coluwn position
	int getColumn() const;

	// sets cell symbol
	void setSymbol(const char& symbol);

	// sets row position
	void setRow(const int& row);

	// sets coluwn position
	void setColumn(const int& column);
};