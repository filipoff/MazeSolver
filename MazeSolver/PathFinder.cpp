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



void PathFinder::resetOpenedAndClosedLists(List<Cell*>& openedCellsList, List<Cell*>& closedCellsList)
{
	for (List<Cell*>::Iterator it = openedCellsList.begin(); it != openedCellsList.end(); ++it)
	{
		(*it)->setInOpenedListStatus(false);
		(*it)->setParent(NULL);
	}

	for (List<Cell*>::Iterator it = closedCellsList.begin(); it != closedCellsList.end(); ++it)
	{
		(*it)->setInClosedListStatus(false);
		(*it)->setParent(NULL);
	}
}

bool PathFinder::findPath(Cell* start, Cell* end, List<Cell*> &path, bool mustClearPath)
{
	List<Cell*> openedCellsList;
	List<Cell*> closedCellsList;
	Cell* current;

	calculateHCostOf(start, end);
	start->setGCost(0);
	openedCellsList.push_back(start);
	start->setInOpenedListStatus(true);


	current = start;

	while (!openedCellsList.isEmpty())
	{
		current = openedCellsList.peek_front();

		for (List<Cell*>::Iterator it = openedCellsList.begin(); it != openedCellsList.end(); ++it)
		{
			if ((*it)->getFCost() <= current->getFCost())
			{
				current = *it;
			}
		}

		if (current == end)
		{
			if (mustClearPath)
				path.clear();
			while (current)
			{
				path.push_front(current);
				//current->setSymbol('+');
				current = current->getParent();
			}

			resetOpenedAndClosedLists(openedCellsList, closedCellsList);

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

	resetOpenedAndClosedLists(openedCellsList, closedCellsList);

	return false;
}





bool PathFinder::algo(Cell* start, Cell* end, Vector<LockPair>& pairs, List<Cell*> &path)
{
	std::queue<Cell*> DoorsAndKeysFound;
	List<Cell*> pathSequence;
	List<Cell*> finalPath;



	pathSequence.push_back(end);
	DoorsAndKeysFound.push(end);

	while (!DoorsAndKeysFound.empty())
	{
		Cell* temp = DoorsAndKeysFound.front();
		DoorsAndKeysFound.pop();

		if (temp->isKey() || temp->isEnd())
		{
			List<Cell*> tempPath;
			if (!findPath(start, temp, tempPath, true))
				return false;

			for (List<Cell*>::Reverse_Iterator it = tempPath.rbegin(); it != tempPath.rend(); ++it)
			{
				if ((*it)->isDoor())
				{
					pathSequence.push_back(*it);
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
			pathSequence.push_back(key);
			DoorsAndKeysFound.push(key);
		}
	}

	pathSequence.push_back(start);
	trimPath(pathSequence);

	for (List<Cell*>::Reverse_Iterator it = pathSequence.rbegin(); it != pathSequence.rend(); ++it)
	{
		List<Cell*>::Reverse_Iterator it2 = it;
		++it2;
		if (it2 == pathSequence.rend())
			break;
		Cell* tempStart = *it;
		Cell* tempEnd = *it2;

		findPath(tempStart, tempEnd, finalPath, false);
	}

	for (List<Cell*>::Iterator it = finalPath.begin(); it != finalPath.end(); ++it)
	{
		(*it)->setSymbol('+');
	}

	return true;
}



void PathFinder::trimPath(List<Cell*>& path)
{
	Vector<Cell*> keys;
	Vector<Cell*> doors;
	for (List<Cell*>::Reverse_Iterator it = path.rbegin(); it != path.rend();)
	{
		if ((*it)->isKey())
		{
			if (keys.contains(*it))
			{
				path.removeAt(it);
				++it;
				continue;
			}
			else
			{
				keys.push(*it);
			}
		}

		else if ((*it)->isDoor())
		{
			if (doors.contains(*it))
			{
				path.removeAt(it);
				++it;
				continue;
			}
			else
			{
				doors.push(*it);
			}
		}
		++it;
	}

}

