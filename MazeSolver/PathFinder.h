#pragma once
#include "Cell.h"
#include <list>
class PathFinder
{
	std::list<Cell*> openedCellsList;
	std::list<Cell*> closedCellsList;

public:
	bool findPath(const Cell* start, const Cell* end);
};