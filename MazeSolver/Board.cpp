#include "Board.h"

Cell** Board::allocate(const size_t height, const size_t width)
{
	Cell** temp = NULL;

	this->height = height;
	this->width = width;

	try
	{
		temp = new Cell*[height];

		for (size_t i = 0; i < height; i++)
		{
			temp[i] = new Cell[width];
		}
	}

	catch (std::bad_alloc)
	{
		free();
		this->height = 0;
		this->width = 0;
	}

	return temp;
}

Board::Board() : board(NULL), height(0), width(0) {}

void Board::free()
{

	for (size_t i = 0; i < height; i++)
	{
		delete[] board[i];
	}
	delete board;
	board = NULL;
	width = 0;
	height = 0;
}

void Board::copyFrom(const Board& other)
{
	height = other.height;
	width = other.width;

	board = allocate(height, width);

	for (size_t i = 0; i < height; i++)
		for (size_t j = 0; j < width; j++)
		{
			board[i][j] = other.board[i][j];
			board[i][j].setOwner(this);
		}
}

Board::Board(const Board& other)
{
	free();
	copyFrom(other);
}

Board& Board::operator=(const Board& other)
{
	if (this != &other)
	{
		free();
		copyFrom(other);
	}

	return *this;
}

Board::~Board()
{
	free();
}

bool Board::getBoardSizeFromFile(std::istream &in, size_t& newHeight, size_t& newWidth) const
{
	in.clear();
	in.seekg(0, std::ios::beg);

	int rows = 0;
	int columns = 0;
	int charCounter = 0;
	char c = 0;

	while (in.get(c))
	{
		if (c == '\n')
		{
			break;
		}
		columns++;
	}

	if (columns == 0)
		return false;

	while (in.get(c))
	{
		if (c == '\n')
		{
			if (columns != charCounter)
				return false;
			rows++;
			charCounter = 0;

			if (in.peek() == '\n')
			{
				rows++;
				break;
			}
		}
		else
			charCounter++;
	}

	newHeight = rows;
	newWidth = columns;
	return true;
}

bool Board::setLockPairsFromFile(std::istream &in)
{
	char c;
	char doorSymbol;
	char keySymbol;
	LockPair pair;
	while (in)
	{
		c = in.get();
		if (c == EOF)
			break;
		if (c == '\n')
		{
			continue;
		}
		doorSymbol = c;
		c = in.get();

		if (c == EOF || c == '\n')
			return false;
		keySymbol = c;

		pair.setDoorSymbol(doorSymbol);
		pair.setKeySymbol(keySymbol);
		lockPairs.push(pair);
	}
	if (lockPairs.isEmpty())
	{
		return false;
	}
	return true;
}

void Board::setBoardFromFile(std::istream &in)
{
	in.clear();
	in.seekg(0, std::ios::beg);

	char c;

	for (size_t i = 0; i < height; i++)
		for (size_t j = 0; j <= width; j++)
		{
			in.get(c);
			if (c == '\n')
				continue;
			board[i][j] = Cell(this, c, i, j);

			// TODO must be in cell constructor
			if (c == constants::PASSABLE)
			{
				board[i][j].setPassableStatus(true);
			}

			if (c == constants::START)
			{
				board[i][j].setStartStatus(true);
			}
			if (c == constants::END)
			{
				board[i][j].setEndStatus(true);
			}

			setLockPairsPositions(c, i, j);
		}
}

void Board::setLockPairsPositions(const char c, const size_t rowPosition, const size_t columnPosition)
{
	if (c == constants::PASSABLE || c == constants::WALL
		|| c == constants::START || c == constants::END)
		return;

	size_t size = lockPairs.getSize();
	for (size_t i = 0; i < size; i++)
	{
		// TODO must check if key or door has already been set
		if (lockPairs[i].getKeySymbol() == c)
		{
			lockPairs[i].setKeyPosition(rowPosition, columnPosition);
			return;
		}
		if (lockPairs[i].getDoorSymbol() == c)
		{
			lockPairs[i].setDoorPosition(rowPosition, columnPosition);
			return;
		}
	}
}

bool Board::loadFromFileName(const char* filename)
{
	std::ifstream inFile(filename);

	if (!inFile)
		return false;

	size_t heightFromFile = 0;
	size_t widthFromFile = 0;
	if (!getBoardSizeFromFile(inFile, heightFromFile, widthFromFile))
		return false;
	if (board)
		free();
	board = allocate(heightFromFile, widthFromFile);
	if (!board)
		return false;
	setLockPairsFromFile(inFile);
	setBoardFromFile(inFile);
	return true;
}

void Board::print() const
{
	for (size_t i = 0; i < height; i++)
	{
		for (size_t j = 0; j < width; j++)
		{
			std::cout << board[i][j].getSymbol();
		}
		std::cout << std::endl;
	}
}

Cell* Board::getCellAt(size_t row, size_t column) const
{
	if (row >= height || column >= width)
		return NULL;

	return &board[row][column];
}