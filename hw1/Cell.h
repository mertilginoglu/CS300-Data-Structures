#ifndef CELL_H
#define CELL_H
#include <string>

class Cell
{
	private:
		int row, column;
		int walls[4];
		bool visited;
		enum direction { TOP, RIGHT, BOTTOM, LEFT };

	public:
		Cell(int row, int col);

		void removeWalls(Cell &);

		void setWalls();
		void setVisited(bool);
		bool isVisited();
		std::string cellInfo();

		int getRow();
		int getColumn();

		friend class Maze;
};

#endif