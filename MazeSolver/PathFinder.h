#pragma once
#include "Cell.h"
#include "Vector.h"
#include "List.h"
#include <algorithm>
#include "Board.h"
#include <queue>

class PathFinder
{
private:

	static void calculateHCostOf(Cell* current, const Cell* end);
	
	static void resetPathCells(List<Cell*>& openedCellsList, List<Cell*>& closedCellsList);
	
	static void trimPathFromDublicatedKeys(List<Cell*>& path);

	static bool findPath(Cell* start, Cell* end, List<Cell*>& path);


	// must be const but i need const iterators
	static const char* convertPathToString(List<Cell*>& path);
	
	// must be const but i need const iterators
	static void addToFinalPath(List<Cell*>& finalPath, List<Cell*>& path);

public:
	
	static bool algo(Cell* start, Cell* end, Vector<LockPair>& pairs, const char* pathString);
	
	static void setPathWithSymbol(List<Cell*>& path, char pathSymbol);
};