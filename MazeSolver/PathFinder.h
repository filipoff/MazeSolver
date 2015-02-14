#pragma once
#include "Cell.h"
#include "Vector.h"
#include "List.h"
#include <algorithm>

/// PathFinder is a pure static class that can find path between two cells if it exists
/// and the path can include going through doors and taking keys 
/// it can also convert the sequence of cell which determine the path to
/// a string containing the directions used for navingating from the start cell to the end cell
class PathFinder
{
private:

	// a function which is used for calculating the heuristics of a given cell
	// to the end cell and sets given cell's hCost member to that value
	static void calculateHCostOf(Cell* current, const Cell* end);
	
	// a function that resets the path-finding members of the cell class 
	// which are used by the path-finding algorithm so the cells can be used again
	// for another pass of the path-finding algorithm
	static void resetPathCells(List<Cell*>& openedCellsList, List<Cell*>& closedCellsList);
	
	// a function that removes duplicated keys from the list which contains the sequence of cells
	// representing the path
	// its a side-effect of the algorithm
	static void trimPathFromDublicatedKeys(List<Cell*>& path);

	// a function find the path between two cells if it exists
	// and fills a list of cell given as parameter with that path
	// this path can contain doors and keys
	// it finds a path as if all doors are unlocked
	// it uses A* path-finding algorithm
	static bool findPath(Cell* start, Cell* end, List<Cell*>& path);


	// a function that converts a given list of cell to a string with
	// directions (U,D,R,L)
	// must be const but i need const iterators
	static const char* convertPathToString(List<Cell*>& path);
	
	// a function that adds to the final path other intermediate paths
	// must be const but i need const iterators
	static void addToFinalPath(List<Cell*>& finalPath, List<Cell*>& path);

public:
	
	// the main method of the class
	// by given start cell, end cell, a vector of lock pairs,
	// it finds the path between that cells if it exists
	// and determines which keys have to be taken
	// and which doors have to be unlocked in order to
	// go from the start cell to the end cell
	static bool algo(Cell* start, Cell* end, Vector<LockPair>& pairs, const char* pathString);
	
	// a method that sets the path's cells' symbol to a given symbol
	// so the path can be printed in the console
	static void setPathWithSymbol(List<Cell*>& path, char pathSymbol);
};