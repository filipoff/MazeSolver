#pragma once

struct Position
{
	size_t rowPosition;
	size_t columnPosition;
	Position();
	Position(const size_t rowPosition, const size_t columnPosition);
	Position(const Position& other);
	Position& operator=(const Position& other);
	bool operator==(const Position& other);
	void setPosition(const size_t rowPosition, const size_t columnPosition);
	bool nextPositionIsUpper(const Position& next);
	bool nextPositionIsDown(const Position& next);
	bool nextPositionIsRight(const Position& next);
	bool nextPositionIsLeft(const Position& next);

};