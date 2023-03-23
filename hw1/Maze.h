#ifndef MAZE_H
#define MAZE_H

#include <vector>
#include "Templated_stack.h"
#include "Cell.h"


class Maze {
	private:
		int colSize, rowSize, id;
		std::vector<std::vector<Cell>> mazeContent; //Stores info of cells in maze.
		Cell * current;                             //Will be used to create random maze.
		Cell * pathCurrentCell;						//Will be used to find a path.

		Stack<Cell *> mazeGenerateStack;			//Stack to create maze.
		Stack<Cell *> pathGenerateStack;			//Stack to find path.

		//Wanted to define three below in private part, in order to avoid scope problems in functions.
		std::vector<Cell *> nextCellCreator();
		Cell *nextCellRandom();
		Cell * pathNextCellCreator();

		
		enum direction { TOP, RIGHT, BOTTOM, LEFT };


	public:
		Maze(int rowSize, int colSize, int id) 
			: rowSize(rowSize), colSize(colSize), id(id)
			{
				for(int i = 0; i<rowSize; i++){
					std::vector<Cell> currRow;
					for(int j = 0; j<colSize; j++){
						Cell currCell(i, j);
						currRow.push_back(currCell);
					}
					mazeContent.push_back(currRow);
					currRow.clear();
				}
				current = &mazeContent[0][0];
			}
		~Maze();

		void generateMaze();
		void printMaze();
		void findPath(int, int, int, int);
		void clearVisit();

		//GETTERS
		int getRow();
		int getCol();
};

#endif