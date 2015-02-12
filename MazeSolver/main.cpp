#include <iostream>
#include "Board.h"
#include "PathFinder.h"
#include "List.h"
#include <list>
using namespace std;

int main()
{

	/*
	Board test;
	test.loadFromFileName("testMap.txt");
	test.print();

	std::list<Cell*> path;
	Cell* start = test.getStartCell();
	Cell* end = test.getEndCell();
	PathFinder::findPath(start, end, path);
	test.print();
	*/
	List<int> list;
	const size_t BIGSIZE = 10;

	for (size_t i = 0; i < BIGSIZE; i++)
	{
		list.push_back(i);
	}

	list.remove(9);

	std::list<int> list2;

	for (size_t i = 0; i < BIGSIZE; i++)
	{
		list2.push_back(i);
	}

	list2.remove(5);

	return 0;
}