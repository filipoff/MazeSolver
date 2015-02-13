#pragma once
#include "Cell.h"
#include <list>
#include "Vector.h"
#include "List.h"
#include <algorithm>
#include <queue>

class PathFinder
{
private:

	static void calculateHCostOf(Cell* current, const Cell* end);
	
	static void resetOpenedAndClosedLists(std::list<Cell*>& openedCellsList, std::list<Cell*>& closedCellsList);
	
	// static void trimPath(std::list<Cell*>& path);

public:
	static bool findPath(Cell* start, Cell* end, std::list<Cell*> &path);
	
	static bool algo(Cell* start, Cell* end, Vector<LockPair>& pairs, std::list<Cell*> &path);
};