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
};