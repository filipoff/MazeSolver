#include <iostream>
#include "Board.h"
#include "PathFinder.h"
#include "List.h"

using namespace std;

int main()
{

	
	Board test;
	test.loadFromFileName("testMap.txt");
	test.print();
	

	std::list<Cell*> path;
	Cell* start = test.getStartCell();
	Cell* end = test.getEndCell();
	PathFinder::findPath(start, end, path);
	test.print();
	


	return 0;
}