#include <iostream>
#include "Board.h"
//#include "List.h"
#include <list>
using namespace std;

int main()
{
	Board test;
	test.loadFromFileName("testMap.txt");
	test.print();


	list<int> list;
	const size_t BIGSIZE = 10;
	for (size_t i = 0; i < BIGSIZE; i++)
	{
		list.push_back(i);
	}

	for (std::list<int>::iterator i = list.begin(); i != list.end(); i++)
	{
		list.pop_back();
	}


	return 0;
}