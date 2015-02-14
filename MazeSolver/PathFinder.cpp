#include "PathFinder.h"

void PathFinder::calculateHCostOf(Cell* current, const Cell* end)
{

	// calculates the H cost of a given cell to the end using the manhattan method
	// by adding the differences between the two cells' row and column positions 
	
	size_t hCost =
		std::max(current->getPosition().rowPosition, end->getPosition().rowPosition) -
		std::min(current->getPosition().rowPosition, end->getPosition().rowPosition) +
		std::max(current->getPosition().columnPosition, end->getPosition().columnPosition) -
		std::min(current->getPosition().columnPosition, end->getPosition().columnPosition);
	current->setHCost(hCost);
}



void PathFinder::resetPathCells(List<Cell*>& openedCellsList, List<Cell*>& closedCellsList)
{

	// all cell were in the opened cell list must reset their statuses to false and parents again
	// in order to be able to be used for another path-finding pass of the algorithm 

	for (List<Cell*>::Iterator it = openedCellsList.begin(); it != openedCellsList.end(); ++it)
	{
		(*it)->setInOpenedListStatus(false);
		(*it)->setParent(NULL);
	}

	// all cell were in the closed cell list must reset their statuses to false and parents again
	// in order to be able to be used for another path-finding pass of the algorithm 

	for (List<Cell*>::Iterator it = closedCellsList.begin(); it != closedCellsList.end(); ++it)
	{
		(*it)->setInClosedListStatus(false);
		(*it)->setParent(NULL);
	}
}

bool PathFinder::findPath(Cell* start, Cell* end, List<Cell*>& path)
{


	// if the start and the end cell are the same
	// return
	if (start == end)
	{
		return true;
	}

	// list of cells that are to be inspected by the algorithm if they are 
	// the end cell 
	List<Cell*> openedCellsList;

	// list of cells that are already inspected by the algorithm so they
	// can't be inspected again
	List<Cell*> closedCellsList;

	// the current cell being inspected
	Cell* current;

	// first calculate the h cost of the starting cell
	calculateHCostOf(start, end);

	// set its g cost to 0 because g cost is the distance from the
	// start to the current cell, but the current cell is the start cell
	start->setGCost(0);

	// add the start cell to the opened cells list
	openedCellsList.push_back(start);

	// set it's isInOpenedList status to true
	start->setInOpenedListStatus(true);


	// set the current cell to the start cell
	current = start;


	// while there are cells to be inspected
	while (!openedCellsList.isEmpty())
	{

		current = openedCellsList.peek_front();


		// get the cell with the lowest f cost from the opened cells list
		for (List<Cell*>::Iterator it = openedCellsList.begin(); it != openedCellsList.end(); ++it)
		{
			if ((*it)->getFCost() <= current->getFCost())
			{
				current = *it;
			}
		}


		// if the current cell is the end cell
		if (current == end)
		{
			path.clear();

			// fill the path list with all cells from end to start
			// by knowing their parents
			// pushing them in the front rearranges the order
			// to start to end
			while (current)
			{
				path.push_front(current);
				current = current->getParent();
			}

			// reset all cells used in the search proccess
			resetPathCells(openedCellsList, closedCellsList);

			return true;
		}

		// else remove the current cell from the opened list
		openedCellsList.remove(current);

		// set it's isInOpenedList status to false;
		current->setInOpenedListStatus(false);
		
		// add it to the closed cells lists
		closedCellsList.push_back(current);

		// set it's isInClosedList status to true;
		current->setInClosedListStatus(true);

		// a vector that contains all valid neighbour of the current cell
		Vector<Cell*> neighbours;

		// get the valid neighbours in the vector
		current->getPassableNeighbours(neighbours);

		for (size_t i = 0; i < neighbours.getSize(); i++)
		{

			// for every valid neighbour
			Cell* neighbour = neighbours[i];

			// check if its in the closed list
			// if it is skipped
			if (neighbour->isInClosedList())
				continue;


			// calculate the g cost of that neighbour
			// the diagonal movement is forbidden
			// so the distance to the neighbour is always 1
			// so we just add 1
			size_t neighbourNextGCost = current->getGCost() + 1;


			// if the neighbour is not in the opened list or 
			// neighbour's next g cost is less that current neighbour g cost
			// meaning the current path found to the neigbour is shorter
			if (!neighbour->isInOpenedList() || neighbourNextGCost < neighbour->getGCost())
			{
				// re-parent the neighbour to the current cell
				neighbour->setParent(current);
				// set its g cost
				neighbour->setGCost(neighbourNextGCost);

				// if it wasn't in the opened list
				// add it and calculate it's h cost
				if (!neighbour->isInOpenedList())
				{
					neighbour->setInOpenedListStatus(true);
					openedCellsList.push_back(neighbour);
					calculateHCostOf(neighbour, end);
				}
			}
		}

	}

	// reset cells
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