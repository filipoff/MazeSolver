#pragma once


/// Position is a struct that contains row and column position of a given cell
/// also has methods that check if two positions are neighbour positions and
/// in which direction are the neighbour positions compared to the given position
struct Position
{
	// row position of the cell on the board
	size_t rowPosition;

	// column position of the cell on the board
	size_t columnPosition;

	// default c-tor
	Position();

	// c-tor that takes two numbers and makes a position of them
	Position(const size_t rowPosition, const size_t columnPosition);

	// copy c-tor
	Position(const Position& other);

	// assigment operator
	Position& operator=(const Position& other);

	// compare operator
	bool operator==(const Position& other);

	// sets positions by given two numbers
	void setPosition(const size_t rowPosition, const size_t columnPosition);

	// checks if a given position is a upper neighbour
	bool nextPositionIsUpper(const Position& next);

	// checks if a given position is a down neighbour
	bool nextPositionIsDown(const Position& next);

	// checks if a given position is a right neighbour
	bool nextPositionIsRight(const Position& next);

	// checks if a given position is a left neighbour
	bool nextPositionIsLeft(const Position& next);

};