#include <iostream>
#include "Board.h"
using namespace std;

int main()
{
	Board test;
	test.loadFromFileName("testMap.txt");
	test.print();
	return 0;
}