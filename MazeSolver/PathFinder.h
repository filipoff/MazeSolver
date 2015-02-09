#pragma once
#include "Cell.h"
#include <list>
#include <algorithm>

class PathFinder
{
private:
	
	static void calculateHCostOf(Cell* current, const Cell* end);

public:
	static bool findPath(Cell* start, Cell* end, std::list<Cell*> &path);
};