#include <iostream>
#include "Maze.h"
#include "Cell.h"
#include <vector>

// Call _CrtDumpMemoryLeaks after main has returned and before program terminates.
struct AtExit
{
    ~AtExit() { _CrtDumpMemoryLeaks(); }
} doAtExit;

using namespace std;

int main()
{
	int numberOfMazes, numberOfCols, numberOfRows, pathID, startRow, startCol, endRow, endCol;
	
	cout << "Enter the number of mazes: ";
	cin >> numberOfMazes;
	vector<Maze> mazeList;

	cout << "Enter the number of rows and columns: ";
	cin >> numberOfRows >> numberOfCols;
	
	for (int i = 1; i <= numberOfMazes; i++)
	{
		Maze mazedeneme(numberOfRows, numberOfCols, i);
		mazedeneme.generateMaze();
		mazedeneme.printMaze();
		mazeList.push_back(mazedeneme);
	}

	cout << "Enter a maze ID between 1 to " + to_string(numberOfMazes) + " inclusive to find a path: ";
	cin >> pathID;

	cout << "Enter x and y coordinates of the entry points (x,y) or (column,row): ";
	cin >> startCol >> startRow;
	
	cout << "Enter x and y coordinates of the exit points (x,y) or (column,row): ";
	cin >> endCol >> endRow;

	mazeList[pathID-1].findPath(startRow, startCol, endRow, endCol);
	mazeList.clear();

	
	return 0;
}