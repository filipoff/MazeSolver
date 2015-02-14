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



void PathFinder::resetPathCells(List<Cell*>& openedCellsList, List<Cell*>& closedCellsList)
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

bool PathFinder::findPath(Cell* start, Cell* end, List<Cell*>& path)
{

	if (start == end)
	{
		return true;
	}

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
			path.clear();
			while (current)
			{
				path.push_front(current);
				current = current->getParent();
			}

			resetPathCells(openedCellsList, closedCellsList);

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

	resetPathCells(openedCellsList, closedCellsList);

	return false;
}


void PathFinder::addToFinalPath(List<Cell*>& finalPath, List<Cell*>& path)
{
	// to remove the dublicating start
	if (path.peek_front()->getSymbol() != constants::START)
		path.pop_front();

	for (List<Cell*>::Iterator it = path.begin(); it != path.end(); ++it)
	{
		finalPath.push_back(*it);
	}
}


bool PathFinder::algo(Cell* start, Cell* end, Vector<LockPair>& pairs, const char* pathString)
{
	// can be queue
	List<Cell*> DoorsAndKeysFound;

	List<Cell*> ReversedPathSequence;
	List<Cell*> finalPath;

	ReversedPathSequence.push_back(end);
	DoorsAndKeysFound.push_back(end);

	while (!DoorsAndKeysFound.isEmpty())
	{
		Cell* temp = DoorsAndKeysFound.pop_front();

		if (temp->isKey() || temp->isEnd())
		{
			List<Cell*> tempPath;
			if (!findPath(start, temp, tempPath))
				return false;

			for (List<Cell*>::Reverse_Iterator it = tempPath.rbegin(); it != tempPath.rend(); ++it)
			{
				if ((*it)->isDoor())
				{
					ReversedPathSequence.push_back(*it);
					DoorsAndKeysFound.push_back(*it);
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
			ReversedPathSequence.push_back(key);
			DoorsAndKeysFound.push_back(key);
		}
	}

	ReversedPathSequence.push_back(start);
	trimPathFromDublicatedKeys(ReversedPathSequence);

	for (List<Cell*>::Reverse_Iterator it = ReversedPathSequence.rbegin();
		it != ReversedPathSequence.rend(); ++it)
	{
		List<Cell*> pathBetweenTwoPoints;
		List<Cell*>::Reverse_Iterator it2 = it;
		++it2;
		if (it2 == ReversedPathSequence.rend())
			break;
		Cell* tempStart = *it;
		Cell* tempEnd = *it2;

		findPath(tempStart, tempEnd, pathBetweenTwoPoints);
		if (pathBetweenTwoPoints.getSize() > 0)
			addToFinalPath(finalPath, pathBetweenTwoPoints);
	}

	pathString = convertPathToString(finalPath);
	setPathWithSymbol(finalPath, '+');
	return true;
}



void PathFinder::trimPathFromDublicatedKeys(List<Cell*>& path)
{
	Vector<Cell*> keys;

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

		++it;
	}

}




const char* PathFinder::convertPathToString(List<Cell*>& path)
{
	Vector<char> directionSequence;
	Cell* current;
	Cell* next;

	for (List<Cell*>::Iterator it = path.begin(); it != path.end(); ++it)
	{
		List<Cell*>::Iterator it2 = it;
		++it2;
		if (it2 == path.end())
			break;
		current = *it;
		next = *it2;
		if (current->getPosition().nextPositionIsLeft(next->getPosition()))
			directionSequence.push('L');
		else if (current->getPosition().nextPositionIsRight(next->getPosition()))
			directionSequence.push('R');
		else if (current->getPosition().nextPositionIsUpper(next->getPosition()))
			directionSequence.push('U');
		else if (current->getPosition().nextPositionIsDown(next->getPosition()))
			directionSequence.push('D');
	}

	char* pathString = new char[directionSequence.getSize() + 1];

	size_t size = directionSequence.getSize();
	for (size_t i = 0; i < size; i++)
	{
		pathString[i] = directionSequence[i];
	}
	pathString[size] = '\0';

	return pathString;
}

void PathFinder::setPathWithSymbol(List<Cell*>& path, char pathSymbol)
{

	for (List<Cell*>::Iterator it = path.begin(); it != path.end(); ++it)
	{
		if ((*it)->getSymbol() == constants::START)
			continue;
		if ((*it)->getSymbol() == constants::END)
			break;
		(*it)->setSymbol(pathSymbol);
	}
}