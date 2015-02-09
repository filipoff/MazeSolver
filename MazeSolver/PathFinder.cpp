#include "PathFinder.h"

void PathFinder::calculateHCostOf(Cell* current, const Cell* end)
{
	size_t hCost = 
		std::max(current->getPosition().rowPosition, end->getPosition().rowPosition) -
		std::min(current->getPosition().rowPosition, end->getPosition().rowPosition) +
		std::max(current->getPosition().columnPosition, end->getPosition().columnPosition) -
		std::min(current->getPosition().columnPosition, end->getPosition().columnPosition);
	current->setHCost(hCost);
}



bool PathFinder::findPath(Cell* start, Cell* end, std::list<Cell*> &path)
{
	std::list<Cell*> openedCellsList;
	std::list<Cell*> closedCellsList;
	Cell* current;

	calculateHCostOf(start,end);
	start->setGCost(0);
	openedCellsList.push_back(start);
	start->setInOpenedListStatus(true);


	current = start;
	while (!openedCellsList.empty())
	{
		for (std::list<Cell*>::iterator i = openedCellsList.begin(); i != openedCellsList.end(); i++)
		{
			if ((*i)->getFCost() <= current->getFCost())
			{
				current = *i;
			}
		}

		if (current == end)
		{
			path.clear();
			while (current)
			{
				path.push_front(current);
				current = current->getParent();
			}
			return true;
		}

		openedCellsList.remove(current);
		current->setInOpenedListStatus(false);

		closedCellsList.push_back(current);
		current->setInClosedListStatus(true);
		
		Vector<Cell*> neighbours;
		current->getPassableNeighbours(neighbours);

		for (size_t i = 0; i < neighbours.getSize(); i++)
		{
			Cell* neighbour = neighbours[i];

			if (neighbour->isInClosedList())
				continue;

			size_t neighbourGCost = current->getGCost() + 1;

			if (!neighbour->isInOpenedList() || neighbourGCost < neighbour->getGCost())
			{
				neighbour->setParent(current);
				neighbour->setGCost(neighbourGCost);
				if (!neighbour->isInOpenedList())
				{
					neighbour->setInOpenedListStatus(true);
					openedCellsList.push_back(neighbour);
					calculateHCostOf(neighbour, end);
				}
			}
		}

	}
	return false;
}