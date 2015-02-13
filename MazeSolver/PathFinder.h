#pragma once
#include "Cell.h"
#include "Vector.h"
#include "List.h"
#include <algorithm>
#include <queue>

class PathFinder
{
private:

	static void calculateHCostOf(Cell* current, const Cell* end);
	
	static void resetOpenedAndClosedLists(List<Cell*>& openedCellsList, List<Cell*>& closedCellsList);
	
	static void trimPath(List<Cell*>& path);

	static bool findPath(Cell* start, Cell* end, List<Cell*> &path, bool mustClearPath);
public:
	
	static bool algo(Cell* start, Cell* end, Vector<LockPair>& pairs, List<Cell*> &path);
};