#include <iostream>
#include "Board.h"
#include "PathFinder.h"
#include "List.h"

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
	PathFinder::algo(start, end, test.getLockPairs(), path);
	test.print();
	

	*/

	List<int> list;
	const size_t BIGSIZE = 10;

	for (size_t i = 0; i < BIGSIZE; i++)
	{
		list.push_back(i);
	}
	for (List<int>::Reverse_Iterator i = list.rbegin(); i != list.rend(); ++i)
	{
		cout << *i << ' ';
	}
	cout << endl;

	return 0;
}