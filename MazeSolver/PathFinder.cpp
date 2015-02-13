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

	calculateHCostOf(start, end);
	start->setGCost(0);
	openedCellsList.push_back(start);
	start->setInOpenedListStatus(true);


	current = start;

	while (!openedCellsList.empty())
	{
		current = openedCellsList.front();

		for (std::list<Cell*>::iterator it = openedCellsList.begin(); it != openedCellsList.end(); ++it)
		{
			if ((*it)->getFCost() <= current->getFCost())
			{
				current = *it;
			}
		}

		if (current == end)
		{
			path.clear();
			while (current)
			{
				path.push_front(current);
				//current->setSymbol('+');
				current = current->getParent();
			}

			for (std::list<Cell*>::iterator it = openedCellsList.begin(); it != openedCellsList.end(); ++it)
			{
				(*it)->setInOpenedListStatus(false);
			}

			for (std::list<Cell*>::iterator it = closedCellsList.begin(); it != closedCellsList.end(); ++it)
			{
				(*it)->setInClosedListStatus(false);
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

			size_t neighbourNextGCost = current->getGCost() + 1;

			if (!neighbour->isInOpenedList() || neighbourNextGCost < neighbour->getGCost())
			{
				neighbour->setParent(current);
				neighbour->setGCost(neighbourNextGCost);
				if (!neighbour->isInOpenedList())
				{
					neighbour->setInOpenedListStatus(true);
					openedCellsList.push_back(neighbour);
					calculateHCostOf(neighbour, end);
				}
			}
		}

	}

	for (std::list<Cell*>::iterator it = openedCellsList.begin(); it != openedCellsList.end(); ++it)
	{
		(*it)->setInOpenedListStatus(false);
	}

	for (std::list<Cell*>::iterator it = closedCellsList.begin(); it != closedCellsList.end(); ++it)
	{
		(*it)->setInClosedListStatus(false);
	}


	return false;
}





bool PathFinder::algo(Cell* start, Cell* end, Vector<LockPair>& pairs, std::list<Cell*> &path)
{
	std::queue<Cell*> DoorsAndKeysFound;
	std::list<Cell*> finalPath;
	std::list<Cell*> realFinalPath;



	finalPath.push_back(end);
	DoorsAndKeysFound.push(end);

	while (!DoorsAndKeysFound.empty())
	{
		Cell* temp = DoorsAndKeysFound.front();
		DoorsAndKeysFound.pop();

		if (temp->isKey() || temp->isEnd())
		{
			std::list<Cell*> tempPath;
			if (!findPath(start, temp, tempPath))
				return false;

			for (std::list<Cell*>::reverse_iterator it = tempPath.rbegin(); it != tempPath.rend(); ++it)
			{
				if ((*it)->isDoor())
				{
					finalPath.push_back(*it);
					DoorsAndKeysFound.push(*it);
				}
			}
		}
		else if (temp->isDoor())
		{
			Cell* key = NULL;
			for (size_t i = 0; i < pairs.getSize(); i++)
			{
				if (pairs[i].getDoorSymbol() == temp->getSymbol())
				{
					key = pairs[i].getKeyCell();
					break;
				}
			}
			finalPath.push_back(key);
			DoorsAndKeysFound.push(key);
		}
	}

	finalPath.push_back(start);
	//	trimPath(finalPath);

	for (std::list<Cell*>::reverse_iterator it = finalPath.rbegin(); it != finalPath.rend(); ++it)
	{
		std::list<Cell*>::reverse_iterator it2 = it;
		++it2;
		if (it2 == finalPath.rend())
			break;
		Cell* tempStart = *it;
		Cell* tempEnd = *it2;

		findPath(tempStart, tempEnd, realFinalPath);
	}


	return true;
}

/*
void PathFinder::trimPath(std::list<Cell*>& path)
{
Vector<Cell*> keys;
// TODO Vector contains

for (std::list<Cell*>::reverse_iterator it = path.rbegin(); it != path.rend();)
{
if ((*it)->isKey())
{
if (keys.contains(*it))
{
it = path.erase(it);
continue;
}
else
{
keys.push(*it);
}
}
++it;
}

}

*/