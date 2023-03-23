#include "Maze.h"
#include "Cell.h"
#include "randgen.h"
#include <fstream>
#include <istream>

//Function to create random maze.
void Maze::generateMaze()
{
	mazeGenerateStack.push(current);
	current->setVisited(true);
	Cell * nextCell = nextCellRandom();

	while(!mazeGenerateStack.isEmpty())
	{
		Cell * nextCell = nextCellRandom();
		if (nextCell != NULL)
		{
			nextCell->setVisited(true);
			mazeGenerateStack.push(nextCell);
			current->removeWalls(*nextCell);
			current = nextCell;
		}
		else
		{
			current = mazeGenerateStack.top();
			mazeGenerateStack.pop();
		}
	}
}


int Maze::getCol() //Returns column size.
{
	return colSize;
}

int Maze::getRow() //Returns row size.
{
	return rowSize;
}

//Returns a vector of cell. Vector consist of the neighbor cells (that can be visited) of the current cell we are at.
std::vector<Cell *> Maze::nextCellCreator()
{
	std::vector<Cell *> possibleCells;
	int currRow = current->getRow();
	int currCol = current->getColumn();

	if(currCol-1 != -1 && !mazeContent[currRow][currCol-1].isVisited()) //Left side
		possibleCells.push_back(&mazeContent[currRow][currCol-1]);

	if(currRow-1 != -1 && !mazeContent[currRow-1][currCol].isVisited()) //Down side
		possibleCells.push_back(&mazeContent[currRow-1][currCol]);

	if(currRow+1 != rowSize && !mazeContent[currRow+1][currCol].isVisited()) //Top side
		possibleCells.push_back(&mazeContent[currRow+1][currCol]);

	if(currCol+1 != colSize && !mazeContent[currRow][currCol+1].isVisited()) //Right side
		possibleCells.push_back(&mazeContent[currRow][currCol+1]);

	return possibleCells;
}

//Returns a random cell from the vector of available neighbour cells.
Cell * Maze::nextCellRandom()
{
	RandGen randomGen;
	std::vector<Cell *> currentNeighbours = nextCellCreator();
	if (currentNeighbours.size() > 0)
		return currentNeighbours.at(randomGen.RandInt(0, currentNeighbours.size()-1));
	else return NULL;
}

//Prints the maze to txt file.
void Maze::printMaze()
{
	ofstream outputFileTxt;
	outputFileTxt.open("maze_" + std::to_string(id) + ".txt");
	outputFileTxt<<rowSize<<" "<<colSize<<endl;

	for(int i = 0; i < rowSize; i++){
		for(int j = 0; j < colSize; j++){

			outputFileTxt << mazeContent[i][j].cellInfo();
		}
	}
	outputFileTxt.close();
}

//Function to create a path from a point to another.
void Maze::findPath(int startX, int startY, int endX, int endY)
{
	Stack<Cell *> reverseList; //This will be used to reverse our stack, since we are required to write our starting from start point to end point.
	this->clearVisit(); //Clearing info of visit.

	pathCurrentCell = &mazeContent[startX][startY];
	pathCurrentCell->setVisited(true);
	pathGenerateStack.push(pathCurrentCell);

	while(!pathGenerateStack.isEmpty() && pathGenerateStack.top() != &mazeContent[endX][endY]) //Iterate until we find our end point or stack is empty.
	{
		Cell * nextPathCell = this->pathNextCellCreator();
		//If we can find a next cell to move.
		if (nextPathCell != NULL)
		{
			nextPathCell->setVisited(true);
			pathGenerateStack.push(nextPathCell);
			pathCurrentCell = nextPathCell;
		}
		//If we can't find, pop from stack.
		else
		{
			pathGenerateStack.pop();
			pathCurrentCell = pathGenerateStack.top();
		}
	}

	ofstream outputFileTxt;
	outputFileTxt.open("maze_" + std::to_string(id) + "_path_" + std::to_string(startX) + "_" +std::to_string(startY) +
		"_" + std::to_string(endX) + "_" +std::to_string(endY)+ ".txt");
	
	//Reverse the stack.
	while(!pathGenerateStack.isEmpty())
	{
		reverseList.push(pathGenerateStack.top());
		pathGenerateStack.pop();
	}
	while(!reverseList.isEmpty())
	{		
		outputFileTxt << reverseList.top()->getColumn() << " " << reverseList.top()->getRow() << "\n";
		reverseList.pop();
	}
	outputFileTxt.close();
}

//Returns the next cell we are going to try in order to find the path.
Cell * Maze::pathNextCellCreator()
{
	int pathCurrRow = pathCurrentCell->getRow();
	int pathCurrCol = pathCurrentCell->getColumn();

	if(pathCurrentCell->walls[LEFT] == 0 && !mazeContent[pathCurrRow][pathCurrCol-1].isVisited()) //Left side
		return &mazeContent[pathCurrRow][pathCurrCol-1];

	else if(pathCurrentCell->walls[BOTTOM] == 0 && !mazeContent[pathCurrRow-1][pathCurrCol].isVisited()) //Down side
		return &mazeContent[pathCurrRow-1][pathCurrCol];

	else if(pathCurrentCell->walls[TOP] == 0 && !mazeContent[pathCurrRow+1][pathCurrCol].isVisited()) //Top side
		return &mazeContent[pathCurrRow+1][pathCurrCol];

	else if(pathCurrentCell->walls[RIGHT] == 0 && !mazeContent[pathCurrRow][pathCurrCol+1].isVisited()) //Right side
		return &mazeContent[pathCurrRow][pathCurrCol+1];
	else
		return NULL;
}

void Maze::clearVisit()
{
	for(int i = 0; i < rowSize; i++)
	{
		for(int j = 0; j < colSize; j++)
			mazeContent[i][j].setVisited(false);
	}
}

Maze::~Maze()
{
	this->mazeContent.clear();
}