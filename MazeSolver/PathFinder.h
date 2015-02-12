#pragma once
#include "Cell.h"
#include "List.h"
#include "Vector.h"
#include <algorithm>

class PathFinder
{
private:

	static void calculateHCostOf(Cell* current, const Cell* end);

public:
	static bool findPath(Cell* start, Cell* end, List<Cell*> &path);
};