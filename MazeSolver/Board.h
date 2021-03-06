#pragma once

class Board;
#include "Cell.h"
#include "Vector.h"
#include "Constants.h"
#include "LockPair.h"
#include <iostream>
#include <fstream>

class Board
{

private:
	// height of the board
	size_t height;

	// width of the board
	size_t width;

	// board is a two-dimensional array of cells
	Cell** board;

	// pairs of keys and door with their position
	Vector<LockPair> lockPairs;
private:

	// a function that allocates a board by height and width parameters
	Cell** allocate(const size_t height, const size_t width);

	// a function that clears the memory taken by the allocated board 
	void free();

	// a function that copies data from one board to another
	void copyFrom(const Board& other);

	// a help fuction that is used in the readFromFileName method for loading a board from text file
	// by reading the file line be line, allocating memory for the board and copying
	// the text from the file into the board array
	void setBoardFromFile(std::istream &in);

	// gets the size of the board by reading the board file
	bool getBoardSizeFromFile(std::istream &in, size_t& newHeight, size_t& newWidth) const;

	// sets the keys and doors pairs by reading the board file
	bool setLockPairsFromFile(std::istream &in);

	// finds whichs cells are part of the lock pairs
	// sets pointer to the cell and sets its symbol
	// also sets its status if its a key or a door
	void setLockPairsCells(const char c, Cell* cell);

public:
	// the default constructor of the class
	Board();

	// the destructor of the class
	~Board();

	// the copy constructor
	Board(const Board& other);

	// the assigment operator
	Board& operator=(const Board& other);

	// print is a method that prints the board on the screen
	void print() const;

	// a method that loads a board from a text file by name
	bool loadFromFileName(const char* filename);

	// gets height of the board
	int getHeight() const;

	// gets width of the board
	int getWidth() const;

	// gets cell at given position
	Cell* getCellAt(size_t row, size_t column) const;

	// gets the start cell
	Cell* getStartCell() const;

	// gets the end cell
	Cell* getEndCell() const;

	// gets the lock pairs of keys and doors
	// used by the path-finding algorithm
	Vector<LockPair> getLockPairs() const;

};