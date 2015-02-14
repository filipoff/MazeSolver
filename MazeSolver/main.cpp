#include <iostream>
#include "Board.h"
#include "PathFinder.h"

using namespace std;

int main()
{
	Board test;
	test.loadFromFileName("testMap.txt");
	test.print();
	Vector<char> pathString;
	Cell* start = test.getStartCell();
	Cell* end = test.getEndCell();
	if (PathFinder::algo(start, end, test.getLockPairs(), pathString))
		test.print();
	else
		cout << "No path exists!" << endl;
	return 0;
}